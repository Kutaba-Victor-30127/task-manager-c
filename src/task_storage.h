#ifndef TASK_STORAGE_H
#define TASK_STORAGE_H

#include "task_list.h"   // aici e definit TaskList si Task

// returneaza 1 daca reuseste, 0 daca nu
int saveTasksToFile(const TaskList *list, const char *filename);
int loadTasksFromFile(TaskList *list, const char *filename);

#endif
