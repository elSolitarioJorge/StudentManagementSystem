cmake_minimum_required(VERSION 3.29)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 11)

set(INC_DIR ./include)
set(LINK_DIR ./dll)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(StudentManagementSystem main.c
        student_management_system.h
        login.c
        student.c
        teacher.c
        file.c
        admin.c
)

target_link_libraries(StudentManagementSystem libcrypto.dll)