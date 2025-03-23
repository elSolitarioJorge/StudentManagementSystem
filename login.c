#include "student_management_system.h"
// 主菜单
void mainMenu(AccNode* aHead, StuNode* sHead, TNode* tHead) {
    int choice = 0;
    while(1) {
        system("cls");   // 清屏
        displayMainMenu();        // 显示主菜单界面
        choice = _getch();        // 获取用户输入
        switch(choice) {          // 根据用户输入进行操作
            case '0'://退出程序
                system("cls");
                printf("谢谢使用，再见！\n");
                pressAnyKeyToContinue();  // 按任意键继续
                exit(0);     // 退出程序
            case '1'://用户登录
                userLogin(aHead, sHead, tHead);
                break;
            case '2'://忘记密码
                passwordAppeal(aHead, tHead);
                break;
            default:
                break;
        }
    }
}
// 主菜单界面
void displayMainMenu() {
    printf("╔═══════════════════════════════════╗\n");
    printf("║       🎓 学生信息管理系统 🎓      ║\n");
    printf("╟───────────────────────────────────╢\n");
    printf("║       🔑 1. 用户登录              ║\n");
    printf("║       🔓 2. 忘记密码              ║\n");
    printf("║       🚪 0. 退出系统              ║\n");
    printf("╚═══════════════════════════════════╝\n");
}
// 用户登录
void userLogin(AccNode* aHead, StuNode* sHead, TNode* tHead) {
    char inputUserName[20] = "";    // 接收用户名输入
    char inputPassword[MAX_PASSWORD_LENGTH + 1] = "";  // 接收密码输入
    system("cls");    // 清屏
    getStringInput("请输入用户名（账号）：", inputUserName, sizeof(inputUserName));  // 获取用户名
    printf("请输入密码：");
    inputHiddenPassword(inputPassword);   // 获取密码
    AccNode* acc = authentication(aHead, inputUserName, inputPassword);  // 进行身份验证
    if(acc == NULL) {  // 验证失败
        printf("用户名或密码错误，请重试\n");
        pressAnyKeyToContinue();
        return;
    }
    // 验证成功，根据用户身份信息进入不同界面
    switch(acc->account.role) {
        case 'S':
            studentMenu(acc, sHead);   // 学生界面
            break;
        case 'T':
            teacherMenu(acc, sHead);   // 教师界面
            break;
        case 'A':
            adminMenu(acc, aHead, sHead, tHead); // 管理员界面
            break;
        default:
            break;
    }
}
// 密码申诉，将忘记密码的用户名写入代办
void passwordAppeal(const AccNode* aHead, TNode* tHead) {
    system("cls");
    AccNode* acc = aHead->next;
    TNode* newTodo = createTodoNode();
    getStringInput("请输入用户名（账号）：", newTodo->userName, sizeof(newTodo->userName));
    while(acc) {
        if(strcmp(acc->account.userName, newTodo->userName) == 0) {
            appendTodoNodeAtTail(tHead, newTodo);
            writeTodoToFile(tHead);
            printf("密码申诉成功，请及时联系管理员帮你重置密码！\n");
            printf("管理员邮箱：2869828375@qq.com\n");
            break;
        }
        acc = acc->next;
    }
    if(acc == NULL) {
        printf("用户名错误，请重试！\n");
    }
    pressAnyKeyToContinue();
}
// 隐式输入密码
void inputHiddenPassword(char* inputPassword) {
    int i = 0;
    while(1) {
        int input = _getch();
        if(input == '\r') {  // 读取到回车键就退出
            if(i > 0) break;
        }else if(input == '\b') {  // 读取到退格键就删除一个字符
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        }else if(i < MAX_PASSWORD_LENGTH) {
            inputPassword[i++] = input;   // 将读取到的密码储存起来
            putchar('*');   // 用'*'显示给用户
        }
    }
    putchar('\n');
    inputPassword[i] = '\0';
}
// 验证身份信息
AccNode* authentication(const AccNode *aHead, const char *inputUserName, const char *inputPassword) {
    AccNode* cur = aHead->next;
    while(cur != NULL) {
        if(strcmp(cur->account.userName, inputUserName) == 0) {  // 用户名匹配
            unsigned char inputHash[HASH_LENGTH];
            hashPassword(inputPassword, cur->account.salt, inputHash);
            if(memcmp(inputHash, cur->account.passwordHash, HASH_LENGTH) == 0) {  // 密码匹配
                return cur;
            }
        }
        cur = cur->next;
    }
    return NULL;
}