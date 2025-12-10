# Task Manager în C (consolă)

Aplicație de tip consolă pentru gestionarea task-urilor, scrisă în C, gândită ca proiect de învățare pentru structurarea codului, lucru cu fișiere și validare de input.

## Funcționalități

- Adăugare task cu:
  - **ID unic** (număr pozitiv, validat – nu acceptă litere)
  - titlu
  - descriere
  - prioritate (1–5)
  - deadline (dată calendaristică reală, validată)
  - status: `TODO / IN_PROGRESS / BLOCKED / DONE`
  - timp estimat (minute)
- Afișare toate task-urile
- Ștergere task după ID
- Editare task existent
- Sortare:
  - după prioritate (descrescător)
  - după deadline (crescător)
- Persistență:
  - task-urile sunt salvate în `data/tasks.dat`
  - se încarcă automat la pornirea programului
  - se salvează automat după adăugare / ștergere / editare

## Structura proiectului

```text
TASK MANAGER/
├── src/
│   ├── main.c            # logica meniului + validare input
│   ├── task.h            # definiția Task, Date, TaskStatus
│   ├── task.c            # createTask, printTask
│   ├── task_list.h       # structura TaskList + prototipuri
│   ├── task_list.c       # add, delete, edit, sort, existsTaskId
│   ├── task_storage.h    # prototipuri pentru load/save
│   ├── task_storage.c    # salvare/încărcare în fișier binar
└── data/
    └── tasks.dat         # fișierul cu task-uri (generat la rulare)
