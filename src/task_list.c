#include <stdio.h>
#include <string.h>
#include "task_list.h"

// ==== Validare data pentru editare ====
static int isLeapYearInt(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int isValidDateInt(int day, int month, int year) {
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12)   return 0;
    if (day < 1)                   return 0;

    int daysInMonth;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31; break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30; break;
        case 2:
            daysInMonth = isLeapYearInt(year) ? 29 : 28;
            break;
        default:
            return 0;
    }

    if (day > daysInMonth) return 0;
    return 1;
}

int existsTaskId(TaskList *list, int id) {
    for (int i = 0; i < list->count; i++) {
        if (list->tasks[i].id == id) {
            return 1;  // ID deja exista
        }
    }
    return 0; // ID liber
}

void initTaskList(TaskList *list){
    list->count = 0;
}

void addTask(TaskList *list,Task task){
    if (list->count > MAX_TASKS){
    printf("Lista taskuri este plina\n");
    return;
    }
    list->tasks[list->count] = task;
    list->count++;
}

void deleteTask(TaskList *list, int id){
    if(list->count == 0){
        printf("Lista este goala\n");
        return;
    }
    int found = -1;

    for (int i=0;i<list->count;i++){
        if (list->tasks[i].id == id){
            found = i;
            break;
        }
    }
    if (found == -1){
        printf("Taskul cu id %d nu a fost gasit\n");
        return;
    }

    for(int i=found;i<list->count-1;i++){
        list->tasks[i] = list->tasks[i+1];
    }
    list->count --;
    printf("task sters cu succes\n");
}

void editTask(TaskList *list, int id) {
    int index = -1;

    for (int i = 0; i < list->count; i++) {
        if (list->tasks[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Task-ul nu exista.\n");
        return;
    }

    Task *t = &list->tasks[index];

    printf("Titlu nou: ");
    fgets(t->title, TITLE_LEN, stdin);
    t->title[strcspn(t->title, "\n")] = '\0';

    printf("Descriere noua: ");
    fgets(t->description, DESC_LEN, stdin);
    t->description[strcspn(t->description, "\n")] = '\0';

    printf("Prioritate noua (1-5): ");
    scanf("%d", &t->priority);

    int day, month, year;
    int c;

    //  aici facem VALIDAREA datei
    while (1) {
        printf("Deadline nou (zi luna an): ");
        if (scanf("%d %d %d", &day, &month, &year) != 3) {
            printf("Input invalid. Introdu 3 numere (zi luna an).\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        while ((c = getchar()) != '\n' && c != EOF) {}

        if (!isValidDateInt(day, month, year)) {
            printf("Data invalida. Introdu o data calendaristica reala.\n");
            continue;
        }

        // data e valida -> o salvam
        t->deadline.day   = day;
        t->deadline.month = month;
        t->deadline.year  = year;
        break;
    }

    printf("Status nou (0=TODO,1=IN_PROGRESS,2=BLOCKED,3=DONE): ");
    scanf("%d", (int *)&t->status);

    printf("Timp estimat nou (minute): ");
    scanf("%d", &t->estimatedMinutes);

    printf("Task modificat cu succes!\n");
}

void sortTasksByPriority(TaskList *list) {
    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (list->tasks[j].priority < list->tasks[j + 1].priority) {
                Task temp = list->tasks[j];
                list->tasks[j] = list->tasks[j + 1];
                list->tasks[j + 1] = temp;
            }
        }
    }
    printf("Sortare dupa prioritate efectuata!\n");
}

int compareDates(Date a, Date b) {
    if (a.year != b.year) return a.year - b.year;
    if (a.month != b.month) return a.month - b.month;
    return a.day - b.day;
}

void sortTasksByDeadline(TaskList *list) {
    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (compareDates(list->tasks[j].deadline, list->tasks[j + 1].deadline) > 0) {
                Task temp = list->tasks[j];
                list->tasks[j] = list->tasks[j + 1];
                list->tasks[j + 1] = temp;
            }
        }
    }
    printf("Sortare dupa deadline efectuata!\n");
}

void printAllTasks(const TaskList *list){
    if (list->count == 0){
        printf("Nu exista taskuri\n");
        return;
    }
    printf("\n=== Toate taskurile===\n");
    for (int i=0;i<list->count;i++)
    {
       printTask(&list->tasks[i]);
    }
}