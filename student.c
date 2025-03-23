#include "student_management_system.h"
// 学生界面
void studentMenu(AccNode* myAccount, StuNode* sHead) {
    int choice = 0;
    // 获取当前登录的学生账户的学生信息，检查该学生是否存在
    StuNode* myself = sHead->next;
    while(myself != NULL) {
        if(strcmp(myself->student.id, myAccount->account.userName) == 0) {
            break;
        }
        myself = myself->next;
    }
    // 不存在，直接退出
    if(myself == NULL) {
        system("cls");
        printf("用户不存在\n");
        pressAnyKeyToContinue();
        return;
    }
    while(1) {
        system("cls");    // 清屏
        displayStudentMenu();     // 显示学生菜单界面
        choice = _getch();        // 获取学生输入
        switch(choice) {
            case '0':         // 返回上一级
                return;
            case '1':         // 成绩查询
                queryMyScore(myself);
                break;
            case '2':         // 查看班级成绩单
                pagePrintingOneClassStudentBySubject(sHead, 10, myself->student.class);
                break;
            case '3':         // 成绩分析
                scoreAnalysis(sHead, myself);
                break;
            case '4':         // 修改密码
                changePassword(myAccount);
                break;
            default:
                break;
        }
    }
}
// 学生菜单界面
void displayStudentMenu() {
    printf("╔════════════════════════════════╗\n");
    printf("║       📚 学生功能菜单 📚       ║\n");
    printf("╟────────────────────────────────╢\n");
    printf("║       📊 1. 成绩查询           ║\n");
    printf("║       👥 2. 班级成绩           ║\n");
    printf("║       📈 3. 成绩分析           ║\n");
    printf("║       🔐 4. 修改密码           ║\n");
    printf("║       ↩️ 0. 返回               ║\n");
    printf("╚════════════════════════════════╝\n");
}
// 查询我的成绩
void queryMyScore(const StuNode* myself) {
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
// 按班级分页打印学生信息， 0 表示年级（双向链表）
void pagePrintingOneClassStudentBySubject(const StuNode* sHead, int pageSize, int class) {
    // 拷贝一份数据进行操作
    StuNode* classHead = copyStudentByClass(sHead, class);
    // 判断班级/年级是否为空
    if(classHead == NULL) {
        printf("班级为空！\n");
        pressAnyKeyToContinue();
        return;
    }
    // 按总分排序
    classHead = mergeSortStudentByCriteria(classHead, 0);
    StuNode* cur = classHead;
    // 计算链表大小
    int size = 0;
    while(cur != NULL) {
        size++;
        cur = cur->next;
    }
    cur = classHead;
    // 计算总页数
    int totalPages = (size + pageSize - 1) / pageSize;
    // 当前页
    int currentPage = totalPages ? 1 : 0;
    while(1) {
        system("cls");
        printf("\t\t-----2023-2024学年下学期高三2024届第四次模拟考试成绩单-----\n\n");
        printf("学号\t\t姓名\t班级\t语文\t数学\t英语\t理综\t物理\t化学\t生物\t总分\n");
        int count = 0;
        StuNode* temp = cur;
        // 打印当前页的学生信息
        while(temp && count < pageSize) {
            printf("%-16s%s\t%-8d%-8g%-8g%-8g%-8g%-8g%-8g%-8g%g\n",temp->student.id, temp->student.name, temp->student.class,
                temp->student.score.chinese, temp->student.score.math, temp->student.score.english, temp->student.score.lizong,
                temp->student.score.physics, temp->student.score.chemistry, temp->student.score.biology, temp->student.score.total);
            count++;
            temp = temp->next;
        }
        printf("\n\n\t\t\t\t--------Page(%d/%d)--------\n\n", currentPage, totalPages);
        // 如果当前页不是最后一页，提示怎么进入下一页
        if (currentPage < totalPages) {
            printf("按 N 查看下一页，");
        }
        // 如果当前页不是第一页，提示怎么返回上一页
        if (currentPage > 1) {
            printf("按 B 返回上一页，");
        }
        // 提示如何退出
        printf("按 Q 退出：");
        // 获取用户输入
        int command = _getch();
        // 根据用户输入进行操作
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
            freeStudentList(classHead);
            break;
        }
    }
}
// 修改密码
void changePassword(AccNode* acc) {
    system("cls");
    char inputPassword[MAX_PASSWORD_LENGTH + 1];
    printf("---修改密码---\n");
    // 必须先输入原密码，确保是用户本人操作
    printf("请输入原密码：");
    inputHiddenPassword(inputPassword);
    unsigned char inputHash[HASH_LENGTH];
    hashPassword(inputPassword, acc->account.salt, inputHash);
    // 如果密码不匹配，直接退出
    if(memcmp(inputHash, acc->account.passwordHash, HASH_LENGTH) != 0) {
        printf("密码错误！\n");
        pressAnyKeyToContinue();
        return;
    }
    // 双重密码确认
    char newPass1[MAX_PASSWORD_LENGTH + 1], newPass2[MAX_PASSWORD_LENGTH + 1];
    setPassword(newPass1, newPass2);
    RAND_bytes(acc->account.salt, SALT_LENGTH);
    hashPassword(newPass1, acc->account.salt, acc->account.passwordHash);
    printf("密码修改成功！\n");
    pressAnyKeyToContinue();
}
// 设置密码（需二次确认）
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
// 成绩分析
void scoreAnalysis(StuNode* sHead, StuNode* myself) {
    system("cls");       // 清屏
    int gradeRanking[8], classRanking[8];             // 年级排名、班级排名
    float gradeMaxScore[8], classMaxScore[8];         // 年级最高分、班级最高分
    float gradeAverageScore[8], classAverageScore[8]; // 年级平均分、班级平均分
    int gradeNum = 0, classNum = 0;                   // 年级人数、班级人数
    StuNode* temp = sHead->next;
    // 统计年级人数和班级人数
    while(temp) {
        gradeNum++;
        if(temp->student.class == myself->student.class) {
            classNum++;
        }
        temp = temp->next;
    }
    // 统计排名、最高分，计算平均分
    for(int i = 0; i < 8; i++) {
        // 获取我的该科目成绩
        float myScore = getScoreBySubject(myself, i);

        float gradeSum = 0, classSum = 0;
        gradeMaxScore[i] = 0, classMaxScore[i] = 0;
        gradeRanking[i] = 1, classRanking[i] = 1;
        StuNode* current = sHead->next;
        while(current) {
            // 获取当前节点学生该科目成绩
            float score = getScoreBySubject(current, i);
            // 加入总成绩
            gradeSum += score;
            // 统计最高分
            if(score > gradeMaxScore[i]) {
                gradeMaxScore[i] = score;
            }
            // 统计排名
            if(score > myScore) {
                gradeRanking[i]++;
            }
            // 统计班级各项
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
// 获取科目成绩
float getScoreBySubject(StuNode* node, int subject) {
    switch(subject) {
        case 0: return node->student.score.total;        // 0：总分
        case 1: return node->student.score.chinese;      // 1：语文
        case 2: return node->student.score.math;         // 2：数学
        case 3: return node->student.score.english;      // 3：英语
        case 4: return node->student.score.lizong;       // 4：物理
        case 5: return node->student.score.physics;      // 5：化学
        case 6: return node->student.score.chemistry;    // 6: 生物
        case 7: return node->student.score.biology;      // 7：总分
        default: return 0.0f;
    }
}
// 获取科目名称
const char* getSubjectName(int subject) {
    const char* names[] = {"总分", "语文", "数学", "英语", "理综", "物理", "化学", "生物"};
    return names[subject];
}

