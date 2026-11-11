#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#include <stdio.h>

#define ID_LEN 32
#define NAME_LEN 80
#define DOB_LEN 16
#define CONTACT_LEN 24
#define EMAIL_LEN 100
#define DB_FILE "students.db"

typedef struct Student {
    char id[ID_LEN];
    char name[NAME_LEN];
    char dob[DOB_LEN];
    float matric_percent;
    float inter_percent;
    float graduation_percent;
    char contact[CONTACT_LEN];
    char email[EMAIL_LEN];
    struct Student *next;
} Student;

void read_line(const char *prompt, char *buffer, size_t size);
int read_int(const char *prompt, int min, int max);
float read_percentage(const char *prompt);
Student *find_record(Student *head, const char *id);
int add_record(Student **head);
void print_records(const Student *head, int reverse);
int delete_record(Student **head);
int edit_record(Student *head);
void find_and_print_record(Student *head);
void free_records(Student *head);
Student *load_records(void);
int save_records(const Student *head);

#endif
