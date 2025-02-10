#include "StudentManagementSystem.h"

int main() {
    accNode* aHead = (accNode*)malloc(sizeof(accNode));
    aHead->next = NULL;
    stuNode* sHead = (stuNode*)malloc(sizeof(stuNode));
    sHead->next = NULL;
    readAccountFromFile(aHead);
    wait();
    system("cls");
    mainMenu(aHead, sHead);
    free(aHead);
    free(sHead);
    return 0;
}

void addAdmin(accNode* aHead) {
    accNode* admin = (accNode*)malloc(sizeof(accNode));
    if(admin == NULL) {
        perror("Error allocating memory");
        wait();
        return;
    }
    admin->next = NULL;
    aHead->next = admin;
    strcpy(admin->account.userName, "admin");
    strcpy(admin->account.password, "000000");
    admin->account.role = 'A';
    writeAccountToFile(aHead);
    printf("管理员账号添加成功！\n");
    wait();
}


