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
    int gradeRanking[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    int classRanking[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    float gradeMaxScore[8];
    float classMaxScore[8];
    float gradeAverageScore[8];
    float classAverageScore[8];
    for(int i = 0; i < 8; i++) {
        int gradeNum = 0, classNum = 0;
        float gradeSum = 0, classSum = 0;
        stuNode* copyList = copyStudentList(sHead->next);
        stuNode* sortedList = mergeSortStudentByCriteria(copyList, i);
        stuNode* temp = sortedList;
        while(temp) {
            gradeNum++;
            if(temp->student.class == myself->student.class) {
                classNum++;
            }
            switch(i) {
                case 0:
                    if(gradeNum == 1) {
                        gradeMaxScore[0] = temp->student.score.total;
                    }
                    if(classNum == 1) {
                        classMaxScore[0] = temp->student.score.total;
                    }
                    if(temp->student.score.total > myself->student.score.total) {
                        gradeRanking[0]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[0]++;
                        }
                    }
                    gradeSum += temp->student.score.total;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.total;
                    }
                    break;
                case 1:
                    if(gradeNum == 1) {
                        gradeMaxScore[1] = temp->student.score.chinese;
                    }
                    if(classNum == 1) {
                        classMaxScore[1] = temp->student.score.chinese;
                    }
                    if(temp->student.score.chinese > myself->student.score.chinese) {
                        gradeRanking[1]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[1]++;
                        }
                    }
                    gradeSum += temp->student.score.chinese;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.chinese;
                    }
                    break;
                case 2:
                    if(gradeNum == 1) {
                        gradeMaxScore[2] = temp->student.score.math;
                    }
                    if(classNum == 1) {
                        classMaxScore[2] = temp->student.score.math;
                    }
                    if(temp->student.score.math > myself->student.score.math) {
                        gradeRanking[2]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[2]++;
                        }
                    }
                    gradeSum += temp->student.score.math;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.math;
                    }
                    break;
                case 3:
                    if(gradeNum == 1) {
                        gradeMaxScore[3] = temp->student.score.english;
                    }
                    if(classNum == 1) {
                        classMaxScore[3] = temp->student.score.english;
                    }
                    if(temp->student.score.english > myself->student.score.english) {
                        gradeRanking[3]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[3]++;
                        }
                    }
                    gradeSum += temp->student.score.english;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.english;
                    }
                    break;
                case 4:
                    if(gradeNum == 1) {
                        gradeMaxScore[4] = temp->student.score.lizong;
                    }
                    if(classNum == 1) {
                        classMaxScore[4] = temp->student.score.lizong;
                    }
                    if(temp->student.score.lizong > myself->student.score.lizong) {
                        gradeRanking[4]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[4]++;
                        }
                    }
                    gradeSum += temp->student.score.lizong;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.lizong;
                    }
                    break;
                case 5:
                    if(gradeNum == 1) {
                        gradeMaxScore[5] = temp->student.score.physics;
                    }
                    if(classNum == 1) {
                        classMaxScore[5] = temp->student.score.physics;
                    }
                    if(temp->student.score.physics > myself->student.score.physics) {
                        gradeRanking[5]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[5]++;
                        }
                    }
                    gradeSum += temp->student.score.physics;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.physics;
                    }
                    break;
                case 6:
                    if(gradeNum == 1) {
                        gradeMaxScore[6] = temp->student.score.chemistry;
                    }
                    if(classNum == 1) {
                        classMaxScore[6] = temp->student.score.chemistry;
                    }
                    if(temp->student.score.chemistry > myself->student.score.chemistry) {
                        gradeRanking[6]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[6]++;
                        }
                    }
                    gradeSum += temp->student.score.chemistry;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.chemistry;
                    }
                    break;
                case 7:
                    if(gradeNum == 1) {
                        gradeMaxScore[7] = temp->student.score.biology;
                    }
                    if(classNum == 1) {
                        classMaxScore[7] = temp->student.score.biology;
                    }
                    if(temp->student.score.biology > myself->student.score.biology) {
                        gradeRanking[7]++;
                        if(temp->student.class == myself->student.class) {
                            classRanking[7]++;
                        }
                    }
                    gradeSum += temp->student.score.biology;
                    if(temp->student.class == myself->student.class) {
                        classSum += temp->student.score.biology;
                    }
                    break;
                default:
                    break;
            }
            temp = temp->next;
        }
        gradeAverageScore[i] = gradeSum / gradeNum;
        classAverageScore[i] = classSum / classNum;
        freeStudentList(sortedList);
    }
    int choice = 'c';
    do {
        if(choice == 'c' || choice == 'C') {
            system("cls");
            printf("---班级成绩对比---\n");
            printf("科目\t分数\t名次\t平均分\t最高分\t差距分\t\n");
            printf("总分\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.total, classRanking[0], classAverageScore[0], classMaxScore[0], myself->student.score.total - classMaxScore[0]);
            printf("语文\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.chinese, classRanking[1], classAverageScore[1], classMaxScore[1], myself->student.score.chinese - classMaxScore[1]);
            printf("数学\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.math, classRanking[2], classAverageScore[2], classMaxScore[2], myself->student.score.math - classMaxScore[2]);
            printf("英语\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.english, classRanking[3], classAverageScore[3], classMaxScore[3], myself->student.score.english - classMaxScore[3]);
            printf("理综\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.lizong, classRanking[4], classAverageScore[4], classMaxScore[4], myself->student.score.lizong - classMaxScore[4]);
            printf("物理\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.physics, classRanking[5], classAverageScore[5], classMaxScore[5], myself->student.score.physics - classMaxScore[5]);
            printf("化学\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.chemistry, classRanking[6], classAverageScore[6], classMaxScore[6], myself->student.score.chemistry - classMaxScore[6]);
            printf("生物\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.biology, classRanking[7], classAverageScore[7], classMaxScore[7], myself->student.score.biology - classMaxScore[7]);
            printf("按 G 查看年级对比，按 enter 退出\n");
        } else if(choice == 'g' || choice == 'G') {
            system("cls");
            printf("---年级成绩对比---\n");
            printf("科目\t分数\t名次\t平均分\t最高分\t差距分\t\n");
            printf("总分\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.total, gradeRanking[0], gradeAverageScore[0], gradeMaxScore[0], myself->student.score.total - gradeMaxScore[0]);
            printf("语文\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.chinese, gradeRanking[1], gradeAverageScore[1], gradeMaxScore[1], myself->student.score.chinese - gradeMaxScore[1]);
            printf("数学\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.math, gradeRanking[2], gradeAverageScore[2], gradeMaxScore[2], myself->student.score.math - gradeMaxScore[2]);
            printf("英语\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.english, gradeRanking[3], gradeAverageScore[3], gradeMaxScore[3], myself->student.score.english - gradeMaxScore[3]);
            printf("理综\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.lizong, gradeRanking[4], gradeAverageScore[4], gradeMaxScore[4], myself->student.score.lizong - gradeMaxScore[4]);
            printf("物理\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.physics, gradeRanking[5], gradeAverageScore[5], gradeMaxScore[5], myself->student.score.physics - gradeMaxScore[5]);
            printf("化学\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.chemistry, gradeRanking[6], gradeAverageScore[6], gradeMaxScore[6], myself->student.score.chemistry - gradeMaxScore[6]);
            printf("生物\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.biology, gradeRanking[7], gradeAverageScore[7], gradeMaxScore[7], myself->student.score.biology - gradeMaxScore[7]);
            printf("按 C 查看年级对比，按 enter 退出\n");
        } else if(choice == '\r') {
            break;
        }
    }while((choice = _getch()));
}



