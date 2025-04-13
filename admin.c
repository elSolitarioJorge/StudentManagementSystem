#include "student_management_system.h"
// 管理员菜单
void adminMenu(AccNode* myAccount, AccNode* aHead, StuNode* sHead, TNode* tHead) {
    int choice = 0;
    int count = 0;
    // 统计代办数量
    TNode* temp = tHead->next;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    while(1) {
        system("cls");     // 清屏
        displayAdminMenu(count);    // 显示管理员菜单界面
        choice = _getch();          // 获取用户输入
        switch(choice) {
            case '0':           // 返回
                return;
            case '1':           // 添加账户
                addAccount(aHead);
                break;
            case '2':           // 删除账户
                deleteAccount(aHead, myAccount);
                break;
            case '3':           // 修改账户
                changeAccount(aHead);
                break;
            case '4':           // 查找账户
                findPrevAccount(aHead);
                pressAnyKeyToContinue();
                break;
            case '5':           // 所有账户
                pagePrintingAccount(aHead, 20);
                break;
            case '6':           // 查看待办事项
                printTodo(tHead, count);
                break;
            case '7':           // 完成代办
                finishTodo(aHead, tHead, &count);
                break;
            case '8':           // 进入教师菜单
                teacherMenu(myAccount, sHead);
                break;
            default :
                break;
        }
    }
}
// 显示管理员菜单界面
void displayAdminMenu(int count) {
    printf("╔════════════════════════════════╗\n");
    printf("║       👑 管理员控制台 👑       ║\n");
    printf("╟────────────────────────────────╢\n");
    printf("║       ➕ 1. 添加账户           ║\n");
    printf("║       ✖️ 2. 删除账户           ║\n");
    printf("║       ✏️ 3. 修改账户           ║\n");
    printf("║       🔍 4. 查找账户           ║\n");
    printf("║       📜 5. 所有账户           ║\n");
    printf("║       📨 6. 待办事项(%d)        ║\n", count);
    printf("║       ✅ 7. 完成待办           ║\n");
    printf("║       👨 8. 教师模式           ║\n");
    printf("║       ↩️ 0. 返回               ║\n");
    printf("╚════════════════════════════════╝\n");
}
// 添加账户
void addAccount(AccNode* aHead) {
    system("cls");    // 清屏
    AccNode* newAccount = createAccountNode();
    printf("---添加账户---\n");
    printf("请选择账户身份（S：学生  T：教师  A：管理员）：");
    // 选择账户身份
    newAccount->account.role = selectIdentify();
    // 输错5次，直接返回
    if(newAccount->account.role == -1) {
        return;
    }
    // 输入用户名
    getStringInput("请输入用户名(账号）：", newAccount->account.userName, sizeof(newAccount->account.userName));
    if(usernameExist(aHead, newAccount->account.userName)) {
        printf("用户名已存在，请重新操作\n");
        pressAnyKeyToContinue();
        return;
    }
    // 输入密码
    getStringInput("姓名：", newAccount->account.name, sizeof(newAccount->account.name));
    // 初始化账户（对密码进行哈希加盐加密）
    initAccount(newAccount);
    // 添加到链表尾部
    appendAccountNodeAtTail(aHead, newAccount);
    // 将账户信息写入文件
    writeAccountToFile(aHead);
    printf("---账户添加成功---\n");
    pressAnyKeyToContinue();
}
// 删除账户
void deleteAccount(AccNode* aHead, AccNode* myAccount) {
    //查找账户
    AccNode* prevAcc = findPrevAccount(aHead);
    // 找到该账户，执行删除操作
    if(prevAcc != NULL) {
        if(prevAcc->next == myAccount) {
            printf("管理员先生，你正在试图删除你自己，这种做法是不被允许的!!!\n");
            pressAnyKeyToContinue();
            return;
        }
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
// 修改账户
void changeAccount(AccNode* aHead) {
    // 先查找，再修改
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
// 查找账户（可根据用户名或姓名查找）
AccNode* findPrevAccount(AccNode* aHead) {
    system("cls");
    char str[50];
    AccNode* prev = aHead;
    getStringInput("请输入用账号或姓名：", str, sizeof(str));
    while(prev->next != NULL) {
        // 用户名和密码均匹配成功，找到账户，显示账户信息
        if(strcmp(prev->next->account.userName, str) == 0 || strcmp(prev->next->account.name, str) == 0) {
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
// 分页打印账户信息（单向链表）
void pagePrintingAccount(const AccNode* aHead, int pageSize) {
    AccNode* cur = aHead->next;
    // 计算链表长度
    int size = 0;
    while(cur != NULL) {
        size++;
        cur = cur->next;
    }
    // 记录当前页，计算总页数
    int currentPage = 1, totalPages = (size + pageSize - 1) / pageSize;
    cur = aHead->next;
    while(1) {
        system("cls");
        printf("---用户信息---\n\n");
        printf("账号\t\t姓名\t\t用户身份\n");
        int count = 0;
        AccNode* temp = cur;
        // 打印当前页的账户信息
        while(temp && count < pageSize) {
            printf("%-16s%s\t\t", temp->account.userName, temp->account.name);
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
        // 如果当前页不是最后一页，提示怎么进入下一页
        if (currentPage < totalPages) {
            printf("按 N 查看下一页，");
        }
        // 如果当前页不是第一页，提示怎么返回上一页
        if (currentPage > 1) {
            printf("按 B 返回上一页，");
        }
        // 提示如何退出
        printf("按 Q 退出：");
        // 获取用户输入
        int command = _getch();
        // 根据用户输入，进行相应的操作
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
// 打印待处理申诉
void printTodo(const TNode* tHead, int count) {
    system("cls");
    TNode* cur = tHead->next;
    if(count == 0) {
        printf("勤劳的管理员，所有代办都已处理完成，您可以尽情地去玩原神啦!\n");
        pressAnyKeyToContinue();
        return;
    }
    printf("有%d个密码申诉代办，请尽快处理！\n", count);
    while(cur) {
        printf("用户名：%s\n", cur->userName);
        cur = cur->next;
    }
    pressAnyKeyToContinue();
}
// 一键完成所有申诉，将申诉账户密码进行重置，学生账户密码为学号后六位，其他账户密码为"111111"
void finishTodo(const AccNode* aHead, TNode* tHead, int* count) {
    system("cls");
    if(*count == 0) {
        printf("没有待处理的申诉!\n");
        pressAnyKeyToContinue();
        return;
    }
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
    system("cls");
    printf("已将所有申诉账号密码重置完成！（学生初始密码为学号后六位，其他账号初始密码为\"111111\"）\n");
    pressAnyKeyToContinue();
}
// 选择身份
char selectIdentify() {
    char ch;
    char monitoring;
    int count = 5;
    while(count--) {
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
    printf("\n错误次数过多，请重新操作！！！\n");
    Sleep(2000);
    return -1;
}
// 生成盐值+密码哈希
void hashPassword(const char* password, const unsigned char* salt, unsigned char* outputHash) {
    unsigned char saltedPass[SALT_LENGTH + MAX_PASSWORD_LENGTH];
    // 生成盐值+密码组合
    memcpy(saltedPass, salt, SALT_LENGTH);
    memcpy(saltedPass + SALT_LENGTH, password, strlen(password));
    // SHA256哈希计算
    SHA256(saltedPass, SALT_LENGTH + strlen(password), outputHash);
}
// 初始化账户
void initAccount(AccNode* acc) {
    if(!RAND_bytes(acc->account.salt, SALT_LENGTH)) {
        fprintf(stderr, "盐值生成失败\n");
        exit(EXIT_FAILURE);
    }
    const char* initPass = acc->account.role == 'S' ? acc->account.userName + strlen(acc->account.userName) - 6 : "111111";
    hashPassword(initPass, acc->account.salt, acc->account.passwordHash);
}
// 判断学号是否存在
int usernameExist(AccNode* aHead, char* userName) {
    AccNode* cur = aHead->next;
    while(cur) {
        if(strcmp(cur->account.userName, userName) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}
