#include <stdio.h>
#include <string.h>
#include "task.h"


const char* statusToString(TaskStatus status) {
    switch (status) {
        case STATUS_TODO:        return "TODO";
        case STATUS_IN_PROGRESS: return "IN PROGRESS";
        case STATUS_BLOCKED:     return "BLOCKED";
        case STATUS_DONE:        return "DONE";
        default:                 return "UNKNOWN";
    }
}

void printTask(const Task *t) {
    if (t == NULL) {
        printf("Task NULL\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("ID: %d\n", t->id);
    printf("Title: %s\n", t->title);
    printf("Description: %s\n", t->description);
    printf("Priority: %d/5\n", t->priority);
    printf("Deadline: %02d-%02d-%04d\n",
           t->deadline.day, t->deadline.month, t->deadline.year);
    printf("Status: %s\n", statusToString(t->status));
    printf("Estemated time: %d minutes\n",t->estimatedMinutes);
    printf("--------------------------------------------------\n");
}

Task createTask(int id,
                const char *title,                             
                const char *description,
                int priority,
                Date deadline,
                TaskStatus status,
                int estimatedMinutes)
 {
    Task t;
    t.id = id;
    strncpy(t.title,title, TITLE_LEN - 1);
    t.title[TITLE_LEN - 1] = '\0';

    strncpy(t.description,description,DESC_LEN -1);
    t.description[DESC_LEN - 1] = '\0';

    t.priority = priority;
    t.deadline = deadline;
    t.status = status;
    t.estimatedMinutes = estimatedMinutes;

    return t;

}



