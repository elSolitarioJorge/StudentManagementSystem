#include "StudentManagementSystem.h"

void adminMenu(accNode* aHead) {
    int choice = 0;

    do {
        system("cls");
        displayAdminMenu();

        choice = getValidInput(0, 3);
        switch(choice) {
            case 0:
                return;
            case 1:
                addAccount(aHead);
            break;
            case 2:
                deleteAccount(aHead);
            break;
            case 3:
                pagePrintingAccount(aHead, 5);
            break;
            default :
                printf("输入不合法，请输入0~3之间的整数\n");
                wait();
            break;
        }
    } while(choice);
}

void displayAdminMenu() {
    printf("欢迎管理员登录！\n");
    printf("1.添加账户信息\n");
    printf("2.删除账户信息\n");
    printf("3.打印所有账户信息\n");
    printf("0.返回上一级\n");
}

void addAccount(accNode* aHead) {
    system("cls");
    char userName[20] = "";
    char password1[MAX_PASSWORD_LENTH + 1] = "";
    char password2[MAX_PASSWORD_LENTH + 1] = "";
    printf("---添加账户---\n");
    printf("请选择账户身份（S：学生  T：教师  A：管理员）：");
    char role = selectIdentify();
    printf("请输入用户名(账号）(长度不超过10位的字符串）：");
    getValidAccount(userName);
    setPassword(password1, password2);
    accNode* newAccount = (accNode*)malloc(sizeof(accNode));
    strcpy(newAccount->account.userName, userName);
    strcpy(newAccount->account.password, password1);
    newAccount->account.role = role;
    accNode* tail = aHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newAccount->next = NULL;
    tail->next = newAccount;
    writeAccountToFile(aHead);
    printf("---账户添加成功---\n");
    printf("新账户信息：\n");
    printf("用户名：%s\n", newAccount->account.userName);
    printf("密码：  %s\n", newAccount->account.password);
    printf("身份：  %c\n", newAccount->account.role);
    wait();
}

char selectIdentify() {
    char ch;
    char monitoring;
    while(1) {
        if(scanf(" %c%c", &ch, &monitoring) != 2 || monitoring != '\n') {
            while(getchar() != '\n');
            printf("输入不合法，请输入一个字符（S/T/A）：");
        }
        else if(ch == 'S' || ch == 's') {
            return 'S';
        }
        else if(ch == 'T' || ch =='t') {
            return 'T';
        }
        else if(ch == 'A' || ch == 'a') {
            return 'A';
        }
        else {
            printf("没有此选项，请重新输入（S：学生  T：教师  A：管理员）：");
        }
    }
}

void getValidAccount(char* userName) {
    do {
        scanf("%19s", userName);
        while(getchar() != '\n');
        if(strlen(userName) > 10) {
            printf("用户名过长，请重新输入：");
        }
    } while(strlen(userName) > 10);
}

void setPassword(char* password1, char* password2) {
    do {
        printf("请输入密码：");
        inputHiddenPassword(password1);
        printf("请确认密码：");
        inputHiddenPassword(password2);
        if(strcmp(password1, password2) != 0) {
            printf("密码不匹配，请重试\n");
        }
    } while(strcmp(password1, password2) != 0);
}

void deleteAccount(accNode* aHead) {
    system("cls");
    char userName[20] = "";
    accNode* cur = aHead;
    printf("请输入要删除的用户名（账号）：");
    scanf("%19s", userName);
    while(getchar() != '\n');
    while(cur->next != NULL) {
        if(strcmp(cur->next->account.userName, userName) == 0) {
            char choice;
            printf("是否确认删除此账户(Y/N):");
            scanf(" %c", &choice);
            while(getchar() != '\n');
            if(choice == 'Y' || choice == 'y') {
                accNode* del = cur->next;
                cur->next = del->next;
                free(del);
                writeAccountToFile(aHead);
                printf("删除成功！！！\n");
                wait();
                return;
            } else {
                printf("已取消删除！！！\n");
                wait();
                return;
            }
        }
        cur = cur->next;
    }
    printf("没有找到该用户！！！\n");
    wait();
}