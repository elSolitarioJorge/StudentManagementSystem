#include "StudentManagementSystem.h"

void writeAccountToFile(const AccNode* aHead) {
    FILE* fp = fopen("accounts.bin", "wb");
    if (fp == NULL) {
        perror("Error opening accounts.bin");
        return;
    }
    AccNode* cur = aHead->next;
    while(cur != NULL) {
        fwrite(&(cur->account), sizeof(Account), 1, fp);
        cur = cur->next;
    }
    printf("账户信息写入成功！\n");
    fclose(fp);
}

void writeStudentToFile(const StuNode* sHead) {
    FILE* fp = fopen("students.bin", "wb");
    if (fp == NULL) {
        perror("Error opening students.bin");
        return;
    }
    StuNode* cur = sHead->next;
    while(cur != NULL) {
        fwrite(&(cur->student), sizeof(Student), 1, fp);
        cur = cur->next;
    }
    printf("学生信息写入成功！\n");
    fclose(fp);
}

void writeTodoToFile(const TNode* tHead) {
    FILE* fp = fopen("todo.bin", "wb");
    if (fp == NULL) {
        perror("Error opening todo.bin");
        return;
    }
    TNode* cur = tHead->next;
    while(cur != NULL) {
        fwrite(cur->userName, sizeof(cur->userName), 1, fp);
        cur = cur->next;
    }
    printf("代办信息写入成功！\n");
    fclose(fp);
}

void readAccountFromFile(AccNode* aHead) {
    FILE* fp = fopen("accounts.bin", "rb");
    if(fp == NULL) {
        perror("Error opening accounts.bin");
        return;
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, fp) == 1) {
        AccNode* newAccNode = createAccountNode();
        newAccNode->account = account;
        appendAccountNodeAtTail(aHead, newAccNode);
    }
    printf("账户信息读取成功！\n");
    fclose(fp);
}

void readStudentFromFile(StuNode* sHead) {
    FILE* fp = fopen("students.bin", "rb");
    if(fp == NULL) {
        perror("Error opening students.bin");
        return;
    }
    Student student;
    while(fread(&student, sizeof(Student), 1, fp) == 1) {
        StuNode* newStuNode = createStudentNode();
        newStuNode->student = student;
        appendStudentNodeAtTail(sHead, newStuNode);
    }
    printf("学生信息读取成功\n");
    fclose(fp);
}

void readTodoFromFile(TNode* tHead) {
    FILE* fp = fopen("todo.bin", "rb");
    if(fp == NULL) {
        perror("Error opening todo.bin");
        return;
    }
    char userName[20];
    while(fread(userName, sizeof(userName), 1, fp) == 1) {
        TNode* newTNode = createTodoNode();
        strcpy(newTNode->userName, userName);
        appendTodoNodeAtTail(tHead, newTNode);
    }
    printf("代办信息读取成功\n");
    fclose(fp);
}

void importStudentToFile(const char* csvFileName, const char* binFileName) {
    FILE* csv = fopen(csvFileName, "r");
    FILE* bin = fopen(binFileName, "wb");
    if(!csv || !bin) {
        perror("Error opening file");
        return;
    }
    char line[200];
    fgets(line, sizeof(line), csv); //跳过第一行标题
    while(fgets(line, sizeof(line), csv)) {
        Student student;
        sscanf(line, "%[^,],%[^,],%d,%f,%f,%f,%f,%f,%f,%f,%f",
            student.id, student.name, &student.class, &student.score.chinese, &student.score.math,&student.score.english,
            &student.score.physics, &student.score.chemistry, &student.score.biology, &student.score.lizong, &student.score.total);
        fwrite(&student, sizeof(Student), 1, bin);
    }
    fclose(csv);
    fclose(bin);
    printf("学生信息导入成功!\n");
}

void importAccountToFile(const char* csvFileName, const char* binFileName) {
    FILE* csv = fopen(csvFileName, "r");
    FILE* bin = fopen(binFileName, "wb");
    if(!csv || !bin) {
        perror("Error opening file");
        return;
    }
    char line[100];
    fgets(line, sizeof(line), csv); //跳过第一行标题
    while(fgets(line, sizeof(line), csv)) {
        Account account;
        sscanf(line, "%[^,],%[^,],%c", account.userName, account.password, &account.role);
        fwrite(&account, sizeof(Account), 1, bin);
    }
    fclose(csv);
    fclose(bin);
    printf("账户信息导入成功!\n");
}