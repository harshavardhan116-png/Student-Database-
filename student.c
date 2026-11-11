#include "student_db.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int has_delimiter(const char *s)
{
    return strchr(s, '|') != NULL || strchr(s, '\n') != NULL || strchr(s, '\r') != NULL;
}

Student *find_record(Student *head, const char *id)
{
    while (head != NULL) {
        if (strcmp(head->id, id) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

int add_record(Student **head)
{
    Student *node, *tail;
    char id[ID_LEN];

    if (head == NULL) return 0;

    read_line("Student ID: ", id, sizeof id);
    if (id[0] == '\0' || has_delimiter(id)) {
        puts("Student ID cannot be empty or contain '|'.");
        return 0;
    }
    if (find_record(*head, id) != NULL) {
        puts("Error: this Student ID already exists.");
        return 0;
    }

    node = (Student *)calloc(1, sizeof *node);
    if (node == NULL) {
        puts("Memory allocation failed.");
        return 0;
    }
    strcpy(node->id, id);

    read_line("Student name: ", node->name, sizeof node->name);
    read_line("Date of birth (DD-MM-YYYY): ", node->dob, sizeof node->dob);
    node->matric_percent = read_percentage("Matriculation percentage: ");
    node->inter_percent = read_percentage("Intermediate/Diploma percentage: ");
    node->graduation_percent = read_percentage("Graduation percentage: ");
    read_line("Contact number: ", node->contact, sizeof node->contact);
    read_line("Email ID: ", node->email, sizeof node->email);

    if (node->name[0] == '\0' || node->dob[0] == '\0' ||
        node->contact[0] == '\0' || node->email[0] == '\0' ||
        has_delimiter(node->name) || has_delimiter(node->dob) ||
        has_delimiter(node->contact) || has_delimiter(node->email)) {
        puts("A text field was empty or contained '|'. Record not added.");
        free(node);
        return 0;
    }

    node->next = NULL;
    if (*head == NULL) {
        *head = node;
    } else {
        tail = *head;
        while (tail->next != NULL) tail = tail->next;
        tail->next = node;
    }
    puts("Student record added.");
    return 1;
}

static void print_one(const Student *s)
{
    printf("\nID: %s\nName: %s\nDOB: %s\n"
           "Matriculation: %.2f%%\nIntermediate/Diploma: %.2f%%\n"
           "Graduation: %.2f%%\nContact: %s\nEmail: %s\n",
           s->id, s->name, s->dob, s->matric_percent, s->inter_percent,
           s->graduation_percent, s->contact, s->email);
}

static void print_reverse(const Student *head)
{
    if (head == NULL) return;
    print_reverse(head->next);
    print_one(head);
}

void print_records(const Student *head, int reverse)
{
    if (head == NULL) {
        puts("Database is empty.");
        return;
    }
    if (reverse) {
        puts("\n--- Records in reverse display order (database unchanged) ---");
        print_reverse(head);
    } else {
        const Student *cur = head;
        puts("\n--- Student Database ---");
        while (cur != NULL) {
            print_one(cur);
            cur = cur->next;
        }
    }
}

int delete_record(Student **head)
{
    char id[ID_LEN];
    Student *cur, *prev = NULL;

    if (head == NULL || *head == NULL) {
        puts("Database is empty.");
        return 0;
    }
    read_line("Enter Student ID to delete: ", id, sizeof id);
    cur = *head;
    while (cur != NULL && strcmp(cur->id, id) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        puts("Student ID not found.");
        return 0;
    }
    if (prev == NULL) *head = cur->next;
    else prev->next = cur->next;
    free(cur);
    puts("Record deleted from memory. Choose Save to write the change to file.");
    return 1;
}

int edit_record(Student *head)
{
    char id[ID_LEN], text[NAME_LEN];
    int choice;
    Student *s;

    read_line("Enter Student ID to edit: ", id, sizeof id);
    s = find_record(head, id);
    if (s == NULL) {
        puts("Student ID not found.");
        return 0;
    }

    puts("\nEdit menu\n1. Name\n2. DOB\n3. Percentages\n4. Contact\n5. Email ID");
    choice = read_int("Select option: ", 1, 5);

    switch (choice) {
        case 1:
            read_line("New name: ", text, sizeof text);
            if (text[0] == '\0' || strchr(text, '|')) { puts("Invalid name."); return 0; }
            strcpy(s->name, text);
            break;
        case 2:
            read_line("New DOB (DD-MM-YYYY): ", text, sizeof text);
            if (text[0] == '\0' || strchr(text, '|')) { puts("Invalid DOB."); return 0; }
            strcpy(s->dob, text);
            break;
        case 3:
            s->matric_percent = read_percentage("New matriculation percentage: ");
            s->inter_percent = read_percentage("New intermediate/diploma percentage: ");
            s->graduation_percent = read_percentage("New graduation percentage: ");
            break;
        case 4:
            read_line("New contact number: ", text, sizeof text);
            if (text[0] == '\0' || strchr(text, '|')) { puts("Invalid contact."); return 0; }
            if (strlen(text) >= sizeof s->contact) { puts("Contact number too long."); return 0; }
            strcpy(s->contact, text);
            break;
        case 5:
            read_line("New email ID: ", text, sizeof text);
            if (text[0] == '\0' || strchr(text, '|')) { puts("Invalid email."); return 0; }
            if (strlen(text) >= sizeof s->email) { puts("Email too long."); return 0; }
            strcpy(s->email, text);
            break;
        default:
            return 0;
    }
    puts("Record updated in memory. Choose Save to write the change to file.");
    return 1;
}

void find_and_print_record(Student *head)
{
    char id[ID_LEN];
    Student *s;
    read_line("Enter Student ID to find: ", id, sizeof id);
    s = find_record(head, id);
    if (s == NULL) puts("Student ID not found.");
    else print_one(s);
}

void free_records(Student *head)
{
    while (head != NULL) {
        Student *next = head->next;
        free(head);
        head = next;
    }
}
