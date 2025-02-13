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
                pagePrintingAccount(aHead, 1);
                break;
            default :
                printf("输入不合法，请输入0~3之间的整数\n");
                pressAnyKeyToContinue();
                break;
        }
    } while(choice);
}

void displayAdminMenu() {
    printf("欢迎管理员登录！\n");
    printf("1.添加账户信息\n");
    printf("2.删除账户信息\n");
    printf("3.查看所有账户信息\n");
    printf("0.返回上一级\n");
}

void addAccount(accNode* aHead) {
    system("cls");
    char userName[20] = "";
    char password1[MAX_PASSWORD_LENGTH + 1] = "";
    char password2[MAX_PASSWORD_LENGTH + 1] = "";
    printf("---添加账户---\n");
    printf("请选择账户身份（S：学生  T：教师  A：管理员）：");
    char role = selectIdentify();
    printf("请输入用户名(账号）(长度不超过10位的字符串）：");
    getValidAccount(userName);
    setPassword(password1, password2);
    accNode* newAccount = createAccountNode();
    strcpy(newAccount->account.userName, userName);
    strcpy(newAccount->account.password, password1);
    newAccount->account.role = role;
    appendAccountNodeAtTail(aHead, newAccount);
    writeAccountToFile(aHead);
    printf("---账户添加成功---\n");
    printf("新账户信息：\n");
    printf("用户名：%s\n", newAccount->account.userName);
    printf("密码：  %s\n", newAccount->account.password);
    printf("身份：  %c\n", newAccount->account.role);
    pressAnyKeyToContinue();
}

char selectIdentify() {
    char ch;
    char monitoring;
    while(1) {
        if(scanf(" %c%c", &ch, &monitoring) != 2 || monitoring != '\n') {
            clearInputBuffer();
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
        clearInputBuffer();
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
    getStringInput("请输入要删除的用户名（账号）：", userName, sizeof(userName));
    while(cur->next != NULL) {
        if(strcmp(cur->next->account.userName, userName) == 0) {
            char choice;
            printf("是否确认删除此账户(Y/N):");
            scanf(" %c", &choice);
            clearInputBuffer();
            if(choice == 'Y' || choice == 'y') {
                accNode* del = cur->next;
                cur->next = del->next;
                free(del);
                writeAccountToFile(aHead);
                printf("删除成功！！！\n");
                pressAnyKeyToContinue();
                return;
            } else {
                printf("已取消删除！！！\n");
                pressAnyKeyToContinue();
                return;
            }
        }
        cur = cur->next;
    }
    printf("没有找到该用户！！！\n");
    pressAnyKeyToContinue();
}

void pagePrintingAccount(const accNode* aHead, int pageSize) {
    accNode* cur = aHead->next;
    int size = 0;
    while(cur != NULL) {
        size++;
        cur = cur->next;
    }
    int currentPage = 1, totalPages = (size + pageSize - 1) / pageSize;
    cur = aHead->next;
    while(1) {
        system("cls");
        printf("---用户账密信息---\n\n");
        printf("账号\t\t用户身份\t密码\n");
        int count = 0;
        accNode* temp = cur;
        while(temp && count < pageSize) {
            printf("%-16s", temp->account.userName);
            if(temp->account.role == 'S') {
                printf("学生\t\t");
            } else if(temp->account.role == 'T') {
                printf("教师\t\t");
            } else if(temp->account.role == 'A') {
                printf("管理员\t\t");
            }
            printf("%s\n", temp->account.password);
            temp = temp->next;
            count++;
        }
        printf("\n\t--------Page(%d/%d)--------\n\n", currentPage, totalPages);
        if (currentPage < totalPages) {
            printf("按 N 查看下一页，");
        }
        if (currentPage > 1) {
            printf("按 B 返回上一页，");
        }
        printf("按 Q 退出：");
        int command = _getch();
        if((command == 'N' || command == 'n') && currentPage < totalPages) {
            for(int i = 0; i < pageSize && cur; i++) {
                cur = cur->next;
            }
            currentPage++;
        } else if((command == 'B' || command == 'b') && currentPage > 1) {
            cur = aHead->next;
            for(int i = 0; i < pageSize * (currentPage - 2) && cur; i++) {
                cur = cur->next;
            }
            currentPage--;
        } else if(command == 'Q' || command == 'q') {
            break;
        }
    }
}
