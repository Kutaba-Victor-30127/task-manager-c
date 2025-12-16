#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input_utils.h"
#include "task.h"
#include "task_list.h"
#include "task_storage.h"

// MENIUL
void printMenu(void) {
    printf("\n=== TASK MANAGER ===\n");
    printf("1. Adaugare Task\n");
    printf("2. Afisare Task-uri\n");
    printf("3. Sterge Task\n");
    printf("4. Editare Task\n");
    printf("5. Sorteaza dupa Prioritate\n");
    printf("6. Sorteaza dupa Deadline\n");
    printf("7. Cauta Task dupa titlu/descriere\n");
    printf("8. Afiseaza Task-urile dupa Status\n");

    printf("0. Iesire\n");
    
}

// input optiune meniu
int readManuOption(void){
    return readIntInRange("Alege optiunea: ",0,8);
}


int main(void) {
    TaskList list;
    initTaskList(&list);

    // INCARCA din fisier la pornire
    loadTasksFromFile(&list, "data/tasks.dat");

    int option = -1;

    do {
      printMenu();
      option = readManuOption();

        switch (option) {
            case 1: {
                int id, priority, minutes;
                int statusChoice;
                char title[TITLE_LEN];
                char description[DESC_LEN];

                while (1) {
                    id = readPositiveInt("Id: ");
                    if (existsTaskId(&list,id)){
                        printf("Acest ID exista deja. Alege alt ID\n");
                        continue;
                    }
                    break;
                }

                printf("Titlu: ");
                if (!fgets(title, TITLE_LEN, stdin)){
                    printf("Eroare la citire titlu\n");
                    continue;
                }
                title[strcspn(title, "\n")] = '\0';

                printf("Descriere: ");
                if (!fgets(description, DESC_LEN, stdin)){
                    printf("Eroare la citire descriere\n");
                    continue;
                }
                description[strcspn(description, "\n")] = '\0';

                priority = readIntInRange("Prioritatea (1-5): ", 1, 5);
                
                Date d = readDate();

                statusChoice = readIntInRange(
                "Status (0=TODO,1=IN_PROGRESS,2=BLOCKED,3=DONE): ",
                0, 3
                );

                minutes = readIntInRange("Timp estimat (minute): ", 1, 1000);

                Task t = createTask(
                    id,
                    title,
                    description,
                    priority,
                    d,
                    (TaskStatus)statusChoice,
                    minutes
                );

                addTask(&list, t);
                printf("Task adaugat cu succes!\n");
                saveTasksToFile(&list, "data/tasks.dat");
                break;
            }

            case 2:
                printAllTasks(&list);
                break;

            case 3: {
                int id = readPositiveInt("ID-ul task-ului de sters: ");
                deleteTask(&list,id);
                saveTasksToFile(&list, "data/tasks.dat");
                break;
            }    
            
            case 4: {
                int id = readPositiveInt("ID-ul task-ului de editat: ");
                editTask(&list,id);
                saveTasksToFile(&list, "data/tasks.dat");
                break;
            }

            case 5:
            sortTasksByPriority(&list);
            printf("Task-urile au fost sortate dupa prioritate (descrescator).\n");
            break;

            case 6:
            sortTasksByDeadline(&list);
            printf("Task-urile au fost sortate dupa deadline (crescator).\n");
            break;

            case 7: {
                char query[128];

                printf("Cauta dupa titlu/descriere: ");
                if (!fgets(query,sizeof(query),stdin)){
                    printf("Eroare la citire\n");
                    break;
                }
                query[strcspn(query,"\r\n")] = '\0';
                searchTaskByTitle(&list,query);
                break;

            }
            
            case 8: {
                int statusChoice = readIntInRange(
                "Status (0=TODO,1=IN_PROGRESS,2=BLOCKED,3=DONE): ",
                0, 3
                );
                printTaskByStatus(&list,(TaskStatus)statusChoice);
                break;
            }

            case 0:
                printf("Iesire...\n");
                break;

            default:
                printf("Optiune invalida!\n");
                break;
        }

    } while (option != 0);

    // SALVEAZA in fisier la iesire
    saveTasksToFile(&list, "data/tasks.dat");

    return 0;
}
