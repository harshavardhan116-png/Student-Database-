# Student-Database-
A modular C mini-project that manages student records using a singly linked list, dynamic memory allocation, and file handling. It supports adding, searching, editing, deleting, and reverse-displaying student details (ID, name, DOB, percentages, contact, email) with input validation and persistent storage in a pipe-delimited students.db file.
Student Database Management System
A C mini-project that manages student records using structures, pointers, dynamic memory allocation, a singly linked list, and file handling.
Features
Add student records with unique Student IDs
Display all records and display them in reverse order
Save records to a file and reload them at startup
Delete, edit, and search records
Store name, date of birth, three percentage values, contact number, and email
Project files
File
Description
main.c
Menu and program entry point
student_db.h
Student structure, constants, and function declarations
input.c
Input, integer, and percentage input functions
student.c
Add, display, delete, edit, search, and free student records
database_file.c
Load records from and save records to the database file
Makefile
Build instructions
Requirements
GCC compiler
GNU Make
Linux, macOS, or Windows with MinGW/MSYS2
Compile and run on Linux/macOS
make
./dataBase
To compile without Make:
gcc -std=c11 -Wall -Wextra -Wpedantic main.c input.c student.c database_file.c -o dataBase
Menu options
Choice
Operation
a
Add a student
p
Print all records
s
Save records to students.db
d
Delete a record by Student ID
e
Edit a record by Student ID
f
Find a record by Student ID
r
Print records in reverse order
q
Quit
The edit submenu allows changes to the name, date of birth, all three percentages, contact number, or email ID.
Data persistence
The program loads students.db when it starts. After adding, editing, or deleting records, choose s to save the changes. The file is created in the current working directory. Quitting does not automatically save changes.
Percentage values must be between 0 and 100. Student IDs must be unique. Text fields cannot contain the | character because it separates fields in the database file.
