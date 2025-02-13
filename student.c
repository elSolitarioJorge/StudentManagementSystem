//
// Created by yaoheng on 25-2-5.
//
#include "StudentManagementSystem.h"

void studentMenu(stuNode* sHead, const char* inputUserName) {
    int choice = 0;
    do {
        system("cls");
        displayStudentMenu();
        choice = getValidInput(0, 1);
        switch(choice) {
            case 0:
                return;
            case 1:
                queryResults(sHead, inputUserName);
                break;
            default:
                break;
        }
    }while(choice != 0);
}
void displayStudentMenu() {
    printf("0.退出\n");
    printf("1.成绩查询\n");
    printf("2.查询本班成绩\n");
    printf("3.成绩分析\n");
    printf("4.成绩申诉\n");
    printf("5.修改密码\n");
    printf("6.返回上一级\n");
}

void queryResults(const stuNode* sHead, const char* inputUserName) {
    system("cls");
    stuNode* cur = sHead->next;;
    while(cur != NULL) {
        if(strcmp(cur->student.id, inputUserName) == 0) {
            printf("学号：\t%s\n", cur->student.id);
            printf("姓名：\t%s\n", cur->student.name);
            printf("班级：\t%d班\n", cur->student.class);
            printf("总分：\t%g\n", cur->student.score.total);
            printf("语文：\t%g\n", cur->student.score.chinese);
            printf("数学：\t%g\n", cur->student.score.math);
            printf("英语：\t%g\n", cur->student.score.english);
            printf("物理：\t%g\n", cur->student.score.physics);
            printf("化学：\t%g\n", cur->student.score.chemistry);
            printf("生物：\t%g\n", cur->student.score.biology);
            break;
        }
        cur = cur->next;;
    }
    pressAnyKeyToContinue();
}





