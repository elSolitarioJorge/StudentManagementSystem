#include "student_management_system.h"
// 教师界面
void teacherMenu(AccNode* myAccount, StuNode* sHead) {
    int choice = 0;
    while(1) {
        system("cls");    // 清屏
        displayTeacherMenu();     // 显示教师菜单界面
        choice = _getch();        // 获取用户输入
        switch(choice) {
            case '0':            // 返回上一级
                return;
            case '1':            // 增加学生
                addStudent(sHead);
                break;
            case '2':            // 删除学生
                deleteStudent(sHead);
                break;
            case '3':            // 修改学生
                changeStudent(sHead);
                break;
            case '4':            // 查找学生
                findStudent(sHead);
                pressAnyKeyToContinue();
                break;
            case '5':            // 分页打印所有学生信息
                pagePrintingStudent(sHead, 30);
                break;
            case '6':            // 成绩分布
                analyzeScoreDistribution(sHead);
                break;
            case'7':             // 成绩分析
                analyzeScoreRanking(sHead);
                break;
            case '8':            // 修改密码
                changePassword(myAccount);
                break;
            case '9':            // 导出学生信息
                exportStudentToFile("students.bin", "new_students.csv");
                break;
            default :
                break;
        }
    }
}
// 显示教师菜单界面
void displayTeacherMenu() {
    printf("╔═════════════════════════════════╗\n");
    printf("║      👨🏫 教师控制台 👩🏫       ║\n");
    printf("╟─────────────────────────────────╢\n");
    printf("║       🆕 1. 添加学生            ║\n");
    printf("║       🗑️ 2. 删除学生            ║\n");
    printf("║       ✏️ 3. 修改信息            ║\n");
    printf("║       🔍 4. 查询学生            ║\n");
    printf("║       📋 5. 所有学生            ║\n");
    printf("║       📊 6. 成绩分布            ║\n");
    printf("║       📝 7. 各科排名            ║\n");
    printf("║       🔐 8. 修改密码            ║\n");
    printf("║       💾 9. 导出学生信息        ║\n");
    printf("║       ↩️ 0. 返回                ║\n");
    printf("╚═════════════════════════════════╝\n");
}
// 输入成绩
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
// 增加学生
void addStudent(StuNode* sHead) {
    system("cls");
    StuNode* newStudent = createStudentNode();
    printf("---添加学生信息---\n");
    getStringInput("学号：", newStudent->student.id, sizeof(newStudent->student.id));
    if(isLegalityId(newStudent->student.id) == 0) {
        pressAnyKeyToContinue();
        return;
    }
    if(idExist(sHead, newStudent->student.id)) {
        printf("学号已存在，请重新操作\n");
        pressAnyKeyToContinue();
        return;
    }
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
// 删除学生
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
// 修改学生
void changeStudent(StuNode* sHead) {
    StuNode* stu = findStudent(sHead);
    if(stu != NULL) {
        Student student = stu->student;
        printf("---修改学生信息---\n");
        getStringInput("学号：", stu->student.id, sizeof(stu->student.id));
        if(isLegalityId(stu->student.id) == 0) {
            pressAnyKeyToContinue();
            return;
        }
        if(idExist(sHead, stu->student.id)) {
            printf("学号已存在，请重新操作\n");
            pressAnyKeyToContinue();
            return;
        }
        getStringInput("姓名：", stu->student.name, sizeof(stu->student.name));
        printf("班级：");
        stu->student.class = getValidInput(1, 25);
        if(stu->student.class == -1) {
            stu->student = student;
            printf("输入不合法（直接输入学生所在班级的数字即可），修改失败！\n");
            pressAnyKeyToContinue();
            return;
        }
        enterScore(stu);
        writeStudentToFile(sHead);
        printf("学生信息修改成功！\n");
    }
    pressAnyKeyToContinue();
}
// 查找学生（根据学号或姓名）
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
// 分页打印学生信息
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
// 比较学生该科目成绩
float compareStudents(const StuNode* s1, const StuNode* s2, int criteria) {
    switch(criteria) {
        case 0:  // 按总分比较
            return s1->student.score.total - s2->student.score.total;
        case 1:  // 按语文成绩比较
            return s1->student.score.chinese - s2->student.score.chinese;
        case 2:  // 按数学成绩比较
            return s1->student.score.math - s2->student.score.math;
        case 3:  // 按英语成绩比较
            return s1->student.score.english - s2->student.score.english;
        case 4:  // 按理综成绩比较
            return s1->student.score.lizong - s2->student.score.lizong;
        case 5:  // 按物理成绩比较
            return s1->student.score.physics - s2->student.score.physics;
        case 6:  // 按化学成绩比较
            return s1->student.score.chemistry - s2->student.score.chemistry;
        case 7:  // 按生物成绩比较
            return s1->student.score.biology - s2->student.score.biology;
        default: // 无效标准返回0
            return 0;
    }
}
// 合并两个已按指定标准降序排列的双向链表，合并后仍保持降序
StuNode* mergeStudentByCriteria(StuNode* head1, StuNode* head2, int criteria) {
    // 创建哑节点简化边界处理
    StuNode dummy;
    dummy.prev = NULL;
    dummy.next = NULL;
    StuNode* tail = &dummy;

    // 遍历两个链表，选择较大节点依次连接
    while(head1 && head2) {
        // 比较节点并选择较大的接入合并链表
        if(compareStudents(head1, head2, criteria) > 0) {
            tail->next = head1;
            head1->prev = tail;  // 维护前驱指针
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2->prev = tail;   // 维护前驱指针
            head2 = head2->next;
        }
        tail = tail->next;
    }

    // 连接剩余节点
    StuNode* remaining = head1 ? head1 : head2;
    if(remaining) {
        tail->next = remaining;
        remaining->prev = tail;  // 维护剩余节点的前驱指针
    }

    // 确保头节点的prev为NULL
    if(dummy.next) {
        dummy.next->prev = NULL;
    }
    return dummy.next;
}
// 将链表从start节点分割为两部分，前n个节点为第一部分
StuNode* splitStudent(StuNode* start, int n) {
    if(start == NULL || start->next == NULL) {
        return NULL;
    }

    // 移动到第n个节点
    for(int i = 1; i < n && start->next; i++) {
        start = start->next;
    }

    // 切断链表并获取第二部分头节点
    StuNode* next = start->next;
    if(next) {
        next->prev = NULL;  // 断开前后联系
    }
    start->next = NULL;     // 切断第一部分末尾

    return next;
}
// 使用迭代归并排序算法对双向链表进行降序排序
StuNode* mergeSortStudentByCriteria(StuNode* head, int criteria) {
    if(head == NULL || head->next == NULL) {
        return head;
    }

    // 计算链表总长度
    int listSize = 0;
    StuNode* curr = head;
    while(curr) {
        listSize++;
        curr = curr->next;
    }

    // 分块大小倍增进行迭代归并
    for(int blockSize = 1; blockSize < listSize; blockSize *= 2) {
        // 创建临时哑节点用于连接排序后的块
        StuNode* dummyHead = (StuNode*)malloc(sizeof(StuNode));
        dummyHead->prev = NULL;
        dummyHead->next = head;
        StuNode* tail = dummyHead;

        // 每次处理两个相邻块进行合并
        while(head) {
            StuNode* left = head;                   // 第一个块
            StuNode* right = splitStudent(left, blockSize); // 分割出第二个块
            head = splitStudent(right, blockSize);  // 准备下一组块

            // 合并两个块并连接到哑节点后
            StuNode* merged = mergeStudentByCriteria(left, right, criteria);
            tail->next = merged;
            merged->prev = tail;

            // 移动tail到合并链表的末尾
            while(tail->next) {
                tail = tail->next;
            }
        }

        // 更新head指针并释放临时哑节点
        head = dummyHead->next;
        free(dummyHead);
    }

    return head;
}
// 科目满分对照
int getFullScoreBySubject(int subject) {
    if(subject == 0) return 750;   // 总分满分
    if(subject == 4) return 300;   // 理综满分
    if(subject == 5) return 110;   // 物理满分
    if(subject == 6) return 100;   // 化学满分
    if(subject == 7) return 90;    // 生物满分
    return 150;                    // 语、数、英满分
}
// 根据科目设置区间大小
int getIntervalSize(int subject) {
    if(subject == 0) return 50;//总分
    if(subject == 4) return 20;//理综
    return 10;
}
// 生成分数区间标签
void generateIntervalLabels(float minVal, float maxVal, int intervalSize, char labels [][20], int* count) {
    *count = 0;
    int start = ((int)minVal / intervalSize) * intervalSize;
    int end = ((int)maxVal / intervalSize + 1) * intervalSize;
    for(int i = end; i > start; i -= intervalSize) {
        sprintf(labels[*count], "[%d, %d):", i - intervalSize, i);
        (*count)++;
    }
}
// 计算成绩分布数据
ScoreDistribution calculateDistribution(StuNode* sHead, int class, int subject) {
    ScoreDistribution current;
    current.class = class;
    current.subject = subject;
    current.minScore = 1000;  // 初始化最小分
    current.maxScore = -1;     // 初始化最大分
    current.maxCount = 0;      // 最大区间人数
    current.totalCount = 0;    // 总参考人数
    current.absentCount = 0;   // 缺考人数
    current.intervalSize = getIntervalSize(subject);
    StuNode* cur = sHead->next;
    // 第一遍遍历：统计基础数据
    while(cur) {
        if(class == 0 || cur->student.class == class) {  // 班级筛选
            if(cur->student.score.total == 0) {          // 缺考判断
                current.absentCount++;
            } else {
                float score = getScoreBySubject(cur, subject);
                current.minScore = current.minScore < score ? current.minScore : score;
                current.maxScore = current.maxScore > score ? current.maxScore : score;
            }
            current.totalCount++;
        }
        cur = cur->next;
    }
    // 处理全缺考特殊情况
    if(current.totalCount == current.absentCount) {
        current.minScore = 0;
        current.maxScore = 0;
    }
    // 计算有效区间范围
    int intervalStart = ((int)current.minScore / current.intervalSize) * current.intervalSize;
    int intervalEnd = ((int)current.maxScore / current.intervalSize + 1) * current.intervalSize;
    intervalEnd = intervalEnd < getFullScoreBySubject(subject) ? intervalEnd : getFullScoreBySubject(subject);
    current.intervalCount = (intervalEnd - intervalStart) / current.intervalSize;
    // 第二遍遍历：统计区间人数
    memset(current.intervals, 0, sizeof(current.intervals));
    cur = sHead->next;
    while(cur) {
        if((class == 0 || cur->student.class == class) && cur->student.score.total > 0) {
            float score = getScoreBySubject(cur, subject);
            int index = (intervalEnd - (int)score - 1) / current.intervalSize;
            index = index >= current.intervalCount ? current.intervalCount - 1 : index;
            current.intervals[index]++;
            current.maxCount = current.maxCount > current.intervals[index] ? current.maxCount : current.intervals[index];
        }
        cur = cur->next;
    }
    return current;
}
// 绘制柱状图
void drawBarChart(const ScoreDistribution* current) {
    char labels[20][20];
    int labelCount = 0;
    generateIntervalLabels(current->minScore, current->maxScore, current->intervalSize, labels, &labelCount);
    printf("\n成绩分布: %g - %g\n", current->minScore, current->maxScore);
    for(int i = 0; i < labelCount; i++) {
        const int maxBarWidth = 150;
        int barLength = current->maxCount ? (current->intervals[i] * maxBarWidth) / current->maxCount : 0;
        printf("\n%-12s", labels[i]);
        for(int j = 0; j < barLength; j++) {
            printf("█");
        }
        printf(" %d人\n", current->intervals[i]);
    }
}
// 成绩分析
void analyzeScoreDistribution(StuNode* sHead) {
    int currentClass = 0, currentSubject = 0;
    while(1) {
        system("cls");
        ScoreDistribution current = calculateDistribution(sHead, currentClass, currentSubject);
        printf("科目：%s  |  ", getSubjectName(currentSubject));
        if(currentClass) printf("%d班", currentClass);
        else printf("年级");
        printf("  |  总人数：%d  |  缺考：", current.totalCount);
        for(int i = current.absentCount; i > 0; i--) {
            printf("🚶");
        }
        printf(" %d人\n", current.absentCount);
        drawBarChart(&current);
        if(currentClass == 0) {
            printf("\n⚠ 缺考人数分布：\n");
            StuNode* cur = sHead->next;
            int classAbsent[26] = {0};
            while(cur) {
                if(cur->student.score.total == 0) {
                    classAbsent[cur->student.class]++;
                }
                cur = cur->next;
            }
            for(int i = 1; i <= 25; i++) {
                if(classAbsent[i]) {
                    printf("%2d班：", i);
                    for(int j = classAbsent[i]; j > 0; j--) {
                        printf("🚶");
                    }
                    printf(" %d人\n", classAbsent[i]);
                }
            }
        }
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
            case 'G':case'g':
                currentClass = 0;
                break;
            case 'Q':case'q':
                return;
            default:
                break;
        }
    }
}
// 成绩排名分析
void analyzeScoreRanking(const StuNode* sHead) {
    int currentClass = 0, currentSubject = 0;
    while(1) {
        system("cls");
        printf("科目：%s  |  ", getSubjectName(currentSubject));
        if(currentClass) printf("%d班\n\n", currentClass);
        else printf("年级\n\n");
        printf("←→:切换科目 | %s | %s\n\n", currentClass ?  "↑↓:调整班级 | G:年级视图" : "C:班级视图", "Q:退出");
        printTranscript(sHead, currentClass, currentSubject);
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
            case 'G':case'g':
                currentClass = 0;
            break;
            case 'Q':case'q':
                return;
            default:
                break;
        }
    }
}
// 打印排序成绩单
void printTranscript(const StuNode* sHead, int class, int subject) {
    StuNode* classHead = copyStudentByClass(sHead, class);
    if(classHead == NULL) {
        printf("班级为空！\n");
        pressAnyKeyToContinue();
        return;
    }
    classHead = mergeSortStudentByCriteria(classHead, subject);
    StuNode* curr = classHead;
    printf("\t\t-----2023-2024学年下学期高三2024届第四次模拟考试成绩单-----\n\n");
    printf("学号\t\t姓名\t班级\t语文\t数学\t英语\t理综\t物理\t化学\t生物\t总分\n");
    while(curr) {
        printf("%-16s%s\t%-8d%-8g%-8g%-8g%-8g%-8g%-8g%-8g%g\n",curr->student.id, curr->student.name, curr->student.class,
            curr->student.score.chinese, curr->student.score.math, curr->student.score.english, curr->student.score.lizong,
            curr->student.score.physics, curr->student.score.chemistry, curr->student.score.biology, curr->student.score.total);
        curr = curr->next;
    }
    scrollConsoleToTop();
    freeStudentList(classHead);
}
// 检查学号是否存在
int idExist(const StuNode* sHead, char* id) {
    StuNode* cur = sHead;
    while(cur) {
        if(strcmp(cur->student.id, id) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}
