#include "StudentManagementSystem.h"

void teacherMenu(StuNode* sHead, char* password) {
    int choice = 0;

    while(1) {
        system("cls");
        displayTeacherMenu();

        choice = _getch();
        switch(choice) {
            case '0':
                return;
            case '1':
                addStudent(sHead);
                break;
            case '2':
                deleteStudent(sHead);
                break;
            case '3':
                changeStudent(sHead);
                break;
            case '4':
                findStudent(sHead);
                pressAnyKeyToContinue();
                break;
            case '5':
                pagePrintingStudent(sHead, 30);
                break;
            case '6':
                analyzeScoreDistribution(sHead);
                break;
            case '7':
                changePassword(password);
                break;
            default :
                break;
        }
    }
}

void displayTeacherMenu() {
    printf("欢迎教师登录!\n");
    printf("1.添加学生信息\n");
    printf("2.删除学生信息\n");
    printf("3.更改学生信息\n");
    printf("4.查询学生信息\n");
    printf("5.查看所有学生信息\n");
    printf("6.成绩分析\n");
    printf("7.修改密码\n");
    printf("0.返回上一级\n");
}

void enterScore(StuNode* student) {
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

void addStudent(StuNode* sHead) {
    system("cls");
    StuNode* newStudent = createStudentNode();
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

void deleteStudent(StuNode* sHead) {
    StuNode* stu = findStudent(sHead);
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

void changeStudent(StuNode* sHead) {
    StuNode* stu = findStudent(sHead);
    if(stu != NULL) {
        printf("请输入修改后的学生成绩：\n");
        enterScore(stu);
        writeStudentToFile(sHead);
        printf("学生信息修改成功！\n");
    }
    pressAnyKeyToContinue();
}

StuNode* findStudent(StuNode* sHead) {
    system("cls");
    StuNode* cur = sHead->next;
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
    return cur;
}

void pagePrintingStudent(const StuNode* sHead, int pageSize) {
    StuNode* cur = sHead->next;
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
        StuNode* temp = cur;
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

float compareStudents(const StuNode* s1, const StuNode* s2, int criteria) {
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

StuNode* mergeStudentByCriteria(StuNode* head1, StuNode* head2, int criteria) {
    StuNode dummy;
    dummy.next = NULL;
    StuNode* tail = &dummy;
    while(head1 && head2) {
        if(compareStudents(head1, head2, criteria) >= 0) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }
    tail->next = head1 ? head1 : head2;
    return dummy.next;
}

StuNode* splitStudent(StuNode* head) {
    if(head == NULL || head->next == NULL) {
        return NULL;
    }
    StuNode* fast = head->next;
    StuNode* slow = head;
    while(fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    StuNode* secondHalf = slow->next;
    slow->next = NULL;
    return secondHalf;
}

StuNode*  mergeSortStudentByCriteria(StuNode* head, int criteria) {
    if(head == NULL || head->next == NULL) {
        return head;
    }
    StuNode* secondHalf = splitStudent(head);
    head = mergeSortStudentByCriteria(head, criteria);
    secondHalf = mergeSortStudentByCriteria(secondHalf, criteria);
    return mergeStudentByCriteria(head, secondHalf, criteria);
}

int getFullScoreBySubject(int subject) {
    if(subject == 0) return 750;
    if(subject == 4) return 300;
    if(subject == 5) return 110;
    if(subject == 6) return 100;
    if(subject == 7) return 90;
    return 150;
}

int getIntervalSize(int subject) {
    if(subject == 0) return 50;//总分
    if(subject == 4) return 20;//理综
    return 10;
}

void generateIntervalLabels(float minVal, float maxVal, int intervalSize, char labels [][20], int* count) {
    *count = 0;
    int start = ((int)minVal / intervalSize) * intervalSize;
    int end = ((int)maxVal / intervalSize + 1) * intervalSize;
    for(int i = end; i > start; i -= intervalSize) {
        snprintf(labels[*count], 20, "[%d-%d):", i - intervalSize, i);
        (*count)++;
    }
}

ScoreDistribution calculateDistribution(StuNode* sHead, int class, int subject) {
    ScoreDistribution current;
    current.class = class;
    current.subject = subject;
    current.minScore = 1000;
    current.maxScore = -1;
    current.maxCount = 0;
    current.totalCount = 0;
    current.intervalSize = getIntervalSize(subject);
    StuNode* cur = sHead->next;
    while(cur) {
        if(class == 0 || cur->student.class == class) {
            current.totalCount++;
            float score = getScoreBySubject(cur, subject);
            current.minScore = current.minScore < score ? current.minScore : score;
            current.maxScore = current.maxScore > score ? current.maxScore : score;
        }
        cur = cur->next;
    }
    int intervalStart = ((int)current.minScore / current.intervalSize) * current.intervalSize;
    int intervalEnd = ((int)current.maxScore / current.intervalSize + 1) * current.intervalSize;
    intervalEnd = intervalEnd < getFullScoreBySubject(subject) ? intervalEnd : getFullScoreBySubject(subject);
    current.intervalCount = (intervalEnd - intervalStart) / current.intervalSize;
    memset(current.intervals, 0, sizeof(current.intervals));
    cur = sHead->next;
    while(cur) {
        if(class == 0 || cur->student.class == class) {
            float score = getScoreBySubject(cur, subject);
            int index = ((int)score - intervalStart) / current.intervalSize;
            current.intervals[index]++;
            current.maxCount = current.maxCount > current.intervals[index] ? current.maxCount : current.intervals[index];
        }
        cur = cur->next;
    }
    return current;
}

void drawBarChart(const ScoreDistribution* current) {
    char labels[20][20];
    int labelCount = 0;
    generateIntervalLabels(current->minScore, current->maxScore, current->intervalSize, labels, &labelCount);
    printf("\n成绩分布: %g-%g\n", current->minScore, current->maxScore);
    for(int i = 0; i < labelCount; i++) {
        const int maxBarWidth = 100;
        int barLength = current->maxCount ? (current->intervals[i] * maxBarWidth) / current->maxCount : 0;
        printf("%-12s", labels[i]);
        for(int j=0; j<barLength; j++) {
            printf("■");
        }
        printf(" %d人", current->intervals[i]);
        printf("\n");
    }

}

void analyzeScoreDistribution(StuNode* sHead) {
    int currentClass = 0, currentSubject = 0;
    while(1) {
        system("cls");
        ScoreDistribution current = calculateDistribution(sHead, currentClass, currentSubject);
        printf("科目：%s  |  ", getSubjectName(currentSubject));
        if(currentClass) printf("%d班", currentClass);
        else printf("年级");
        printf("  |  总人数：%d\n", current.totalCount);
        drawBarChart(&current);
        printf("\n操作指南：\n");
        printf("←→:切换科目 | %s | Q:退出\n", currentClass ?  "↑↓:调整班级 | G:年级视图" : "C:班级视图");
        int input = _getch();
        switch(input) {
            case 75:
                currentSubject = (currentSubject - 1 + 8) % 8;
                break;
            case 77:
                currentSubject = (currentSubject + 1) % 8;
                break;
            case 'C':case'c':
                currentClass = 1;
                break;
            case 72:
                if(currentClass > 0 && currentClass < 25) currentClass++;
                break;
            case 80:
                if(currentClass > 1) currentClass--;
                break;
            case 'Q':case'q':
                return;
            default:
                break;
        }
    }
}