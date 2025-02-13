#include "StudentManagementSystem.h"

void mainMenu(accNode* aHead, stuNode* sHead) {

    int choice = 0;

    do {

        system("cls");
        displayMainMenu();

        choice = getValidInput(0, 2);
        switch(choice) {
            case 0://退出程序
                printf("谢谢使用，再见！\n");
                pressAnyKeyToContinue();
                exit(0);
            case 1://用户登录
                userLogin(aHead, sHead);
                break;
            case 2://忘记密码
                //passwordRecovery();
                break;
            default:
                printf("输入不合法，请输入0~2之间的整数\n");
                pressAnyKeyToContinue();
                break;
        }
    } while(choice);
}

void displayMainMenu() {
    printf("欢迎使用学生信息管理系统\n");
    printf("0.退出\n");
    printf("1.用户登录\n");
    printf("2.忘记密码\n");
}

void userLogin(accNode* aHead, stuNode* sHead) {
    char inputUserName[20] = "";
    char inputPassword[MAX_PASSWORD_LENGTH + 1] = "";
    system("cls");
    getStringInput("请输入用户名（账号）：", inputUserName, sizeof(inputUserName));
    printf("请输入密码：");
    inputHiddenPassword(inputPassword);
    char role = authentication(aHead, inputUserName, inputPassword);
    switch(role) {
        case 'S':
            //studentMenu();
        break;
        case 'T':
            teacherMenu(sHead);
        break;
        case 'A':
            adminMenu(aHead);
        break;
        default:
            printf("用户名或密码错误，请重试\n");
            pressAnyKeyToContinue();
        break;
    }
}

void inputHiddenPassword(char* inputPassword) {
    int i = 0;
    int input;
    while((input = _getch()) != '\r') {
        if(input == '\b') {
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

char authentication(const accNode* aHead, const char* inputUserName, const char* inputPassword) {
    accNode* cur = aHead->next;
    while(cur != NULL) {
        if(strcmp(cur->account.userName, inputUserName) == 0 && strcmp(cur->account.password, inputPassword) == 0) {
            return cur->account.role;
        }
        cur = cur->next;
    }
    return -1;
}