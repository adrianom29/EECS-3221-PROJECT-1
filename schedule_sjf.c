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
void sortBurst(struct node *head);

//task is added to linked list
void add(char *name, int priority, int burst){
    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
}

// sorts list based on burst time before iterating through
void schedule() {
    sortBurst(head);

    int numProcesses = 0;
    int time = 0;
    int waiting = 0;
    int turnaround = 0;

    while(head != NULL){
        numProcesses++;
        struct node *temp = head;
        time += temp->task->burst;
        waiting += time - temp->task->burst;
        turnaround += time;

        run(temp->task, temp->task->burst);
        delete(&head, temp->task);
    }
    printf("\n");
    printf("Waiting Time: %.2lf\n", (double)waiting/numProcesses);
    printf("Turnaround Time: %.2lf\n", (double)turnaround/numProcesses);
    //waiting time == response time for non-preemptive algorithms
    printf("Response Time: %.2lf\n", (double)waiting/numProcesses);
}

// selection sort on linked list
// sorts based on burst time (increasing)
void sortBurst(struct node *head){
    if (head == NULL){
        return;
    }

    for (struct node *i = head; i->next != NULL; i = i->next){
        struct node *min = i;
        
        // finds node with smallest burst
        for (struct node *j = i->next; j != NULL; j = j->next){
            if (j->task->burst < min->task->burst){
                min = j;
            }
        }

        // swaps node with smallest burst to correct position
        if (min != i){
            Task *temp = i->task;
            i->task = min->task;
            min->task = temp;
        }
    }
}