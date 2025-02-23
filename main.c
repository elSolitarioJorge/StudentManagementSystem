#include "student_management_system.h"

int main() {
    AccNode* aHead = createAccountNode();
    StuNode* sHead = createStudentNode();
    TNode* tHead = createTodoNode();
    readAccountFromFile(aHead);
    readStudentFromFile(sHead);
    readTodoFromFile(tHead);
    system("cls");
    showLoading();
    pressAnyKeyToContinue();
    system("cls");
    mainMenu(aHead, sHead, tHead);
    freeAccountList(aHead);
    freeStudentList(sHead);
    return 0;
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

StuNode* copyStudentByClass(const StuNode* sHead, int class) {
    StuNode dummy;
    StuNode* tail = &dummy;
    StuNode* cur = sHead->next;
    while(cur != NULL) {
        if(class == 0 || cur->student.class == class) {
            StuNode* newStuNode = createStudentNode();
            newStuNode->student = cur->student;
            newStuNode->prev = tail;
            tail->next = newStuNode;
            tail = tail->next;
        }
        cur = cur->next;
    }
    return dummy.next;
}

void showLoading() {
    const char* frames[] = {"🌑 ","🌒 ","🌓 ","🌔 ","🌕 ","🌖 ","🌗 ","🌘 "};
    for(int i = 0; i < 8; i++) {
        printf("\r%s 加载中...", frames[i % 8]);
        fflush(stdout);
        Sleep(250);
    }
    printf("\r✅ 加载完成! \n");
}

// 将控制台窗口滚动到顶部(需以管理员权限运行)
void scrollConsoleToTop() {
    // 获取标准输出句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // 1. 获取当前控制台信息
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        printf("无法获取控制台信息，错误代码：%d\n", GetLastError());
        return;
    }

    // 2. 计算新窗口位置（移动到缓冲区顶部）
    SMALL_RECT newWindow = {
        .Left = 0,
        .Top = 0,  // 关键：将窗口顶部对齐缓冲区顶部
        .Right = csbi.srWindow.Right,
        .Bottom = csbi.srWindow.Bottom - csbi.srWindow.Top
    };

    // 3. 设置新的窗口显示区域
    if (!SetConsoleWindowInfo(hConsole, TRUE, &newWindow)) {
        printf("无法滚动到顶部，错误代码：%d\n", GetLastError());
    }
}