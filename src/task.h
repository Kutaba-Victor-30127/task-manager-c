#ifndef TASK_H
#define TASK_H

#define TITLE_LEN 100
#define DESC_LEN  256
#define MAX_TASKS 1000


typedef enum {
    STATUS_TODO,
    STATUS_IN_PROGRESS,
    STATUS_BLOCKED,
    STATUS_DONE
} TaskStatus;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char title[TITLE_LEN];
    char description[DESC_LEN];
    int priority;
    Date deadline;
    TaskStatus status;
    int estimatedMinutes;
} Task;

void printTask(const Task *t);

Task createTask(int id,
                const char *title,
                const char *description,
                int priority,
                Date deadline,
                TaskStatus status,
                int estimatedMinutes);


#endif
