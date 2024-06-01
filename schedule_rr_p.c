#include "schedule_rr_p.h"
#include "list.c"
#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PRIORITIES 5

int executionTime = 0;

struct node *head = NULL;
typedef struct Queue {
    struct node *head;
} Queue;

Queue priorityQueues[NUM_PRIORITIES];
LARGE_INTEGER frequency;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    insert(&head, task);
}

void addToPriorityQueue(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    insert(&(priorityQueues[priority].head), task);
}

double elapsedTime(LARGE_INTEGER startTime) {
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double totalTime = (double)(endTime.QuadPart - startTime.QuadPart) / (double)frequency.QuadPart;
    return totalTime;
}

void runTask(Task *task, int quantum) {
    printf("Executing task %s\n", task->name);
    printf("Burst time remaining before execution: %d\n", task->burst);
    printf("-----------------------------------------\n");

    if (task->burst > quantum) {
        run(task, quantum);
        task->burst -= quantum;
        executionTime += quantum;
    } else {
        run(task, task->burst);
        executionTime += task->burst;
        task->burst = 0;
    }

    printf("Burst time remaining after execution: %d\n", task->burst);
    printf("Total execution time so far: %d\n", executionTime);
    printf("-----------------------------------------\n");
}

void moveToEnd(Queue *queue, struct node *node) {
    if (queue->head == NULL) {
        return;
    }

    struct node *temp = queue->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
    node->next = NULL;
}

void executePriorityQueue(Queue *queue) {
    while (queue->head != NULL) {
        struct node *current = queue->head;
        int allTasksCompleted = 1; // flag to check if all tasks are completed

        while (current != NULL) {
            runTask(current->task, QUANTUM);

            if (current->task->burst == 0) {
                struct node *completedTask = current;
                current = current->next;
                delete(&(queue->head), completedTask->task);
                printf("It took %i units of time to complete the task %s. \n", executionTime, completedTask->task->name);
            } else {
                current = current->next;
                allTasksCompleted = 0;
            }
        }

        if (allTasksCompleted) {
            break;
        }

        if (queue->head != NULL) {
            struct node *tail = queue->head;
            queue->head = queue->head->next;
            moveToEnd(queue, tail);
        }
    }
}

void initializePriorityQueues() {
    for (int i = 0; i < NUM_PRIORITIES; i++) {
        priorityQueues[i].head = NULL;
    }
}

void distributeTasksToPriorityQueues() {
    struct node *temp = head;
    while (temp != NULL) {
        addToPriorityQueue(temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}

void schedule() {
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    initializePriorityQueues();
    distributeTasksToPriorityQueues();

    for (int i = 0; i < NUM_PRIORITIES; ++i) {
        if (priorityQueues[i].head != NULL) {
            printf("Executing priority queue %d\n", i);
            executePriorityQueue(&priorityQueues[i]);
        }
    }

    printf("----------------------------------------\n");
    printf("It took %.9f seconds to complete all tasks.\n", elapsedTime(startTime));
    printf("----------------------------------------\n");
}
