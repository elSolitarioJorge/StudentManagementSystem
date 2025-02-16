#include "StudentManagementSystem.h"

int main() {
    accNode* aHead = createAccountNode();
    stuNode* sHead = createStudentNode();
    tNode* tHead = createTodoNode();
    readAccountFromFile(aHead);
    readStudentFromFile(sHead);
    readTodoFromFile(tHead);
    pressAnyKeyToContinue();
    system("cls");
    mainMenu(aHead, sHead, tHead);
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

void pressAnyKeyToContinue() {
    printf("请按任意键继续...\n");
    _getch();
}

void clearInputBuffer() {
    while(getchar() != '\n');
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
    if(size == 0) return;
    printf("%s", prompt);
    if(fgets(input, size, stdin) == NULL) {
        input[0] = '\0';
        return;
    }
    char* end = strchr(input, '\n');
    if(end) {
        *end = '\0';
    } else {
        clearInputBuffer();
    }
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

tNode* createTodoNode() {
    tNode* newTNode = (tNode*)malloc(sizeof(tNode));
    if(newTNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newTNode->next = NULL;
    return newTNode;
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

void appendTodoNodeAtTail(tNode* tHead, tNode* newTNode) {
    tNode* tail = tHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newTNode->next = NULL;
    tail->next = newTNode;
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

stuNode* copyStudentList(stuNode* head) {
    stuNode dummy;
    stuNode* tail = &dummy;
    while(head != NULL) {
        stuNode* newStuNode = createStudentNode();
        newStuNode->student = head->student;
        newStuNode->prev = tail;
        tail->next = newStuNode;
        tail = tail->next;
        head = head->next;
    }
    return dummy.next;
}