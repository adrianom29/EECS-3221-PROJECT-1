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

//task is added to linked list
void add(char *name, int priority, int burst) {

    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
}

// reverses linked list before iterating through
void schedule() {
    head = reverse(head);
    while(head != NULL){
        struct node *temp = head;    
        run(temp->task, temp->task->burst);
        delete(&head, temp->task);
    }
}

