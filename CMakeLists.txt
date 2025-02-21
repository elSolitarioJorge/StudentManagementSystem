cmake_minimum_required(VERSION 3.29)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 11)

set(OPENSSL_ROOT_DIR "C:\\Program Files\\OpenSSL-Win64")
include_directories(${OPENSSL_ROOT_DIR}/include)
link_directories(${OPENSSL_ROOT_DIR}/lib)

add_executable(StudentManagementSystem main.c
        student_management_system.h
        login.c
        student.c
        teacher.c
        file.c
        admin.c
)

target_link_libraries(StudentManagementSystem PRIVATE
        libssl.lib
        libcrypto.lib
)