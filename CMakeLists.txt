cmake_minimum_required(VERSION 3.29)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 11)

add_executable(StudentManagementSystem main.c
        StudentManagementSystem.h
        login.c
        student.c
        teacher.c
        file.c
        admin.c
)
