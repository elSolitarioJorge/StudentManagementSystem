//
// Created by yaoheng on 25-2-5.
//

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

//初始化
void addAdmin(accNode* aHead);
void pressAnyKeyToContinue();
void clearInputBuffer();
int getValidInput(int min, int max);
void getStringInput(const char* prompt, char* input, int size);
float getFloatInput(const char* prompt);
accNode* createAccountNode();
stuNode* createStudentNode();
void appendAccountNodeAtTail(accNode* aHead, accNode*  newAccNode);
void appendStudentNodeAtTail(stuNode* sHead, stuNode* newStuNode);
void freeAccountList(accNode* aHead);
void freeStudentList(stuNode* sHead);
//登录
void mainMenu(accNode* aHead, stuNode* sHead);
void userLogin(accNode* aHead, stuNode* sHead);
void displayMainMenu();

void inputHiddenPassword(char* inputPassword);
char authentication(const accNode* aHead, const char* inputUserName, const char* inputPassword);

//学生端
void studentMenu(stuNode* sHead, const char* inputUserName);
void displayStudentMenu();
void queryResults(const stuNode* sHead, const char* inputUserName);

//教师端
void teacherMenu(stuNode* sHead);
void displayTeacherMenu();
void addStudent(stuNode* sHead);
void deleteStudent(stuNode* sHead);
void pagePrintingStudent(const stuNode* sHead, int pageSize);
//管理员端
void adminMenu(accNode* aHead);
void displayAdminMenu();

void addAccount(accNode* aHead);
void deleteAccount(accNode* aHead);
void pagePrintingAccount(const accNode* aHead, int pageSize);
void getValidAccount(char* userName);
void setPassword(char* password1, char* password2);
char selectIdentify();

//忘记密码
void passwordRecovery();

//数据读写
void writeAccountToFile(const accNode* aHead);
void writeStudentToFile(const stuNode* sHead);

void readAccountFromFile(accNode* aHead);
void readStudentFromFile(stuNode* sHead);

void addAccountToFile(const char* userName, const char* password, const char* role);













#endif //STUDENTMANAGEMENTSYSTEM_H
