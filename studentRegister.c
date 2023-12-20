#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LINES 3
#define MAX_ADDRESS_LENGTH 100

// Student structure
struct Student {
    char name[MAX_NAME_LENGTH];
    int roll;
    char telephone[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LINES][MAX_ADDRESS_LENGTH];
};

// Student Register structure
struct SReg {
    struct Student students[MAX_STUDENTS];
    int count;
};

// Function prototypes
int add(struct SReg *sr, struct Student s);
struct Student get(struct SReg *sr, int r);
int deleteStudent(struct SReg *sr, int r);
int modify(struct SReg *sr, struct Student s);
void sortStudents(struct SReg *sr);
int getCount(struct SReg *sr);
void exportToFile(struct SReg *sr, const char *fname);
int exportBin(struct SReg *sr, const char *fname);
void sortBin(const char *fname);
int loadBin(struct SReg *sr, const char *fname);

// Helper function for comparing student records for sorting
int compareStudents(const void *a, const void *b) {
    return strcmp(((struct Student *)a)->name, ((struct Student *)b)->name);
}

// Function to get student details from the user
struct Student getStudentDetails() {
    struct Student s;
    printf("Enter student name (Last, First): ");
    fgets(s.name, MAX_NAME_LENGTH, stdin);
    printf("Enter student roll number: ");
    scanf("%d", &s.roll);
    getchar(); // Consume the newline character left by scanf
    printf("Enter student telephone: ");
    fgets(s.telephone, MAX_NAME_LENGTH, stdin);
    printf("Enter student address (up to %d lines, empty line to stop):\n", MAX_ADDRESS_LINES);
    for (int i = 0; i < MAX_ADDRESS_LINES; i++) {
        fgets(s.address[i], MAX_ADDRESS_LENGTH, stdin);
        if (s.address[i][0] == '\n') {
            // Empty line, stop taking address lines
            s.address[i][0] = '\0';
            break;
        }
    }
    return s;
}

int add(struct SReg *sr, struct Student s) {
    if (sr->count >= MAX_STUDENTS)
        return 0;

    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == s.roll)
            return 0;
    }

    sr->students[sr->count] = s;
    sr->count++;
    return 1;
}

struct Student get(struct SReg *sr, int r) {
    struct Student emptyStudent = { "", 0, "", { "" } };
    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == r)
            return sr->students[i];
    }

    return emptyStudent;
}

int deleteStudent(struct SReg *sr, int r) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == r) {
            for (int j = i; j < sr->count - 1; j++) {
                sr->students[j] = sr->students[j + 1];
            }
            sr->count--;
            return 1;
        }
    }

    return 0;
}

int modify(struct SReg *sr, struct Student s) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == s.roll) {
            sr->students[i] = s;
            return 1;
        }
    }
    return 0;
}

void sortStudents(struct SReg *sr) {
    for (int i = 0; i < sr->count - 1; i++) {
        for (int j = 0; j < sr->count - i - 1; j++) {
            if (strcmp(sr->students[j].name, sr->students[j + 1].name) > 0) {
                struct Student temp = sr->students[j];
                sr->students[j] = sr->students[j + 1];
                sr->students[j + 1] = temp;
            }
        }
    }
}

int getCount(struct SReg *sr) {
    return sr->count;
}

void exportToFile(struct SReg *sr, const char *fname) {
    FILE *outfile = fopen(fname, "w");
    if (outfile != NULL) {
        for (int i = 0; i < sr->count; i++) {
            fprintf(outfile, "%s,%d,%s", sr->students[i].name, sr->students[i].roll, sr->students[i].telephone);
            for (int j = 0; j < MAX_ADDRESS_LINES; j++) {
                if (strlen(sr->students[i].address[j]) > 0) {
                    fprintf(outfile, ",%s", sr->students[i].address[j]);
                }
            }
            fprintf(outfile, "\n");
        }
        fclose(outfile);
    }
}

void loadFromFile(struct SReg *sr, const char *fname) {
    FILE *infile = fopen(fname, "r");
    if (infile != NULL) {
        struct Student s;
        while (fscanf(infile, "%[^,],%d,%[^,],%[^,^\n]\n",
                      s.name, &s.roll, s.telephone, s.address[0]) == 4) {
            // Read additional address lines
            for (int i = 1; i < MAX_ADDRESS_LINES; i++) {
                fscanf(infile, ",%[^,^\n]\n", s.address[i]);
            }
            add(sr, s);
        }
        fclose(infile);
    }
}
                                                                                                                                                           
int main() {
    struct SReg studentRegister = { .count = 0 };
    int choice;
    char fname[] = "student_register.bin";

    do {
        printf("\nChoose an operation:\n");
        printf("1. Add student\n");
        printf("2. Get student\n");
        printf("3. Delete student\n");
        printf("4. Modify student\n");
        printf("5. Sort students\n");
        printf("6. Get student count\n");
        printf("7. Export student register to file (binary)\n");
        printf("8. Load student register from file (binary)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        switch (choice) {
            case 1: {
                struct Student newStudent = getStudentDetails();
                if (add(&studentRegister, newStudent)) {
                    printf("Student added successfully.\n");
                } else {
                    printf("Failed to add student. Either the student already exists or the student register is full.\n");
                }
                break;
            }
            case 2: {
                int rollNumber;
                printf("Enter roll number to get student details: ");
                scanf("%d", &rollNumber);
                getchar(); // Consume the newline character left by scanf
                struct Student foundStudent = get(&studentRegister, rollNumber);
                if (foundStudent.roll != 0) {
                    printf("Student found:\n");
                    printf("Name: %s\n", foundStudent.name);
                    printf("Roll: %d\n", foundStudent.roll);
                    printf("Telephone: %s\n", foundStudent.telephone);
                    printf("Telephone: %s\n", foundStudent.telephone);
                    printf("Address:\n");
                    for (int i = 0; i < MAX_ADDRESS_LINES; i++) {
                        if (foundStudent.address[i][0] != '\0') {
                            printf("%s", foundStudent.address[i]);
                        }
                    }
                    printf("\n");
                } else {
                    printf("Student with roll number %d not found.\n", rollNumber);
                }
                break;
            }
            case 3: {
                int rollNumber;
                printf("Enter roll number to delete student: ");
                scanf("%d", &rollNumber);
                getchar(); // Consume the newline character left by scanf
                if (deleteStudent(&studentRegister, rollNumber)) {
                    printf("Student with roll number %d deleted.\n", rollNumber);
                } else {
                    printf("Student with roll number %d not found.\n", rollNumber);
                }
                break;
            }
            case 4: {
                struct Student newStudent = getStudentDetails();
                if (modify(&studentRegister, newStudent)) {
                    printf("Student modified successfully.\n");
                } else {
                    printf("Failed to modify student. Student with the provided roll number does not exist.\n");
                }
                break;
            }
            case 5: {
                sortStudents(&studentRegister);
                printf("Students sorted successfully.\n");
                break;
            }
            case 6: {
                int count = getCount(&studentRegister);
                printf("Number of students in the register: %d\n", count);
                break;
            }
            case 0: {
                printf("Exiting the program. Goodbye!\n");
                break;
            }
            default: {
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
