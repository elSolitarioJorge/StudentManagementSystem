#ifndef STUDENTMANAGEMENTSYSTEM_H
#define STUDENTMANAGEMENTSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_PASSWORD_LENGTH 50

typedef struct Score{
    float chinese;
    float math;
    float english;
    float physics;
    float chemistry;
    float biology;
    float lizong;
    float total;
} Sco;

typedef struct Account {
    char userName[20];
    char password[MAX_PASSWORD_LENGTH + 1];
    char role;
} Acc;

typedef struct Student {
    char name[50];
    char id[20];
    int class;
    Sco score;
} Stu;

typedef struct studentList {
    Stu student;
    struct studentList* prev;
    struct studentList* next;
} stuNode;

typedef struct accountList {
    Acc account;
    struct accountList* next;
} accNode;

typedef struct todoList {
    char userName[20];
    struct todoList* next;
} tNode;

void addAdmin(accNode* aHead);
void pressAnyKeyToContinue();
void clearInputBuffer();
int getValidInput(int min, int max);
void getStringInput(const char* prompt, char* input, int size);
float getFloatInput(const char* prompt);
accNode* createAccountNode();
stuNode* createStudentNode();
tNode* createTodoNode();
void appendAccountNodeAtTail(accNode* aHead, accNode*  newAccNode);
void appendStudentNodeAtTail(stuNode* sHead, stuNode* newStuNode);
void appendTodoNodeAtTail(tNode* tHead, tNode* newTNode);
void freeAccountList(accNode* aHead);
void freeStudentList(stuNode* sHead);
stuNode* copyStudentList(stuNode* head);
void mainMenu(accNode* aHead, stuNode* sHead, tNode* tHead);
void displayMainMenu();
void userLogin(accNode* aHead, stuNode* sHead, tNode* tHead);
void passwordAppeal(const accNode* aHead, tNode* tHead);
void inputHiddenPassword(char* inputPassword);
char authentication(const accNode* aHead, const char* inputUserName, const char* inputPassword);


void studentMenu(stuNode* sHead, const char* userName, char* password);
void displayStudentMenu();
void queryResults(const stuNode* myself);
void pagePrintingOneClassStudent(const stuNode* sHead, int pageSize, int class);
void changePassword(char* oldPassword);
char* setPassword(char* password1, char* password2);
void scoreAnalysis(stuNode* sHead, stuNode* myself);
float getScoreBySubject(stuNode* node, int subject);
const char* getSubjectName(int subject);

void teacherMenu(stuNode* sHead, char* password);
void displayTeacherMenu();
void enterScore(stuNode* student);
void addStudent(stuNode* sHead);
void deleteStudent(stuNode* sHead);
void changeStudent(stuNode* sHead);
stuNode* findStudent(stuNode* sHead);
void pagePrintingStudent(const stuNode* sHead, int pageSize);
float compareStudents(const stuNode* s2, const stuNode* s1, int criteria);
stuNode* mergeStudentByCriteria(stuNode* head1, stuNode* head2, int criteria);
stuNode* splitStudent(stuNode* head);
stuNode* mergeSortStudentByCriteria(stuNode* head, int criteria);

void adminMenu(accNode* aHead, stuNode* sHead, tNode* tHead);
void displayAdminMenu(int count);
void addAccount(accNode* aHead);
void deleteAccount(accNode* aHead);
void changeAccount(accNode* aHead);
accNode* findPrevAccount(accNode* aHead);
void pagePrintingAccount(const accNode* aHead, int pageSize);
void printTodo(const tNode* tHead, int count);
void finishTodo(const accNode* aHead, tNode* tHead, int* count);
char selectIdentify();

void writeAccountToFile(const accNode* aHead);
void writeStudentToFile(const stuNode* sHead);
void writeTodoToFile(const tNode* tHead);
void readAccountFromFile(accNode* aHead);
void readStudentFromFile(stuNode* sHead);
void readTodoFromFile(tNode* tHead);















#endif //STUDENTMANAGEMENTSYSTEM_H
