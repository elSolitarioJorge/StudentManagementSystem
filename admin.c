#include "student_management_system.h"

void adminMenu(AccNode* myAccount, AccNode* aHead, StuNode* sHead, TNode* tHead) {
    int choice = 0;
    int count = 0;
    TNode* temp = tHead->next;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    while(1) {
        system("cls");
        displayAdminMenu(count);
        choice = _getch();
        switch(choice) {
            case '0':
                return;
            case '1':
                addAccount(aHead);
                break;
            case '2':
                deleteAccount(aHead);
                break;
            case '3':
                changeAccount(aHead);
                break;
            case '4':
                findPrevAccount(aHead);
                pressAnyKeyToContinue();
                break;
            case '5':
                pagePrintingAccount(aHead, 12);
                break;
            case '6':
                printTodo(tHead, count);
                break;
            case '7':
                finishTodo(aHead, tHead, &count);
                break;
            case '8':
                teacherMenu(myAccount, sHead);
                break;
            default :
                break;
        }
    }
}

void displayAdminMenu(int count) {
    printf("欢迎管理员登录！\n");
    printf("1.添加账户信息\n");
    printf("2.删除账户信息\n");
    printf("3.更改账户信息\n");
    printf("4.查找账户信息\n");
    printf("5.查看所有账户信息\n");
    printf("6.查看代办(%d)\n", count);
    printf("7.完成代办\n");
    printf("8.登录教师端\n");
    printf("0.返回上一级\n");
}

void addAccount(AccNode* aHead) {
    system("cls");
    AccNode* newAccount = createAccountNode();
    printf("---添加账户---\n");
    printf("请选择账户身份（S：学生  T：教师  A：管理员）：");
    newAccount->account.role = selectIdentify();
    getStringInput("请输入用户名(账号）：", newAccount->account.userName, sizeof(newAccount->account.userName));
    getStringInput("姓名：", newAccount->account.name, sizeof(newAccount->account.name));
    initAccount(newAccount);
    appendAccountNodeAtTail(aHead, newAccount);
    writeAccountToFile(aHead);
    printf("---账户添加成功---\n");
    pressAnyKeyToContinue();
}

void deleteAccount(AccNode* aHead) {
    AccNode* prevAcc = findPrevAccount(aHead);
    if(prevAcc != NULL) {
        char choice;
        printf("是否确认删除此账户(Y/N):");
        scanf(" %c", &choice);
        clearInputBuffer();
        if(choice == 'Y' || choice == 'y') {
            AccNode* delAcc = prevAcc->next;
            prevAcc->next = delAcc->next;
            free(delAcc);
            writeAccountToFile(aHead);
            printf("删除成功！！！\n");
        } else {
            printf("已取消删除！！！\n");
        }
    }
    pressAnyKeyToContinue();
}

void changeAccount(AccNode* aHead) {
    AccNode* cur = findPrevAccount(aHead)->next;
    if(cur) {
        getStringInput("设置用户名：", cur->account.userName, sizeof(cur->account.userName));
        getStringInput("设置姓名：  ", cur->account.name, sizeof(cur->account.name));
        printf("设置身份（S/T/A）：");
        cur->account.role = selectIdentify();
        printf("更改成功！\n");
    }
    pressAnyKeyToContinue();
}

AccNode* findPrevAccount(AccNode* aHead) {
    system("cls");
    char userName[20];
    AccNode* prev = aHead;
    getStringInput("请输入用户名（账号）：", userName, sizeof(userName));
    while(prev->next != NULL) {
        if(strcmp(prev->next->account.userName, userName) == 0) {
            printf("该用户信息如下：\n");
            printf("用户名：%s\n", prev->next->account.userName);
            printf("姓名：  %s\n", prev->next->account.name);
            switch(prev->next->account.role) {
                case 'A':
                    printf("身份：  管理员\n");
                    break;
                case 'T':
                    printf("身份：  教师\n");
                    break;
                case 'S':
                    printf("身份：  学生\n");
                    break;
                default:
                    printf("身份：  未知\n");
                    break;
            }
            return prev;
        }
        prev = prev->next;
    }
    printf("未找到该用户\n");
    return prev;
}

void pagePrintingAccount(const AccNode* aHead, int pageSize) {
    AccNode* cur = aHead->next;
    int size = 0;
    while(cur != NULL) {
        size++;
        cur = cur->next;
    }
    int currentPage = 1, totalPages = (size + pageSize - 1) / pageSize;
    cur = aHead->next;
    while(1) {
        system("cls");
        printf("---用户信息---\n\n");
        printf("账号\t\t姓名\t\t用户身份\n");
        int count = 0;
        AccNode* temp = cur;
        while(temp && count < pageSize) {
            printf("%-16s%-16s", temp->account.userName, temp->account.name);
            if(temp->account.role == 'S') {
                printf("学生\n");
            } else if(temp->account.role == 'T') {
                printf("教师\n");
            } else if(temp->account.role == 'A') {
                printf("管理员\n");
            }
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

void printTodo(const TNode* tHead, int count) {
    system("cls");
    TNode* cur = tHead->next;
    printf("有%d个密码申诉代办，请尽快处理！\n", count);
    while(cur) {
        printf("用户名：%s\n", cur->userName);
        cur = cur->next;
    }
    pressAnyKeyToContinue();
}

void finishTodo(const AccNode* aHead, TNode* tHead, int* count) {
    system("cls");
    while(tHead->next) {
        AccNode* acc = aHead->next;
        while(acc) {
            if(strcmp(acc->account.userName, tHead->next->userName) == 0) {
                RAND_bytes(acc->account.salt, SALT_LENGTH);
                const char* newPass = acc->account.role == 'S' ? acc->account.userName + strlen(acc->account.userName) - 6 : "111111";
                hashPassword(newPass, acc->account.salt, acc->account.passwordHash);
                TNode* del = tHead->next;
                tHead->next = del->next;
                free(del);
                (*count)--;
                break;
            }
            acc = acc->next;
        }
    }
    writeAccountToFile(aHead);
    writeTodoToFile(tHead);
    printf("已将所有申诉账号密码重置完成！（学生初始密码为学号后六位，其他账号初始密码为\"111111\"）\n");
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

void hashPassword(const char* password, const unsigned char* salt, unsigned char* outputHash) {
    unsigned char saltedPass[SALT_LENGTH + MAX_PASSWORD_LENGTH];
    // 生成盐值+密码组合
    memcpy(saltedPass, salt, SALT_LENGTH);
    memcpy(saltedPass + SALT_LENGTH, password, strlen(password));
    // SHA256哈希计算
    SHA256(saltedPass, SALT_LENGTH + strlen(password), outputHash);
}

void initAccount(AccNode* acc) {
    if(!RAND_bytes(acc->account.salt, SALT_LENGTH)) {
        fprintf(stderr, "盐值生成失败\n");
        exit(EXIT_FAILURE);
    }
    const char* initPass = acc->account.role == 'S' ? acc->account.userName + strlen(acc->account.userName) - 6 : "111111";
    hashPassword(initPass, acc->account.salt, acc->account.passwordHash);
}

