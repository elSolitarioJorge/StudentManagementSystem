#include "StudentManagementSystem.h"

int main() {
    AccNode* aHead = createAccountNode();
    StuNode* sHead = createStudentNode();
    TNode* tHead = createTodoNode();
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

void addAdmin(AccNode* aHead) {
    AccNode* admin = (AccNode*)malloc(sizeof(AccNode));
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

AccNode* createAccountNode() {
    AccNode* newAccNode = (AccNode*)malloc(sizeof(AccNode));
    if(newAccNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newAccNode->next = NULL;
    return newAccNode;
}

StuNode* createStudentNode() {
    StuNode* newStuNode = (StuNode*)malloc(sizeof(StuNode));
    if(newStuNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newStuNode->prev = NULL;
    newStuNode->next = NULL;
    return newStuNode;
}

TNode* createTodoNode() {
    TNode* newTNode = (TNode*)malloc(sizeof(TNode));
    if(newTNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newTNode->next = NULL;
    return newTNode;
}

void appendAccountNodeAtTail(AccNode* aHead, AccNode* newAccNode) {
    AccNode* tail = aHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newAccNode->next = NULL;
    tail->next = newAccNode;
}

void appendStudentNodeAtTail(StuNode* sHead, StuNode* newStuNode) {
    StuNode* tail = sHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newStuNode->next = NULL;
    newStuNode->prev = tail;
    tail->next = newStuNode;
}

void appendTodoNodeAtTail(TNode* tHead, TNode* newTNode) {
    TNode* tail = tHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newTNode->next = NULL;
    tail->next = newTNode;
}

void freeAccountList(AccNode* aHead) {
    AccNode* cur = aHead;
    while(cur != NULL) {
        AccNode* del = cur;
        cur = cur->next;
        free(del);
    }
}

void freeStudentList(StuNode* sHead) {
    StuNode* cur = sHead;
    while(cur != NULL) {
        StuNode* del = cur;
        cur = cur->next;
        free(del);
    }
}

StuNode* copyStudentList(StuNode* head) {
    StuNode dummy;
    StuNode* tail = &dummy;
    while(head != NULL) {
        StuNode* newStuNode = createStudentNode();
        newStuNode->student = head->student;
        newStuNode->prev = tail;
        tail->next = newStuNode;
        tail = tail->next;
        head = head->next;
    }
    return dummy.next;
}