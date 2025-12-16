# Task Manager în C (CLI)

Aplicație de tip consolă pentru gestionarea task-urilor, scrisă în C.  
Proiect realizat cu scop educațional, axat pe structurarea codului, validarea inputului și lucrul cu fișiere.

---

## Funcționalități

- Adăugare task cu:
  - ID unic (număr pozitiv, validat – nu acceptă litere)
  - titlu
  - descriere
  - prioritate (1–5)
  - deadline (dată calendaristică reală, validată)
  - status: TODO / IN_PROGRESS / BLOCKED / DONE
  - timp estimat (minute)

- Afișare toate task-urile
- Ștergere task după ID
- Editare task existent
- Sortare:
  - după prioritate (descrescător)
  - după deadline (crescător)
- Căutare task-uri după titlu sau descriere (case-insensitive)
- Afișare task-uri filtrate după status

---

## Persistență date

- Task-urile sunt salvate în fișierul `data/tasks.dat`
- Se încarcă automat la pornirea aplicației
- Se salvează automat la:
  - adăugare
  - editare
  - ștergere

---

## Structura proiectului

TASK MANAGER/
├── src/
│ ├── main.c # meniu principal + flow aplicație
│ ├── task.h # structuri Task, Date, TaskStatus
│ ├── task.c # creare + afișare task
│ ├── task_list.h # structura TaskList
│ ├── task_list.c # add / delete / edit / sort / search
│ ├── task_storage.h # salvare / încărcare fișier
│ ├── task_storage.c
│ ├── input_utils.h # validare input numeric și date
│ └── input_utils.c
├── data/
│ └── tasks.dat # fișier generat la rulare
├── Makefile
├── README.md
└── .gitignore
