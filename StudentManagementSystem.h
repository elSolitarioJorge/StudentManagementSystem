#ifndef STUDENTMANAGEMENTSYSTEM_H
#define STUDENTMANAGEMENTSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_PASSWORD_LENGTH 50

typedef struct {
    float chinese;
    float math;
    float english;
    float physics;
    float chemistry;
    float biology;
    float lizong;
    float total;
} Score;

typedef struct {
    char userName[20];
    char password[MAX_PASSWORD_LENGTH + 1];
    char role;
} Account;

typedef struct {
    char name[50];
    char id[20];
    int class;
    Score score;
} Student;

typedef struct studentList {
    Student student;
    struct studentList* prev;
    struct studentList* next;
} StuNode;

typedef struct accountList {
    Account account;
    struct accountList* next;
} AccNode;

typedef struct todoList {
    char userName[20];
    struct todoList* next;
} TNode;

typedef struct {
    int class;            // 班级号（0表示年级）
    int subject;          // 科目代码
    float minScore;       // 最低分
    float maxScore;       // 最高分
    int intervalSize;     // 区间大小
    int intervalCount;    // 区间数量
    int intervals[20];    // 各区间人数
    int maxCount;         // 最大区间人数
    int totalCount;       // 总人数
    int absentCount;      // 缺考人数
}ScoreDistribution;

void addAdmin(AccNode* aHead);
void pressAnyKeyToContinue();
void clearInputBuffer();
int getValidInput(int min, int max);
void getStringInput(const char* prompt, char* input, int size);
float getFloatInput(const char* prompt);
AccNode* createAccountNode();
StuNode* createStudentNode();
TNode* createTodoNode();
void appendAccountNodeAtTail(AccNode* aHead, AccNode*  newAccNode);
void appendStudentNodeAtTail(StuNode* sHead, StuNode* newStuNode);
void appendTodoNodeAtTail(TNode* tHead, TNode* newTNode);
void freeAccountList(AccNode* aHead);
void freeStudentList(StuNode* sHead);
StuNode* copyStudentList(StuNode* head);
void mainMenu(AccNode* aHead, StuNode* sHead, TNode* tHead);
void displayMainMenu();
void userLogin(AccNode* aHead, StuNode* sHead, TNode* tHead);
void passwordAppeal(const AccNode* aHead, TNode* tHead);
void inputHiddenPassword(char* inputPassword);
char authentication(const AccNode* aHead, const char* inputUserName, const char* inputPassword);


void studentMenu(StuNode* sHead, const char* userName, char* password);
void displayStudentMenu();
void queryResults(const StuNode* myself);
void pagePrintingOneClassStudent(const StuNode* sHead, int pageSize, int class);
void changePassword(char* oldPassword);
char* setPassword(char* password1, char* password2);
void scoreAnalysis(StuNode* sHead, StuNode* myself);
float getScoreBySubject(StuNode* node, int subject);
const char* getSubjectName(int subject);

void teacherMenu(StuNode* sHead, char* password);
void displayTeacherMenu();
void enterScore(StuNode* student);
void addStudent(StuNode* sHead);
void deleteStudent(StuNode* sHead);
void changeStudent(StuNode* sHead);
StuNode* findStudent(StuNode* sHead);
void pagePrintingStudent(const StuNode* sHead, int pageSize);
float compareStudents(const StuNode* s2, const StuNode* s1, int criteria);
void analyzeScoreDistribution(StuNode* sHead);
StuNode* mergeStudentByCriteria(StuNode* head1, StuNode* head2, int criteria);
StuNode* splitStudent(StuNode* head);
StuNode* mergeSortStudentByCriteria(StuNode* head, int criteria);
int getFullScoreBySubject(int subject);
int getIntervalSize(int subject);
void generateIntervalLabels(float minVal, float maxVal, int intervalSize, char labels [][20], int* count);
ScoreDistribution calculateDistribution(StuNode* sHead, int class, int subject);
void drawBarChart(const ScoreDistribution* current);


void adminMenu(AccNode* aHead, StuNode* sHead, TNode* tHead);
void displayAdminMenu(int count);
void addAccount(AccNode* aHead);
void deleteAccount(AccNode* aHead);
void changeAccount(AccNode* aHead);
AccNode* findPrevAccount(AccNode* aHead);
void pagePrintingAccount(const AccNode* aHead, int pageSize);
void printTodo(const TNode* tHead, int count);
void finishTodo(const AccNode* aHead, TNode* tHead, int* count);
char selectIdentify();

void writeAccountToFile(const AccNode* aHead);
void writeStudentToFile(const StuNode* sHead);
void writeTodoToFile(const TNode* tHead);
void readAccountFromFile(AccNode* aHead);
void readStudentFromFile(StuNode* sHead);
void readTodoFromFile(TNode* tHead);
void importStudentToFile(const char* csvFileName, const char* binFileName);
void importAccountToFile(const char* csvFileName, const char* binFileName);








#endif //STUDENTMANAGEMENTSYSTEM_H
