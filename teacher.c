//
// Created by yaoheng on 25-2-5.
//
#include "StudentManagementSystem.h"

void teacherMenu(stuNode* sHead) {
    int choice = 0;

    do {
        system("cls");
        displayTeacherMenu();

        choice = getValidInput(0, 2);
        switch(choice) {
            case 0:
                return;
            case 1:
                addStudent(sHead);
                break;
            case 2:
                //deleteStudent(sHead);
                break;
            default :
                printf("输入不合法，请输入0~2之间的整数\n");
                pressAnyKeyToContinue();
                break;
        }
    } while(choice);
}

void displayTeacherMenu() {
    printf("欢迎教师登录!\n");
    printf("1.添加学生信息\n");
    printf("2.删除学生信息\n");
    printf("0.返回上一级\n");
}

void addStudent(stuNode* sHead) {
    system("cls");
    char name[50] = "";
    char id[20] = "";
    printf("---添加学生信息---\n");
    getStringInput("学号：", id, sizeof(id));
    getStringInput("姓名：", name, sizeof(name));
    float chinese = getFloatInput("语文成绩：");
    float math = getFloatInput("数学成绩：");
    float english = getFloatInput("英语成绩：");
}