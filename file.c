#include "student_management_system.h"
// 将账户信息写入文件
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
// 将学生信息写入文件
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
// 将代办信息写入文件
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
// 从文件中读取账户信息
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
// 从文件中读取学生信息
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
// 从文件中读取代办信息
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
// 将学生信息从csv文件导入到二进制文件
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
    printf("学生信息导入成功!\n");
    fclose(csv);
    fclose(bin);
}
// 将账户信息从csv文件导入到二进制文件
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
        sscanf(line, "%[^,],%[^,],%c", account.userName, account.name, &account.role);
        const char* initPass = account.role == 'S' ? account.userName + strlen(account.userName) - 6 : "111111";
        RAND_bytes(account.salt, SALT_LENGTH);
        hashPassword(initPass, account.salt, account.passwordHash);
        fwrite(&account, sizeof(Account), 1, bin);
    }
    printf("账户信息导入成功!\n");
    fclose(csv);
    fclose(bin);
}
// 将学生信息导出到csv文件
void exportStudentToFile(const char* binFileName, const char* csvFileName) {
    system("cls");
    FILE* bin = fopen(binFileName, "rb");
    FILE* csv = fopen(csvFileName, "wb, ccs=UTF-8");
    if(!bin || !csv) {
        perror("Error opening file");
        pressAnyKeyToContinue();
        return;
    }
    unsigned char bom[] = {0xEF, 0xBB, 0xBF}; // UTF-8 BOM
    fwrite(bom, 1, sizeof(bom), csv); // 写入 BOM

    fprintf(csv, "学号,姓名,班级,语文,数学,英语,物理,化学,生物,理综,总分\n");
    Student student;
    int count = 0;
    while(fread(&student, sizeof(Student), 1, bin) == 1) {
        fprintf(csv, "%s,%s,%d,%g,%g,%g,%g,%g,%g,%g,%g\n",
            student.id, student.name, student.class, student.score.chinese, student.score.math,student.score.english,
            student.score.physics, student.score.chemistry, student.score.biology, student.score.lizong, student.score.total);
        count++;
    }
    if(ferror(bin)) {
        printf("Error reading from file\n");
    }
    printf("成功导出 %d 条学生信息到 %s !\n", count, csvFileName);
    fclose(bin);
    fclose(csv);
    pressAnyKeyToContinue();
}