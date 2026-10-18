// Adriano Mancuso 221259940
// First come first serve algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

// Linked list implementation

struct node *head = NULL;
int numProcesses = 0;

//task is added to linked list
void add(char *name, int priority, int burst) {

    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
    numProcesses++;
}

// reverses linked list before iterating through
void schedule() {
    int time = 0;
    int waiting = 0;
    int turnaround = 0;

    head = reverse(head);
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

