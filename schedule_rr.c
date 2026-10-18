// Adriano Mancuso 221259940
// Round Robin algorithm

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
// const QUANTUM already defined in cpu.h

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
    //int waiting = 0;
    int turnaround = 0;
    //int response = 0;


    head = reverse(head);
    while(head != NULL){
        struct node *temp = head;
        while (temp != NULL){
            if (temp->task->burst <= QUANTUM){
                run(temp->task, temp->task->burst);
                time += temp->task->burst;
                turnaround += time;
                delete(&head, temp->task);
            }
            else{
                run(temp->task, QUANTUM);
                time += QUANTUM;
                temp->task->burst -= QUANTUM;   
            }

            temp = temp->next;
        }

    }
    printf("\n");
    //printf("Average waiting time = %.2lf\n", (double)waiting/numProcesses);
    printf("Average turnaround time = %.2lf\n", (double)turnaround/numProcesses);
    //printf("Average response time = %.2lf\n", (double)response/numProcesses);

}