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
    while (head != NULL){
        struct node *temp = head;    
        run(temp->task, temp->task->burst);
        delete(&head, temp->task);
    }
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