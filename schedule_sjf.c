// Adriano Mancuso 221259940
// Shortest job first algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "cpu.h"
#include "list.h"
#include "schedulers.h"

// linked list implementation
struct node *head = NULL;
int numProcesses = 0;
void sortBurst(struct node *head);

//task is added to linked list
void add(char *name, int priority, int burst){
    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
    numProcesses++;
}

// sorts list based on burst time before iterating through
void schedule() {
    head = reverse(head);
    sortBurst(head);

    int time = 0;
    int waiting = 0;
    int turnaround = 0;

    while(head != NULL){
        struct node *temp = head;
        time += temp->task->burst;
        waiting += time - temp->task->burst;
        turnaround += time;

        run(temp->task, temp->task->burst);
        delete(&head, temp->task);
    }
    printf("\n");
    printf("Average waiting time = %.2lf\n", (double)waiting/numProcesses);
    printf("Average turnaround time = %.2lf\n", (double)turnaround/numProcesses);
    //waiting time == response time for non-preemptive algorithms
    printf("Average response time = %.2lf\n", (double)waiting/numProcesses);
}

// bubble sort on linked list
// sorts based on burst time (increasing)
void sortBurst(struct node *head){
    if (head == NULL){
        return;
    }
    int swapped;
    struct node *current;

    do{
        swapped = 0;
        current = head;
        while (current->next != NULL){
            Task *temp = current->task;
            if (current->task->burst > current->next->task->burst){
                current->task = current->next->task;
                current->next->task = temp;
                swapped = 1;
            }
            current = current->next;
        }
    }
    while(swapped);
}