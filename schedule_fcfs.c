// Adriano Mancuso 221259940
// First come first serve algorithm


#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

// Linked list implementation

struct node *head = NULL;

//task is added to linked list
void add(char *name, int priority, int burst) {

    Task *t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
}

// goes to tail of linked list and removes 
void schedule() {    
    while(head != NULL){
        struct node *temp = head;    
        
        while(temp->next != NULL){
            temp = temp->next;
        }
        run(temp->task, temp->task->burst);        
        delete(&head, temp->task);
    }
}

