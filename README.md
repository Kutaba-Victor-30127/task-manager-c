# Task Manager in C (CLI)

A console-based task management application written in C.

This project was built for educational purposes, focusing on clean code organization, input validation, file persistence, and modular software design.

## Features

### Task Creation

Create tasks with:

* Unique ID (positive integer, validated)
* Title
* Description
* Priority (1–5)
* Deadline (validated calendar date)
* Status:

  * TODO
  * IN_PROGRESS
  * BLOCKED
  * DONE
* Estimated time (minutes)

### Task Management

* View all tasks
* Delete tasks by ID
* Edit existing tasks
* Search tasks by title or description (case-insensitive)
* Filter tasks by status

### Sorting

* Sort by priority (descending)
* Sort by deadline (ascending)

## Data Persistence

Tasks are stored in:

```text
data/tasks.dat
```

The application:

* Loads tasks automatically on startup
* Saves tasks automatically after:

  * creating a task
  * editing a task
  * deleting a task

## Project Structure

```text
TASK-MANAGER/
│
├── src/
│   ├── main.c              # Main menu and application flow
│   ├── task.h              # Task, Date and TaskStatus structures
│   ├── task.c              # Task creation and display
│   ├── task_list.h         # TaskList structure
│   ├── task_list.c         # Add, delete, edit, sort and search operations
│   ├── task_storage.h      # File save/load functionality
│   ├── task_storage.c
│   ├── input_utils.h       # Input and date validation
│   └── input_utils.c
│
├── data/
│   └── tasks.dat           # Generated data file
│
├── Makefile
├── README.md
└── .gitignore
```

## Technologies

* C
* File I/O
* Dynamic memory management
* Modular programming
* Makefile
* Git

## Learning Objectives

This project was created to practice:

* Structured programming in C
* Modular software architecture
* Data validation
* File persistence
* Separation of responsibilities
* Building medium-sized console applications
