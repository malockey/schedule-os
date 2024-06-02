# Task Scheduling

This project implements a task scheduling system using different scheduling algorithms. Currently, it supports Round-Robin and EDF (Earliest Deadline First) scheduling.

## Description of the project to be developed
To consolidate your understanding of schedulers, you are required to implement two task scheduling algorithms: Priority Round-Robin (RR_p) and Earliest Deadline First (EDF) .

- driver (.c) – This file implements the main() function, which reads task information from a test file (provided), adds the tasks to the list (ready queue), and calls the scheduler. This file is ready but can be completed.
- cpu (.c and .h) – These files implement the execution monitor, whose sole function is to print which task is currently being executed. These files are ready but can be completed.
- list (.c and .h) – These files are responsible for implementing the linked list structure and functions for inserting, deleting, and traversing the created list. These files are ready but can be completed.
- task (.h) – This file describes the structure of the task to be manipulated by the scheduler (where the information is stored when read from the file). This file is ready but can be completed.
- scheduler (.h) – This file is responsible for implementing the functions to add tasks to the list (add() function) and perform scheduling (schedule() function). This file needs to be implemented by you. You will create two versions of the scheduling algorithm, RR_p and EDF, in different projects.

You may modify the files that are already ready, such as the linked list manipulation file, to better suit the implementation, but you must not lose the essence of the provided implementation. Here is some information about the implementation:

- For the Priority Round-Robin (RR_p), the priority will only be taken into account when choosing which task should be executed if there are two (or more) tasks to be executed at the moment. In the case of equal priorities, you can implement your criterion, such as the first in the list (for example). For this work, consider the highest priority as 1. Additionally, the use of multiple queues for priority management is mandatory.
- You should consider more ready queues for different priorities. Add two tasks for each created priority.
- The time slice counting can be implemented as desired, such as with libraries or by a shared global variable.
- Remember that the task list (ready queue) must be kept "alive" throughout the execution. Therefore, it is recommended to implement it in a library (which can be within the scheduler.h itself) and share it as a global variable.
- Again, you can modify the files, especially the "list" file, but without compromising their original essence. However, this file helps in creating priority, as it works in the stack model.
- To use the Makefile, generate a file schedule_rr.c, schedule_rrp.c, and schedule_fcfs.c that includes the scheduler.h library (you can also rename the library). If you do not want to use the Makefile, you can work with the preferred IDE or compile via the terminal.
- Use a slice of up to 10 time units.
- For the algorithms, you must, via a first extra thread, simulate the occurrence of the hardware timer. This thread will simulate time and generate the time-out flag (for the slice). Additionally, for the EDF algorithm, it will be necessary to evaluate the task deadlines and check which task has the smallest deadline.

## How to Execute

- Round Robin:
```
make rr_p
```

- EDF
```
make rr_p
```