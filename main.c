#include "student_db.h"
#include <ctype.h>

static void show_menu(void)
{
    puts("\n------------------ MENU ------------------");
    puts("a/A : Add a new student record");
    puts("p/P : Print records");
    puts("s/S : Save database to file");
    puts("d/D : Delete a record");
    puts("e/E : Edit a record");
    puts("f/F : Find a student");
    puts("r/R : Reverse display order (database unchanged)");
    puts("q/Q : Quit");
    puts("------------------------------------------");
}

int main(void)
{
    Student *head = load_records();
    char choice_line[32];
    int running = 1;

    puts("Student Database Management System");
    while (running) {
        show_menu();
        read_line("Enter choice: ", choice_line, sizeof choice_line);
        if (choice_line[0] == '\0') continue;

        switch (tolower((unsigned char)choice_line[0])) {
            case 'a':
                add_record(&head);
                break;
            case 'p':
                print_records(head, 0);
                break;
            case 's':
                save_records(head);
                break;
            case 'd':
                delete_record(&head);
                break;
            case 'e':
                edit_record(head);
                break;
            case 'f':
                find_and_print_record(head);
                break;
            case 'r':
                print_records(head, 1);
                break;
            case 'q':
                puts("Quit selected. Save first if you want to keep recent changes.");
                running = 0;
                break;
            default:
                puts("Invalid menu option.");
                break;
        }
    }

    free_records(head);
    return 0;
}
