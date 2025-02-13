//
// Created by yaoheng on 25-2-5.
//
#include "StudentManagementSystem.h"

void teacherMenu(stuNode* sHead) {
    int choice = 0;

    do {
        system("cls");
        displayTeacherMenu();

        choice = getValidInput(0, 3);
        switch(choice) {
            case 0:
                return;
            case 1:
                addStudent(sHead);
                break;
            case 2:
                deleteStudent(sHead);
                break;
            case 3:
                pagePrintingStudent(sHead, 1);
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
    printf("3.查看所有学生信息\n");
    printf("0.返回上一级\n");
}

void addStudent(stuNode* sHead) {
    system("cls");
    char name[50] = "";
    char id[20] = "";
    printf("---添加学生信息---\n");
    getStringInput("学号：", id, sizeof(id));
    getStringInput("姓名：", name, sizeof(name));
    printf("班级：");
    int class = getValidInput(1, 25);
    if(class == -1) {
        printf("输入不合法（直接输入学生所在班级的数字即可），添加学生失败！\n");
        pressAnyKeyToContinue();
        return;
    }
    float chinese = getFloatInput("语文成绩：");
    float math = getFloatInput("数学成绩：");
    float english = getFloatInput("英语成绩：");
    float physics = getFloatInput("物理成绩：");
    float chemistry = getFloatInput("化学成绩：");
    float biology = getFloatInput("生物成绩：");
    float total = chinese + math + english + physics + chemistry + biology;
    stuNode* newStudent = createStudentNode();
    strcpy(newStudent->student.id, id);
    strcpy(newStudent->student.name, name);
    newStudent->student.class = class;
    newStudent->student.score.chinese = chinese;
    newStudent->student.score.math = math;
    newStudent->student.score.english = english;
    newStudent->student.score.physics = physics;
    newStudent->student.score.chemistry = chemistry;
    newStudent->student.score.biology = biology;
    newStudent->student.score.total = total;
    appendStudentNodeAtTail(sHead, newStudent);
    writeStudentToFile(sHead);
    printf("学生信息添加成功！\n");
    pressAnyKeyToContinue();
}

void deleteStudent(stuNode* sHead) {
    system("cls");
    char name[50] = "";
    stuNode* cur = sHead->next;
    getStringInput("请输入要删除的学生的姓名：", name, sizeof(name));
    while(cur != NULL) {
        if(strcmp(cur->student.name, name) == 0) {
            char choice;
            printf("是否确认删除此账户(Y/N):");
            scanf(" %c", &choice);
            clearInputBuffer();
            if(choice == 'Y' || choice == 'y') {
                cur->prev->next = cur->next;
                if(cur->next != NULL) {
                    cur->next->prev = cur->prev;
                }
                free(cur);
                writeStudentToFile(sHead);
                printf("删除成功！！！\n");
                pressAnyKeyToContinue();
                return;
            } else {
                printf("已取消删除！！！\n");
                pressAnyKeyToContinue();
                return;
            }
        }
        cur = cur->next;
    }
    printf("没有找到该学生信息！！！\n");
    pressAnyKeyToContinue();
}
void pagePrintingStudent(const stuNode* sHead, int pageSize) {
    stuNode* cur = sHead->next;
    int size = 0;
    while(cur != NULL) {
        size++;
        cur = cur->next;
    }
    cur = sHead->next;
    int totalPages = (size + pageSize - 1) / pageSize;
    int currentPage = totalPages ? 1 : 0;
    while(1) {
        system("cls");
        printf("\t\t----2023-2024学年下学期高三2024届第四次模拟考试成绩单----\n\n");
        printf("学号\t\t姓名\t班级\t总分\t语文\t数学\t英语\t物理\t化学\t生物\n");
        int count = 0;
        stuNode* temp = cur;
        while(temp && count < pageSize) {
            printf("%-16s%s\t%d班\t%-8g%-8g%-8g%-8g%-8g%-8g%g\n",
                temp->student.id, temp->student.name, temp->student.class,temp->student.score.total,
                temp->student.score.chinese, temp->student.score.math,temp->student.score.english,
                temp->student.score.physics, temp->student.score.chemistry, temp->student.score.biology);
            temp = temp->next;
            count++;
        }
        printf("\n\n\t\t\t\t--------Page(%d/%d)--------\n\n", currentPage, totalPages);
        if (currentPage < totalPages) {
            printf("按 N 查看下一页，");
        }
        if (currentPage > 1) {
            printf("按 B 返回上一页，");
        }
        printf("按 Q 退出：");
        int command = _getch();
        if((command == 'N' || command == 'n') && currentPage < totalPages) {
            for(int i = 0; i < pageSize && cur; i++) {
                cur = cur->next;
            }
            currentPage++;
        } else if((command == 'B' || command == 'b') && currentPage > 1) {
            for(int i = 0; i < pageSize && cur != sHead->next && cur; i++) {
                cur = cur->prev;
            }
            currentPage--;
        } else if(command == 'Q' || command == 'q') {
            break;
        }
    }
}