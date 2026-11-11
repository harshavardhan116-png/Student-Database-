#include "student_db.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int save_records(const Student *head)
{
    FILE *fp = fopen(DB_FILE, "w");
    if (fp == NULL) {
        perror("Could not open database file for writing");
        return 0;
    }

    while (head != NULL) {
        if (fprintf(fp, "%s|%s|%s|%.2f|%.2f|%.2f|%s|%s\n",
                    head->id, head->name, head->dob, head->matric_percent,
                    head->inter_percent, head->graduation_percent,
                    head->contact, head->email) < 0) {
            perror("Error writing database file");
            fclose(fp);
            return 0;
        }
        head = head->next;
    }

    if (fclose(fp) != 0) {
        perror("Error closing database file");
        return 0;
    }
    puts("Database saved successfully.");
    return 1;
}

static int parse_record(char *line, Student *s)
{
    char *fields[8];
    char *p = line;
    int i;
    for (i = 0; i < 8; ++i) {
        fields[i] = p;
        if (i < 7) {
            p = strchr(p, '|');
            if (p == NULL) return 0;
            *p++ = '\0';
        }
    }
    if (strchr(fields[7], '|') != NULL) return 0;
    fields[7][strcspn(fields[7], "\r\n")] = '\0';

    if (strlen(fields[0]) >= sizeof s->id ||
        strlen(fields[1]) >= sizeof s->name ||
        strlen(fields[2]) >= sizeof s->dob ||
        strlen(fields[6]) >= sizeof s->contact ||
        strlen(fields[7]) >= sizeof s->email) return 0;

    strcpy(s->id, fields[0]);
    strcpy(s->name, fields[1]);
    strcpy(s->dob, fields[2]);
    strcpy(s->contact, fields[6]);
    strcpy(s->email, fields[7]);

    {
        char *end;
        s->matric_percent = strtof(fields[3], &end);
        if (*end != '\0' || s->matric_percent < 0 || s->matric_percent > 100) return 0;
        s->inter_percent = strtof(fields[4], &end);
        if (*end != '\0' || s->inter_percent < 0 || s->inter_percent > 100) return 0;
        s->graduation_percent = strtof(fields[5], &end);
        if (*end != '\0' || s->graduation_percent < 0 || s->graduation_percent > 100) return 0;
    }
    return s->id[0] != '\0';
}

Student *load_records(void)
{
    FILE *fp = fopen(DB_FILE, "r");
    Student *head = NULL, *tail = NULL;
    char line[512];

    if (fp == NULL) {
        if (errno != ENOENT) perror("Could not open database file");
        return NULL;
    }
    while (fgets(line, sizeof line, fp) != NULL) {
        Student *node = (Student *)calloc(1, sizeof *node);
        if (node == NULL) {
            puts("Memory allocation failed while loading database.");
            break;
        }
        if (!parse_record(line, node) || find_record(head, node->id) != NULL) {
            puts("Warning: skipped invalid or duplicate record in database file.");
            free(node);
            continue;
        }
        node->next = NULL;
        if (head == NULL) head = node;
        else tail->next = node;
        tail = node;
    }
    fclose(fp);
    return head;
}
