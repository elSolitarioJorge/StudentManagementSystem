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
    printf("写入成功\n");
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
    printf("写入成功\n");
    fclose(fp);
}

void readAccountFromFile(accNode* aHead) {
    FILE* fp = fopen("account.txt", "rb");
    if(fp == NULL) {
        perror("Error opening account.txt");
        return;
    }
    accNode* tail = aHead;
    Acc account;
    while(fread(&account, sizeof(Acc), 1, fp) == 1) {
        accNode* newAccNode = (accNode*)malloc(sizeof(accNode));
        if(newAccNode == NULL) {
            perror("Error allocating memory");
            fclose(fp);
            return;
        }
        newAccNode->account = account;
        newAccNode->next = NULL;
        tail->next = newAccNode;
        tail = newAccNode;
    }
    printf("读取成功\n");
    fclose(fp);
}

void readStudentFromFile(stuNode* sHead) {
    FILE* fp = fopen("student.txt", "rb");
    if(fp == NULL) {
        perror("Error opening student.txt");
        return;
    }
    accNode* tail = sHead;
    Acc account;
    while(fread(&account, sizeof(Stu), 1, fp) == 1) {
        accNode* newStuNode = (accNode*)malloc(sizeof(stuNode));
        if(newStuNode == NULL) {
            perror("Error allocating memory");
            fclose(fp);
            return;
        }
        newStuNode->account = account;
        newStuNode->next = NULL;
        tail->next = newStuNode;
        tail = newStuNode;
    }
    printf("读取成功\n");
    fclose(fp);
}

