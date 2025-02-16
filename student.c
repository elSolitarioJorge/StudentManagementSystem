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
    int ranking[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    float maxScore[8];
    float averageScore[8];
    for(int i = 0; i < 8; i++) {
        int num = 0;
        float sum = 0;
        stuNode* copyList = copyStudentList(sHead->next);
        stuNode* sortedList = mergeSortStudentByCriteria(copyList, i);
        stuNode* temp = sortedList;
        while(temp) {
            num++;
            switch(i) {
                case 0:
                    if(num == 1) {
                        maxScore[0] = temp->student.score.total;
                    }
                    if(temp->student.score.total > myself->student.score.total) {
                        ranking[0]++;
                    }
                    sum += temp->student.score.total;
                    break;
                case 1:
                    if(num == 1) {
                        maxScore[1] = temp->student.score.chinese;
                    }
                    if(temp->student.score.chinese > myself->student.score.chinese) {
                        ranking[1]++;
                    }
                    sum += temp->student.score.chinese;
                    break;
                case 2:
                    if(num == 1) {
                        maxScore[2] = temp->student.score.math;
                    }
                    if(temp->student.score.math > myself->student.score.math) {
                        ranking[2]++;
                    }
                    sum += temp->student.score.math;
                    break;
                case 3:
                    if(num == 1) {
                        maxScore[3] = temp->student.score.english;
                    }
                    if(temp->student.score.english > myself->student.score.english) {
                        ranking[3]++;
                    }
                    sum += temp->student.score.english;
                    break;
                case 4:
                    if(num == 1) {
                        maxScore[4] = temp->student.score.lizong;
                    }
                    if(temp->student.score.lizong > myself->student.score.lizong) {
                        ranking[4]++;
                    }
                    sum += temp->student.score.lizong;
                    break;
                case 5:
                    if(num == 1) {
                        maxScore[5] = temp->student.score.physics;
                    }
                    if(temp->student.score.physics > myself->student.score.physics) {
                        ranking[5]++;
                    }
                    sum += temp->student.score.physics;
                    break;
                case 6:
                    if(num == 1) {
                        maxScore[6] = temp->student.score.chemistry;
                    }
                    if(temp->student.score.chemistry > myself->student.score.chemistry) {
                        ranking[6]++;
                    }
                    sum += temp->student.score.chemistry;
                    break;
                case 7:
                    if(num == 1) {
                        maxScore[7] = temp->student.score.biology;
                    }
                    if(temp->student.score.biology > myself->student.score.biology) {
                        ranking[7]++;
                    }
                    sum += temp->student.score.biology;
                    break;
                default:
                    break;
            }
            temp = temp->next;
        }
        averageScore[i] = sum / num;
        freeStudentList(sortedList);
    }
    printf("科目\t分数\t名次\t平均分\t最高分\t差距分\t\n");
    printf("总分\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.total, ranking[0], averageScore[0], maxScore[0], myself->student.score.total - maxScore[0]);
    printf("语文\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.chinese, ranking[1], averageScore[1], maxScore[1], myself->student.score.chinese - maxScore[1]);
    printf("数学\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.math, ranking[2], averageScore[2], maxScore[2], myself->student.score.math - maxScore[2]);
    printf("英语\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.english, ranking[3], averageScore[3], maxScore[3], myself->student.score.english - maxScore[3]);
    printf("理综\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.lizong, ranking[4], averageScore[4], maxScore[4], myself->student.score.lizong - maxScore[4]);
    printf("物理\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.physics, ranking[5], averageScore[5], maxScore[5], myself->student.score.physics - maxScore[5]);
    printf("化学\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.chemistry, ranking[6], averageScore[6], maxScore[6], myself->student.score.chemistry - maxScore[6]);
    printf("生物\t%g\t%d\t%.2f\t%g\t%g\t\n", myself->student.score.biology, ranking[7], averageScore[7], maxScore[7], myself->student.score.biology - maxScore[7]);
    pressAnyKeyToContinue();
}



