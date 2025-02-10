#include "StudentManagementSystem.h"

void writeAccountToFile(const accNode* aHead) {
    FILE* fp = fopen("account.txt", "wb");
    if (fp == NULL) {
        perror("Error opening account.txt");
        return;
    }
    accNode* cur = aHead->next;
    while(cur != NULL) {
        if(fwrite(cur, sizeof(accNode), 1, fp) != 1) {
            perror("Error writing to account.txt");
            fclose(fp);
            return;
        }
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
        if(fwrite(cur, sizeof(stuNode), 1, fp) != 1) {
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
    accNode* cur = aHead;
    while(!feof(fp)) {
        accNode* new = (accNode*)malloc(sizeof(accNode));
        if(new == NULL) {
            perror("Error allocating memory");
            fclose(fp);
            return;
        }
        if(fread(new, sizeof(accNode), 1, fp) != 1) {
            free(new);
            break;
        }
        new->next = NULL;
        cur->next = new;
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
    stuNode* cur = sHead;
    while(!feof(fp)) {
        stuNode* new = (stuNode*)malloc(sizeof(stuNode));
        if(new == NULL) {
            perror("Error allocating memory");
            fclose(fp);
            return;
        }
        if(fread(new, sizeof(stuNode), 1, fp) != 1) {
            free(new);
            break;
        }
        new->next = NULL;
        cur->next = new;
    }
    printf("读取成功\n");
    fclose(fp);
}

