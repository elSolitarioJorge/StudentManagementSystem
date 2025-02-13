//
// Created by yaoheng on 25-2-5.
//
#include "StudentManagementSystem.h"

void studentMenu(stuNode* sHead, const char* inputUserName) {
    int choice = 0;
    stuNode* myself = sHead->next;
    while(myself != NULL) {
        if(strcmp(myself->student.id, inputUserName) == 0) {
            break;
        }
        myself = myself->next;
    }
    if(myself == NULL) {
        system("cls");
        printf("用户不存在\n");
        pressAnyKeyToContinue();
        return;
    }
    do {
        system("cls");
        displayStudentMenu();
        choice = getValidInput(0, 2);
        switch(choice) {
            case 0:
                return;
            case 1:
                queryResults(myself);
                break;
            case 2:
                pagePrintingOneClassStudent(sHead, 10, myself->student.class);
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

void queryResults(const stuNode* myself) {
    system("cls");
    printf("学号：\t%s\n", myself->student.id);
    printf("姓名：\t%s\n", myself->student.name);
    printf("班级：\t%d班\n", myself->student.class);
    printf("语文：\t%g\n", myself->student.score.chinese);
    printf("数学：\t%g\n", myself->student.score.math);
    printf("英语：\t%g\n", myself->student.score.english);
    printf("物理：\t%g\n", myself->student.score.physics);
    printf("化学：\t%g\n", myself->student.score.chemistry);
    printf("生物：\t%g\n", myself->student.score.biology);
    printf("总分：\t%g\n", myself->student.score.total);
    pressAnyKeyToContinue();
}

void pagePrintingOneClassStudent(const stuNode* sHead, int pageSize, int class) {
    stuNode* cur = sHead->next;
    int size = 0;
    while(cur != NULL) {
        if(cur->student.class == class) {
            size++;
        }
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
            if(temp->student.class == class) {
                printf("%-16s%s\t%d班\t%-8g%-8g%-8g%-8g%-8g%-8g%g\n",
                    temp->student.id, temp->student.name, temp->student.class,temp->student.score.total,
                    temp->student.score.chinese, temp->student.score.math,temp->student.score.english,
                    temp->student.score.physics, temp->student.score.chemistry, temp->student.score.biology);
                count++;
            }
            temp = temp->next;
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
            int i = 0;
            while(i < pageSize && cur) {
                if(cur->student.class == class) {
                    i++;
                }
                cur = cur->next;
            }
            currentPage++;
        } else if((command == 'B' || command == 'b') && currentPage > 1) {
            int i = 0;
            while(i < pageSize && cur != sHead->next && cur) {
                if(cur->student.class == class) {
                    i++;
                }
                cur = cur->prev;
            }
            currentPage--;
        } else if(command == 'Q' || command == 'q') {
            break;
        }
    }
}



