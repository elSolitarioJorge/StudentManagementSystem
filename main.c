#include "student_management_system.h"

int main() {
    AccNode* aHead = createAccountNode();
    StuNode* sHead = createStudentNode();
    TNode* tHead = createTodoNode();
    readData(aHead, sHead, tHead);

    showLoading();
    system("cls");

    mainMenu(aHead, sHead, tHead);

    freeList(aHead, sHead, tHead);
    return 0;
}
// 从文件读取数据
void readData(AccNode* aHead, StuNode* sHead, TNode* tHead) {
    readAccountFromFile(aHead);    // 从文件读取账户信息
    readStudentFromFile(sHead);    // 从文件读取学生信息
    readTodoFromFile(tHead);       // 从文件读取代办
    system("cls");        // 清屏
}
// 释放链表
void freeList(AccNode* aHead, StuNode* sHead, TNode* tHead) {
    freeAccountList(aHead);    // 释放账户链表
    freeStudentList(sHead);    // 释放学生链表
    freeTodoList(tHead);       // 释放代办链表
}
// 请按任意键继续
void pressAnyKeyToContinue() {
    printf("请按任意键继续...\n");
    _getch();      // 读取用户按键操作
}
// 清空缓冲区
void clearInputBuffer() {
    while(getchar() != '\n');
}
// 获取一个有效整数输入，min~max之间的整数
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
// 获取一个有效字符串输入
void getStringInput(const char* prompt, char* input, int size) {
    if(size == 0) return;      // 如果size为0，直接返回
    printf("%s", prompt);    // 输出提示信息
    if(fgets(input, size, stdin) == NULL) {
        input[0] = '\0';   // 如果没有任何输入，将第一个字符设为'\0'，防止清空缓冲区时卡住
        return;
    }  // 读取用户输入
    char* end = strchr(input, '\n');  // 查找并返回'\n'的位置
    if(end) {
        *end = '\0';  // 将'\n'替换为'\0'
    } else {
        clearInputBuffer();   // 如果输入超出限制，需清空缓冲区，防止影响后续程序运行
    }
}
// 获取一个浮点数输入
float getFloatInput(const char* prompt) {
    float input;
    while(1) {
        printf("%s", prompt);
        if(scanf("%f", &input) == 1) {
            clearInputBuffer();
            return input;
        } else {
            clearInputBuffer();
            fprintf(stderr, "输入错误，请重新输入!\n");
        }
    }
}
// 创建账户节点（链表）
AccNode* createAccountNode() {
    AccNode* newAccNode = (AccNode*)malloc(sizeof(AccNode));
    if(newAccNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newAccNode->next = NULL;
    return newAccNode;
}
// 创建学生节点（双向链表）
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
// 创建代办节点（链表）
TNode* createTodoNode() {
    TNode* newTNode = (TNode*)malloc(sizeof(TNode));
    if(newTNode == NULL) {
        perror("Error allocating memory");
        exit(-1);
    }
    newTNode->next = NULL;
    return newTNode;
}
// 将账户节点添加到账户链表尾部
void appendAccountNodeAtTail(AccNode* aHead, AccNode* newAccNode) {
    AccNode* tail = aHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newAccNode->next = NULL;
    tail->next = newAccNode;
}
// 将学生节点添加到学生链表尾部
void appendStudentNodeAtTail(StuNode* sHead, StuNode* newStuNode) {
    StuNode* tail = sHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newStuNode->next = NULL;
    newStuNode->prev = tail;
    tail->next = newStuNode;
}
// 将代办节点添加到代办链表尾部
void appendTodoNodeAtTail(TNode* tHead, TNode* newTNode) {
    TNode* tail = tHead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    newTNode->next = NULL;
    tail->next = newTNode;
}
// 释放账户链表
void freeAccountList(AccNode* aHead) {
    AccNode* cur = aHead;
    while(cur != NULL) {
        AccNode* del = cur;
        cur = cur->next;
        free(del);
    }
}
// 释放学生链表
void freeStudentList(StuNode* sHead) {
    StuNode* cur = sHead;
    while(cur != NULL) {
        StuNode* del = cur;
        cur = cur->next;
        free(del);
    }
}
// 释放代办链表
void freeTodoList(TNode* tHead) {
    TNode* cur = tHead;
    while(cur != NULL) {
        TNode* del = cur;
        cur = cur->next;
        free(del);
    }
}
// 根据班级复制学生链表
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
// 展示加载页面
void showLoading() {
    const char* frames[] = {"🌑 ","🌒 ","🌓 ","🌔 ","🌕 ","🌖 ","🌗 ","🌘 "};
    for(int i = 0; i < 8; i++) {
        printf("\r%s 加载中...", frames[i % 8]);
        fflush(stdout);
        Sleep(250);
    }
    printf("\r✅ 加载完成! \n");
    pressAnyKeyToContinue();
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