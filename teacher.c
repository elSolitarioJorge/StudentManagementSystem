//
// Created by yaoheng on 25-2-5.
//
#include "StudentManagementSystem.h"

void teacherMenu(stuNode* sHead) {
    int choice = 0;

    do {
        system("cls");
        displayTeacherMenu();

        choice = getValidInput(0, 6);
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
                changeStudent(sHead);
                break;
            case 4:
                findStudent(sHead);
                pressAnyKeyToContinue();
                break;
            case 5:
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
    printf("3.更改学生信息\n");
    printf("4.查询学生信息\n");
    printf("5.查看所有学生信息\n");
    printf("6.成绩分析\n");
    printf("0.返回上一级\n");
}

void enterScore(stuNode* student) {
    student->student.score.chinese = getFloatInput("语文成绩：");
    student->student.score.math = getFloatInput("数学成绩：");
    student->student.score.english = getFloatInput("英语成绩：");
    student->student.score.physics = getFloatInput("物理成绩：");
    student->student.score.chemistry = getFloatInput("化学成绩：");
    student->student.score.biology = getFloatInput("生物成绩：");
    student->student.score.lizong = student->student.score.physics + student->student.score.chemistry
                                       + student->student.score.biology;
    student->student.score.total = student->student.score.chinese + student->student.score.math
                                      + student->student.score.english + student->student.score.lizong;
}

void addStudent(stuNode* sHead) {
    system("cls");
    stuNode* newStudent = createStudentNode();
    printf("---添加学生信息---\n");
    getStringInput("学号：", newStudent->student.id, sizeof(newStudent->student.id));
    getStringInput("姓名：", newStudent->student.name, sizeof(newStudent->student.name));
    printf("班级：");
    newStudent->student.class = getValidInput(1, 25);
    if(newStudent->student.class == -1) {
        printf("输入不合法（直接输入学生所在班级的数字即可），添加学生失败！\n");
        pressAnyKeyToContinue();
        return;
    }
    enterScore(newStudent);
    appendStudentNodeAtTail(sHead, newStudent);
    writeStudentToFile(sHead);
    printf("学生信息添加成功！\n");
    pressAnyKeyToContinue();
}

void deleteStudent(stuNode* sHead) {
    system("cls");
    stuNode* stu = findStudent(sHead);
    if(stu != NULL) {
        char choice;
        printf("是否确认删除此学生(Y/N):");
        scanf(" %c", &choice);
        clearInputBuffer();
        if(choice == 'Y' || choice == 'y') {
            stu->prev->next = stu->next;
            if(stu->next != NULL) {
                stu->next->prev = stu->prev;
            }
            free(stu);
            writeStudentToFile(sHead);
            printf("删除成功！！！\n");
        } else {
            printf("已取消删除！！！\n");
        }
    }
    pressAnyKeyToContinue();
}

void changeStudent(stuNode* sHead) {
    system("cls");
    stuNode* stu = findStudent(sHead);
    if(stu != NULL) {
        printf("请输入修改后的学生成绩：\n");
        enterScore(stu);
        writeStudentToFile(sHead);
        printf("学生信息修改成功！\n");
    }
    pressAnyKeyToContinue();
}

stuNode* findStudent(stuNode* sHead) {
    system("cls");
    stuNode* cur = sHead->next;
    char str[50];
    getStringInput("请输入学生姓名或学号：", str, sizeof(str));
    while(cur != NULL) {
        if(strcmp(cur->student.name, str) == 0 || strcmp(cur->student.id, str) == 0) {
            printf("该学生的信息如下：\n");
            printf("学号\t\t姓名\t班级\t语文\t数学\t英语\t理综\t物理\t化学\t生物\t总分\n");
            printf("%-16s%s\t%-8d%-8g%-8g%-8g%-8g%-8g%-8g%-8g%g\n\n", cur->student.id, cur->student.name, cur->student.class,
                cur->student.score.chinese, cur->student.score.math, cur->student.score.english, cur->student.score.lizong,
                cur->student.score.physics, cur->student.score.chemistry, cur->student.score.biology, cur->student.score.total);
            return cur;
        }
        cur = cur->next;
    }
    printf("没有找到该学生信息！！！\n");
    return NULL;
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
        printf("\t\t-----2023-2024学年下学期高三2024届第四次模拟考试成绩单-----\n\n");
        printf("学号\t\t姓名\t班级\t语文\t数学\t英语\t理综\t物理\t化学\t生物\t总分\n");
        int count = 0;
        stuNode* temp = cur;
        while(temp && count < pageSize) {
            printf("%-16s%s\t%-8d%-8g%-8g%-8g%-8g%-8g%-8g%-8g%g\n",temp->student.id, temp->student.name, temp->student.class,
                temp->student.score.chinese, temp->student.score.math, temp->student.score.english, temp->student.score.lizong,
                temp->student.score.physics, temp->student.score.chemistry, temp->student.score.biology, temp->student.score.total);
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

float compareStudents(const stuNode* s1, const stuNode* s2, int criteria) {
    switch(criteria) {
        case 0:
            return s1->student.score.total - s2->student.score.total;
        case 1:
            return s1->student.score.chinese - s2->student.score.chinese;
        case 2:
            return s1->student.score.math - s2->student.score.math;
        case 3:
            return s1->student.score.english - s2->student.score.english;
        case 4:
            return s1->student.score.lizong - s2->student.score.lizong;
        case 5:
            return s1->student.score.physics - s2->student.score.physics;
        case 6:
            return s1->student.score.chemistry - s2->student.score.chemistry;
        case 7:
            return s1->student.score.biology - s2->student.score.biology;
        default:
            return 0;
    }
}

stuNode* mergeStudentByCriteria(stuNode* head1, stuNode* head2, int criteria) {
    stuNode* mergeHead = NULL;
    if(head1 == NULL) {
        return head2;
    }
    if(head2 == NULL) {
        return head1;
    }
    if(compareStudents(head1, head2, criteria) >= 0.0f) {
        mergeHead = head1;
        mergeHead->next = mergeStudentByCriteria(head1->next, head2, criteria);
    } else {
        mergeHead = head2;
        mergeHead->next = mergeStudentByCriteria(head1, head2->next, criteria);
    }
    return mergeHead;
}

stuNode* splitStudent(stuNode* head) {
    stuNode* fast = head->next;
    stuNode* slow = head;
    while(fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    stuNode* secondHalf = slow->next;
    slow->next = NULL;
    return secondHalf;
}

stuNode*  mergeSortStudentByCriteria(stuNode* head, int criteria) {
    if(head == NULL || head->next == NULL) {
        return head;
    }
    stuNode* secondHalf = splitStudent(head);
    head = mergeSortStudentByCriteria(head, criteria);
    secondHalf = mergeSortStudentByCriteria(secondHalf, criteria);
    return mergeStudentByCriteria(head, secondHalf, criteria);
}