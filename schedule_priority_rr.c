// Adriano Mancuso 221259940
// Priority Round Robin Scheduling algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "cpu.h"
#include "list.h"
#include "schedulers.h"

// Linked list implementation

struct node *head = NULL;
int numProcesses = 0;
void sortPriority(struct node *head);
// const QUANTUM already defined in cpu.h

//task is added to linked list
void add(char *name, int priority, int burst){
    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
    numProcesses++;
}

// reverses linked list before iterating through
// sorts list based on priority time before iterating through
void schedule() {
    int time = 0;
    int waiting = 0;
    int turnaround = 0;
    int response = 0;

    //checks if task has been visited (for response time)
    //allocates proper amount of memory
    int *visited = calloc(numProcesses, sizeof(int));  
    
    head = reverse(head);
    sortPriority(head);
    
    while(head != NULL){
        struct node *temp = head;
        

        //if no tie breaker
        if (temp->next == NULL || temp->task->priority != temp->next->task->priority){
            //is this node unvisited?
            int i = atoi(head->task->name + 1);
            if (visited[i] == 0){
                waiting -= temp->task->burst;      //waiting time = -burst + turnaround 
                response += time;
                visited[i] = 1;
            }

            run(temp->task, temp->task->burst);
            time += temp->task->burst;
            turnaround += time;
            delete(&head, temp->task);
            continue;   //go to next iteration before rr runs
        }
        //if no tie breaker, same priority, use rr.
        int priority = temp->task->priority;
        struct node *current = head;

        while (current != NULL && current->task->priority == priority){
            struct node *next = current->next;
            Task *t = current->task;
            //is current node the last remaining node of that priority?
            int isLastRemaining = current == head && 
                                   (next == NULL || next->task->priority != priority);

            int i = atoi(current->task->name + 1);
            if (visited[i] != 1){
                response += time;
                waiting -= current->task->burst;   //waiting time = -burst + turnaround
            }
            visited[i] = 1;

            //if burst <= quantum or node is last of that priority delete from list
            if (t->burst <= QUANTUM || isLastRemaining){
                run(t, t->burst);
                time += t->burst;
                turnaround += time;
                delete(&head, t);
            }
            else{
                run(t, QUANTUM);
                time += QUANTUM;
                t->burst -= QUANTUM;
            }
            current = next;
        }
    }
    waiting += turnaround;   //waiting time = -burst + turnaround 

    printf("\n");    
    printf("Average waiting time = %.2lf\n", (double)waiting/numProcesses);
    printf("Average turnaround time = %.2lf\n", (double)turnaround/numProcesses);
    printf("Average response time = %.2lf\n", (double)response/numProcesses);
}

// bubble sort on linked list
// sorts based on burst time (increasing)
// bubble sort is used because duplicates will remain in same order as they originally appear
void sortPriority(struct node *head){
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
            if (current->task->priority < current->next->task->priority){
                current->task = current->next->task;
                current->next->task = temp;
                swapped = 1;
            }
            current = current->next;
        }
    }
    while(swapped);
}