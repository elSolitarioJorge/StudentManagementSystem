#include "student_management_system.h"

void mainMenu(AccNode* aHead, StuNode* sHead, TNode* tHead) {
    int choice = 0;
    while(1) {
        system("cls");
        displayMainMenu();
        choice = _getch();
        switch(choice) {
            case '0'://退出程序
                system("cls");
                printf("谢谢使用，再见！\n");
                pressAnyKeyToContinue();
                exit(0);
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

void displayMainMenu() {
    printf("╔═══════════════════════════════════╗\n");
    printf("║       🎓 学生信息管理系统 🎓      ║\n");
    printf("╟───────────────────────────────────╢\n");
    printf("║       🔑 1. 用户登录              ║\n");
    printf("║       🔓 2. 忘记密码              ║\n");
    printf("║       🚪 0. 退出系统              ║\n");
    printf("╚═══════════════════════════════════╝\n");
}

void userLogin(AccNode* aHead, StuNode* sHead, TNode* tHead) {
    char inputUserName[20] = "";
    char inputPassword[MAX_PASSWORD_LENGTH + 1] = "";
    system("cls");
    getStringInput("请输入用户名（账号）：", inputUserName, sizeof(inputUserName));
    printf("请输入密码：");
    inputHiddenPassword(inputPassword);
    AccNode* acc = authentication(aHead, inputUserName, inputPassword);
    if(acc == NULL) {
        printf("用户名或密码错误，请重试\n");
        pressAnyKeyToContinue();
        return;
    }
    switch(acc->account.role) {
        case 'S':
            studentMenu(acc, sHead);
            break;
        case 'T':
            teacherMenu(acc, sHead);
            break;
        case 'A':
            adminMenu(acc, aHead, sHead, tHead);
            break;
        default:
            break;
    }
}

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

void inputHiddenPassword(char* inputPassword) {
    int i = 0;
    while(1) {
        int input = _getch();
        if(input == '\r') {
            if(i > 0) break;
        }else if(input == '\b') {
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        }else if(i < MAX_PASSWORD_LENGTH) {
            inputPassword[i++] = input;
            putchar('*');
        }
    }
    putchar('\n');
    inputPassword[i] = '\0';
}

AccNode* authentication(const AccNode *aHead, const char *inputUserName, const char *inputPassword) {
    AccNode* cur = aHead->next;
    while(cur != NULL) {
        if(strcmp(cur->account.userName, inputUserName) == 0) {
            unsigned char inputHash[HASH_LENGTH];
            hashPassword(inputPassword, cur->account.salt, inputHash);
            if(memcmp(inputHash, cur->account.passwordHash, HASH_LENGTH) == 0) {
                return cur;
            }
        }
        cur = cur->next;
    }
    return NULL;
}