#include <stdio.h>
#include "task_storage.h"

int saveTasksToFile(const TaskList *list, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Nu pot deschide fisierul %s pentru scriere.\n", filename);
        return 0;
    }

    // salvam count + toate task-urile
    if (fwrite(&list->count, sizeof(int), 1, f) != 1) {
        printf("Eroare la scrierea numarului de task-uri.\n");
        fclose(f);
        return 0;
    }

    if (list->count > 0) {
        if (fwrite(list->tasks, sizeof(Task), list->count, f) != (size_t)list->count) {
            printf("Eroare la scrierea task-urilor.\n");
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

int loadTasksFromFile(TaskList *list, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        // nu exista fisierul, nu e o tragedie
        list->count = 0;
        return 0;
    }

    int count = 0;
    if (fread(&count, sizeof(int), 1, f) != 1) {
        printf("Eroare la citirea numarului de task-uri.\n");
        fclose(f);
        list->count = 0;
        return 0;
    }

    if (count > MAX_TASKS) {
        count = MAX_TASKS;
    }

    if (count > 0) {
        if (fread(list->tasks, sizeof(Task), count, f) != (size_t)count) {
            printf("Eroare la citirea task-urilor.\n");
            fclose(f);
            list->count = 0;
            return 0;
        }
    }

    list->count = count;
    fclose(f);
    return 1;
}
