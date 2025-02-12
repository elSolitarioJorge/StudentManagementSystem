#include "StudentManagementSystem.h"

int main() {
    accNode* aHead = createAccountNode();
    stuNode* sHead = createStudentNode();
    readAccountFromFile(aHead);
    readStudentFromFile(sHead);
    pressAnyKeyToContinue();
    system("cls");
    mainMenu(aHead, sHead);
    freeAccountList(aHead);
    freeStudentList(sHead);
    return 0;
}

void addAdmin(accNode* aHead) {
    accNode* admin = (accNode*)malloc(sizeof(accNode));
    if(admin == NULL) {
        perror("Error allocating memory");
        pressAnyKeyToContinue();
        return;
    }
    admin->next = aHead->next;
    aHead->next = admin;
    strcpy(admin->account.userName, "admin");
    strcpy(admin->account.password, "111111");
    admin->account.role = 'A';
    writeAccountToFile(aHead);
    printf("管理员账号添加成功！\n");
    pressAnyKeyToContinue();
}

void clearInputBuffer() {
    while(getchar() != '\n');
}

void pressAnyKeyToContinue() {
    printf("请按任意键继续...\n");
    _getch();
}

int getValidInput(int min, int max) {
    int input;
    char monitoring; //用于监视输入  monitor  v.监测;监视;监控
    if(scanf("%d%c", &input, &monitoring) != 2 || monitoring != '\n') {
        clearInputBuffer();//清空输入缓冲区
        return -1;
    }
    if(input < min || input > max) {
        return -1;
    }
    return input;
}

void getStringInput(const char* prompt, char* input, int size) {
    printf("%s", prompt);
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';
}

float getFloatInput(const char* prompt) {
    float input;
    while(1) {
        printf("%s", prompt);
        if(scanf("%f", &input) == 1) {
            clearInputBuffer();
            return input;
        } else {
            clearInputBuffer();
            fprintf(stderr, "输入错误，请重新输入！\n");
        }
    }
}

accNode* createAccountNode() {
    accNode* newAccNode = (accNode*)malloc(sizeof(accNode));
    if(newAccNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newAccNode->next = NULL;
    return newAccNode;
}

stuNode* createStudentNode() {
    stuNode* newStuNode = (stuNode*)malloc(sizeof(stuNode));
    if(newStuNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newStuNode->prev = NULL;
    newStuNode->next = NULL;
    return newStuNode;
}

void appendAccountNodeAtTail(accNode* aHead, accNode* newAccNode) {
    accNode* tail = aHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newAccNode->next = NULL;
    tail->next = newAccNode;
}

void appendStudentNodeAtTail(stuNode* sHead, stuNode* newStuNode) {
    stuNode* tail = sHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newStuNode->next = NULL;
    newStuNode->prev = tail;
    tail->next = newStuNode;
}

void freeAccountList(accNode* aHead) {
    accNode* cur = aHead;
    while(cur != NULL) {
        accNode* del = cur;
        cur = cur->next;
        free(del);
    }
}

void freeStudentList(stuNode* sHead) {
    stuNode* cur = sHead;
    while(cur != NULL) {
        stuNode* del = cur;
        cur = cur->next;
        free(del);
    }
}
