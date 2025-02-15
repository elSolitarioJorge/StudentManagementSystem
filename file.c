#include "StudentManagementSystem.h"

void writeAccountToFile(const accNode* aHead) {
    FILE* fp = fopen("account.txt", "wb");
    if (fp == NULL) {
        perror("Error opening account.txt");
        return;
    }
    accNode* cur = aHead->next;
    while(cur != NULL) {
        fwrite(&(cur->account), sizeof(Acc), 1, fp);
        cur = cur->next;
    }
    printf("账户信息写入成功\n");
    fclose(fp);
}

void writeStudentToFile(const stuNode* sHead) {
    FILE* fp = fopen("student.txt", "wb");
    if (fp == NULL) {
        perror("Error opening student.txt");
        return;
    }
    stuNode* cur = sHead->next;
    while(cur != NULL) {
        if(fwrite(&(cur->student), sizeof(Stu), 1, fp) != 1) {
            perror("Error writing to student.txt");
            fclose(fp);
            return;
        }
        cur = cur->next;
    }
    printf("学生信息写入成功\n");
    fclose(fp);
}

void writeTodoToFile(const tNode* tHead) {
    FILE* fp = fopen("todo.txt", "wb");
    if (fp == NULL) {
        perror("Error opening todo.txt");
        return;
    }
    tNode* cur = tHead->next;
    while(cur != NULL) {
        if(fwrite(cur->userName, sizeof(cur->userName), 1, fp) != 1) {
            perror("Error writing to todo.txt");
            fclose(fp);
            return;
        }
        cur = cur->next;
    }
    printf("代办信息写入成功\n");
    fclose(fp);
}

void readAccountFromFile(accNode* aHead) {
    FILE* fp = fopen("account.txt", "rb");
    if(fp == NULL) {
        perror("Error opening account.txt");
        return;
    }
    Acc account;
    while(fread(&account, sizeof(Acc), 1, fp) == 1) {
        accNode* newAccNode = createAccountNode();
        newAccNode->account = account;
        appendAccountNodeAtTail(aHead, newAccNode);
    }
    printf("账户信息读取成功\n");
    fclose(fp);
}

void readStudentFromFile(stuNode* sHead) {
    FILE* fp = fopen("student.txt", "rb");
    if(fp == NULL) {
        perror("Error opening student.txt");
        return;
    }
    Stu student;
    while(fread(&student, sizeof(Stu), 1, fp) == 1) {
        stuNode* newStuNode = createStudentNode();
        newStuNode->student = student;
        appendStudentNodeAtTail(sHead, newStuNode);
    }
    printf("学生信息读取成功\n");
    fclose(fp);
}

void readTodoFromFile(tNode* tHead) {
    FILE* fp = fopen("todo.txt", "rb");
    if(fp == NULL) {
        perror("Error opening todo.txt");
        return;
    }
    char userName[20];
    while(fread(userName, sizeof(userName), 1, fp) == 1) {
        tNode* newTNode = createTodoNode();
        strcpy(newTNode->userName, userName);
        appendTodoNodeAtTail(tHead, newTNode);
    }
    printf("代办信息读取成功\n");
    fclose(fp);
}