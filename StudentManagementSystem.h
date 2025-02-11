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

#define MAX_PASSWORD_LENTH 50

typedef struct Score{
    int chinese;
    int math;
    int english;
} Sco;

typedef struct Account {
    char userName[20];
    char password[MAX_PASSWORD_LENTH + 1];
    char role;
} Acc;

typedef struct Student {
    char name[50];
    char id[20];
    Sco score;
} Stu;


typedef struct studentList {
    Stu student;
    struct studentList* next;
} stuNode;

typedef struct accountList {
    Acc account;
    struct accountList* next;
} accNode;

//初始化
void addAdmin(accNode* aHead);
//登录
void mainMenu(accNode* aHead, stuNode* sHead);
void userLogin(accNode* aHead, stuNode* sHead);
void displayMainMenu();

int getValidInput(int min, int max);
void inputHiddenPassword(char* inputPassword);
char authentication(const accNode* aHead, const char* inputUserName, const char* inputPassword);
void wait();
//学生端
void displayStudentMenu();

//教师端

//管理员端
void adminMenu(accNode* aHead);
void displayAdminMenu();

void addAccount(accNode* aHead);
void deleteAccount(accNode* aHead);
void pagePrintingAccount(const accNode* aHead, const int pageSize);
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
