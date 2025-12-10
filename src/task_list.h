#ifndef TASK_LIST_H
#define TASK_LIST_H

#include "task.h"

#define MAX_TASKS 1000

typedef struct{
    Task tasks[MAX_TASKS];
    int count;
}TaskList;

int existsTaskId(TaskList *list, int id);
void initTaskList(TaskList *list);
void addTask(TaskList *list, Task task);
void deleteTask(TaskList *list, int id);
void editTask(TaskList *list, int id);
void sortTasksByPriority(TaskList *list);
void sortTasksByDeadline(TaskList *list);
void printAllTasks(const TaskList *list);

#endif