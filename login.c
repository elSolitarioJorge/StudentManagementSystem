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
                wait();
                exit(0);
            case 1://用户登录
                userLogin(aHead, sHead);
            break;
            case 2://忘记密码
                //passwordRecovery();
            break;
            default:
                printf("输入不合法，请输入0~2之间的整数\n");
                wait();
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

int getValidInput(int min, int max) {
    int input;
    char monitoring; //用于监视输入  monitor  v.监测;监视;监控
    if(scanf("%d%c", &input, &monitoring) != 2 || monitoring != '\n') {
        while(getchar() != '\n');//清空输入缓冲区
        return -1;
    }
    if(input < min || input > max) {
        return -1;
    }
    return input;
}

void wait() {
    printf("请按任意键继续...\n");
    _getch();
}

void userLogin(accNode* aHead, stuNode* sHead) {
    char inputUserName[20] = "";
    char inputPassword[MAX_PASSWORD_LENTH + 1] = "";
    system("cls");
    printf("请输入用户名(账号)：");
    scanf("%19s", inputUserName);
    while(getchar() != '\n');
    printf("请输入密码：");
    inputHiddenPassword(inputPassword);
    char role;
    if(authentication(inputUserName, inputPassword, &role)) {
        switch(role) {
            case 'S':
                //studentMenu();
            break;
            case 'T':
                //teacherMenu();
            break;
            case 'A':
                adminMenu(aHead);
            break;
            default:
            break;
        }
    } else {
        printf("用户名或密码错误！！！\n");
        wait();
    }

}

void inputHiddenPassword(char* inputPassword) {
    int i = 0;
    char input;
    while((input = _getch()) != '\r') {
        if(input == '\b') {
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        }else if(i < MAX_PASSWORD_LENTH) {
            inputPassword[i++] = input;
            putchar('*');
        }
    }
    putchar('\n');
    inputPassword[i] = '\0';
}

int authentication(const char* inputUserName, const char* inputPassword, char* role) {
    FILE* fp = fopen("account.txt", "rb");
    if(fp == NULL) {
        perror("Error opening account.txt");
        wait();
        return 0;
    }
    char userName[21] = "";
    char password[MAX_PASSWORD_LENTH + 1] = "";
    accNode* user = (accNode*)malloc(sizeof(accNode));
    user->next = NULL;
    while(!feof(fp)) {
        fread(user, sizeof(accNode), 1, fp);
        *role = user->account.role;
        if(strcmp(user->account.userName, inputUserName) == 0 && strcmp(user->account.password, inputPassword) == 0) {
            fclose(fp);
            free(user);
            return 1;
        }
    }
    fclose(fp);
    free(user);
    return 0;
}