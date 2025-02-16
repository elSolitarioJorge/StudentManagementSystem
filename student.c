#include "StudentManagementSystem.h"

void studentMenu(stuNode* sHead, const char* userName, char* password) {
    int choice = 0;
    stuNode* myself = sHead->next;
    while(myself != NULL) {
        if(strcmp(myself->student.id, userName) == 0) {
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
    while(1) {
        system("cls");
        displayStudentMenu();
        choice = getValidInput(0, 5);
        switch(choice) {
            case 0:
                return;
            case 1:
                queryResults(myself);
                break;
            case 2:
                pagePrintingOneClassStudent(sHead, 10, myself->student.class);
                break;
            case 3:
                scoreAnalysis(sHead, myself);
                break;
            case 4:
                changePassword(password);
                break;
            default:
                break;
        }
    }
}

void displayStudentMenu() {
    printf("1.成绩查询\n");
    printf("2.查询本班成绩\n");
    printf("3.成绩分析\n");
    printf("4.修改密码\n");
    printf("0.返回上一级\n");
}

void queryResults(const stuNode* myself) {
    system("cls");
    printf("学号：\t%s\n", myself->student.id);
    printf("姓名：\t%s\n", myself->student.name);
    printf("班级：\t%d\n", myself->student.class);
    printf("语文：\t%g\n", myself->student.score.chinese);
    printf("数学：\t%g\n", myself->student.score.math);
    printf("英语：\t%g\n", myself->student.score.english);
    printf("理综：\t%g\n", myself->student.score.lizong);
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
        printf("\t\t-----2023-2024学年下学期高三2024届第四次模拟考试成绩单-----\n\n");
        printf("学号\t\t姓名\t班级\t语文\t数学\t英语\t理综\t物理\t化学\t生物\t总分\n");
        int count = 0;
        stuNode* temp = cur;
        while(temp && count < pageSize) {
            if(temp->student.class == class) {
                printf("%-16s%s\t%-8d%-8g%-8g%-8g%-8g%-8g%-8g%-8g%g\n",temp->student.id, temp->student.name, temp->student.class,
                    temp->student.score.chinese, temp->student.score.math, temp->student.score.english, temp->student.score.lizong,
                    temp->student.score.physics, temp->student.score.chemistry, temp->student.score.biology, temp->student.score.total);
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

void changePassword(char* oldPassword) {
    system("cls");
    char inputPassword[MAX_PASSWORD_LENGTH + 1];
    printf("---修改密码---\n");
    printf("请输入原密码：");
    inputHiddenPassword(inputPassword);
    if(strcmp(inputPassword, oldPassword) == 0) {
        char password2[MAX_PASSWORD_LENGTH + 1];
        char password1[MAX_PASSWORD_LENGTH + 1];
        strcpy(oldPassword, setPassword(password1, password2));
        printf("密码修改成功！\n");
    } else {
        printf("密码错误，请重试\n");
    }
    pressAnyKeyToContinue();
}

char* setPassword(char* password1, char* password2) {
    while(1){
        printf("请输入新密码：");
        inputHiddenPassword(password1);
        printf("请确认密码：  ");
        inputHiddenPassword(password2);
        if(strcmp(password1, password2) != 0) {
            printf("密码不匹配，请重试！\n");
        } else {
            return password1;
        }
    }
}

void scoreAnalysis(stuNode* sHead, stuNode* myself) {
    system("cls");
    int gradeRanking[8], classRanking[8];
    float gradeMaxScore[8], classMaxScore[8];
    float gradeAverageScore[8], classAverageScore[8];
    int gradeNum = 0, classNum = 0;
    stuNode* temp = sHead->next;
    while(temp) {
        gradeNum++;
        if(temp->student.class == myself->student.class) {
            classNum++;
        }
        temp = temp->next;
    }

    for(int i = 0; i < 8; i++) {
        float myScore = getScoreBySubject(myself, i);
        float gradeSum = 0, classSum = 0;
        gradeMaxScore[i] = 0, classMaxScore[i] = 0;
        gradeRanking[i] = 1, classRanking[i] = 1;
        stuNode* current = sHead->next;
        while(current) {
            float score = getScoreBySubject(current, i);
            gradeSum += score;
            if(score > gradeMaxScore[i]) {
                gradeMaxScore[i] = score;
            }
            if(score > myScore) {
                gradeRanking[i]++;
            }
            if(current->student.class == myself->student.class) {
                classSum += score;
                if(score > classMaxScore[i]) {
                    classMaxScore[i] = score;
                }
                if(score > myScore) {
                    classRanking[i]++;
                }
            }
            current = current->next;
        }
        gradeAverageScore[i] = gradeNum ? gradeSum / gradeNum : 0;
        classAverageScore[i] = classNum ? classSum / classNum : 0;
    }
    int currentView = 0; // 0: 班级, 1: 年级
    int choice;
    do {
        system("cls");
        printf("---%s成绩对比---\n", currentView ? "年级" : "班级");
        printf("科目\t分数\t名次\t平均分\t最高分\t差距分\n");
        for(int i = 0; i < 8; i++) {
            float score = getScoreBySubject(myself, i);
            int ranking = currentView ? gradeRanking[i] : classRanking[i];
            float avg = currentView ? gradeAverageScore[i] : classAverageScore[i];
            float maxScore = currentView ? gradeMaxScore[i] : classMaxScore[i];
            float gap = maxScore - score;

            printf("%s\t%g\t%d\t%.2f\t%g\t%g\n", getSubjectName(i), score, ranking, avg, maxScore, gap);
        }
        printf("\n按 %s 切换视图，按 Enter 退出", currentView ? "C" : "G");
        choice = _getch();
        if((choice == 'g' || choice == 'G') && !currentView) {
            currentView = 1;
        } else if((choice == 'c' || choice == 'C') && currentView) {
            currentView = 0;
        }
    } while(choice != '\r');
}

float getScoreBySubject(stuNode* node, int subject) {
    switch(subject) {
        case 0: return node->student.score.total;
        case 1: return node->student.score.chinese;
        case 2: return node->student.score.math;
        case 3: return node->student.score.english;
        case 4: return node->student.score.lizong;
        case 5: return node->student.score.physics;
        case 6: return node->student.score.chemistry;
        case 7: return node->student.score.biology;
        default: return 0.0f;
    }
}

const char* getSubjectName(int subject) {
    const char* names[] = {"总分", "语文", "数学", "英语", "理综", "物理", "化学", "生物"};
    return names[subject];
}

