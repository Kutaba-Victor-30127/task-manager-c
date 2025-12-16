#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input_utils.h"
#include "task.h"
#include "task_list.h"

static int containsIgnoreCase(const char *str,const char *sub){
    if (!str || !sub) return 0;
    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);

    if (!sub_len || sub_len>str_len) return 0;

    for (size_t i=0;i<str_len-sub_len;i++){
        size_t j = 0;
        while (j<sub_len){
            char c1 = (char)tolower((unsigned char)str[i+j]);
            char c2 = (char)tolower((unsigned char)sub[j]);
            if (c1 != c2) break;
            j++;
        }
        if (j == sub_len) return 1;
    }
    return 0;
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
        printf("Taskul cu id %d nu a fost gasit\n",id);
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
    if (!fgets(t->title, TITLE_LEN, stdin)){
        printf("Eroare la citire titlu!\n");
        return;
    }
    t->title[strcspn(t->title, "\r\n")] = '\0';

    printf("Descriere noua: ");
    if (!fgets(t->description, DESC_LEN, stdin)){
        printf("Eroare la citire descriere!\n");
        return;
    }
    t->description[strcspn(t->description, "\r\n")] = '\0';

    t->priority = readIntInRange("Prioritate noua (1-5): ",1,5);

    t->deadline = readDate();
    
    t->status = readIntInRange("Status nou (0=TODO,1=IN_PROGRESS,2=BLOCKED,3=DONE): ",0,3);

    t->estimatedMinutes = readIntInRange("Timpul nou estimat: ",1,1000);

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

void searchTaskByTitle(const TaskList *list,const char *query){
    if (!list || list->count ==0){
        printf("Nu exista Task-uri\n");
        return; 
    }
    if (!query || query[0] == '\0'){
        printf("Cuvantul de cautare este gol\n");
        return;
    }
    int found =0;
    for (int i=0;i<list->count;i++){
        const Task *t = &list->tasks[i];
        if (containsIgnoreCase(t->title,query) || containsIgnoreCase(t->description,query)){
            printTask(t);
            found = 1;
        } 
    }
        if (!found){
        printf("Nu a fost gasit niciun task care sa contina \"%s\".\n", query);
        }
    
}

void printTaskByStatus(const TaskList *list,TaskStatus status){
    if(!list || list->count == 0){
        printf("Nu exista task-uri\n");
        return;
    }
    int found = 0;

    for (int i=0;i<list->count;i++){
        if (list->tasks[i].status == status){
            printTask(&list->tasks[i]);
            found = 1;
        }
    }
    if (!found){
        printf("Nu exista task-uri cu statusul selectat\n");
    }

}