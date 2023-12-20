#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    char *name;
    int roll;
    char telephone[11];
    char *address;
} Student;

typedef struct SReg
{
    int count;
    Student **arrStudPtr;

} SReg;

Student *createstudentrecord(int max_stud, Student *ptr)
{
    char tempstr[50];

    if (ptr == NULL)
    {
        printf("ERROR! null student pointer\n");
        return 0;
    }

    getchar();
    printf("Enter the details of the student: ");

    printf("Enter name: ");
    fgets(tempstr, 50, stdin);

    ptr->name = (char *)malloc(strlen(tempstr) + 1);
    strcpy(ptr->name, tempstr);

    printf("Enter the roll no.: ");
    scanf("%d", &ptr->roll);

    printf("Enter the telephone no.: ");
    scanf("%s", ptr->telephone);

    getchar();

    printf("Enter the address: ");
    fgets(tempstr, 50, stdin);

    ptr->address = (char *)malloc(strlen(tempstr) + 1);
    strcpy(ptr->address, tempstr);

    return ptr;
}

void freestudentrecord(Student *ptr)
{
    free(ptr->name);
    ptr->name = NULL;
    free(ptr->address);
    ptr->address = NULL;
    free(ptr);
    ptr = NULL;
}

int printstudentdata(Student *ptr)
{
    if (ptr == NULL)
    {
        printf("ERROR! null student pointer\n");
        return 0;
    }

    printf("Name: ");
    fputs(ptr->name, stdout);
    printf("roll no.: %d\n", ptr->roll);
    printf("telephone: %s\n", ptr->telephone);
    printf("address: ");
    fputs(ptr->address, stdout);
}

int add(SReg *sr, Student *ptr)
{

    if (ptr == NULL)
    {
        printf("ERROR! null student pointer\n");
        return 0;
    }

    int n = sr->count;
    printf("%d\n", n);
    fputs(ptr->name, stdout);
    printf("%d\n", ptr->roll);
    printf("%s\n", ptr->telephone);
    for (int i = 0; i < n; i++)
    {

        if (sr->arrStudPtr[i]->roll == ptr->roll)
        {
            return 0;
        }
    }

    sr->arrStudPtr[n] = ptr;
    sr->count++;
    // printf("%s\n", sr->arrStudPtr[1]->telephone);
    // printf("%d\n", sr->arrStudPtr[1]->roll);
    return 1;
}

Student get(SReg sr, int r)
{
    for (int i = 0; i < sr.count; i++)
    {
        if (sr.arrStudPtr[i]->roll == r)
            return *(sr.arrStudPtr[i]);
    }
    Student empty = {"", 0, "", ""};
    return empty;
}

int delete(SReg *sr, int r)
{
    int n = sr->count;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (sr->arrStudPtr[i]->roll == r)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        return 0;
    }
    else
    {
        for (int i = index; i < n - 1; i++)
        {
            sr->arrStudPtr[i] = sr->arrStudPtr[i + 1];
        }
        printf("deleted\n");
        sr->count = n - 1;
        return 1;
    }
}

int modify(SReg *sr, Student *ptr)
{
    int n = sr->count;
    for (int i = 0; i < n; i++)
    {
        if (sr->arrStudPtr[i]->roll == ptr->roll)
        {
            strcpy(sr->arrStudPtr[i]->name, ptr->name);
            sr->arrStudPtr[i]->roll, ptr->roll;
            strcpy(sr->arrStudPtr[i]->telephone, ptr->telephone);
            strcpy(sr->arrStudPtr[i]->address, ptr->address);
            return 1;
        }
    }
    return 0;
}

void sortStudent(SReg *sr)
{
    int n = sr->count;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strcmp(sr->arrStudPtr[j]->name, sr->arrStudPtr[j + 1]->name) > 0)
            {
                Student *temp = sr->arrStudPtr[j];
                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];
                sr->arrStudPtr[j + 1] = temp;
            }
        }
    }
}

int getCount(SReg *sr)
{
    int n = sr->count;
    return n;
}

void export(SReg *sr, char fname[20])
{
    FILE *f1 = fopen(fname, "w");
    int n = sr->count;
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %s %s \n", sr->arrStudPtr[i]->name, sr->arrStudPtr[i]->roll, sr->arrStudPtr[i]->telephone, sr->arrStudPtr[i]->address);
    }
    printf("saved %d entries.\n", n);
}
void load(SReg *sr, char fname[20])
{
    FILE *f1 = fopen(fname, "r");
    int n = sr->count;
    int size = 0;
    char ch;
    while ((ch = getc(f1)) != EOF)
    {
        if (ch == '\n')
            size++;
    }
    fseek(f1, 0, SEEK_SET);
    for (int i = 0; i < size; i++)
    {
        fscanf(f1, "%s %d %s %s \n", sr->arrStudPtr[n]->name, &(sr->arrStudPtr[n]->roll), sr->arrStudPtr[n]->telephone, sr->arrStudPtr[n]->address);
        n++;
    }
    sr->count = n;
    printf("loaded %d entries.\n", sr->count);
} 
int main()
{

    SReg sr;
    Student ptr;
    int max_stud = 0;
    sr.count = 0;
    int r;

    printf("input maximum student= ");
    scanf("%d", &max_stud);

    sr.arrStudPtr = (Student **)malloc(max_stud * sizeof(Student *));

    for (int i = 0; i < max_stud; i++)
    {
        sr.arrStudPtr[i] = (Student *)malloc(sizeof(Student));
        sr.arrStudPtr[i] = NULL;
    }

    for (int i = 0; i < max_stud; i++)
    {
        createstudentrecord(max_stud, &ptr);
        printf("-x-x-x-\n");
        printstudentdata(&ptr);
        printf("-x-x-x-\n");
        (add(&sr, &ptr) == 1) ? printf("Added\n") : printf("Not Added\n");
    }
    printf("Enter the roll no. whose detail you want: ");
    scanf("%d", &r);

    Student sget=get(sr, r);
    printf("Name: %s\nRoll No.: %d\nTelephone: %s\nAddress: %s",sget.name,sget.roll,sget.telephone,sget.address);
}

