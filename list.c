#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "list.h"

/*
 * Return a pointer to a newly-heap-allocated struct proclist.
 * Don't forget to initialize the contents of the struct!
 */
struct proclist* proclist_new() {
    struct proclist* list = malloc(sizeof(struct proclist));
    list -> head = NULL;
    list -> length = 0;
    return list;
}

/*
 * Completely free the memory consumed by a struct proclist,
 * including each node (and each cmd in each node, which should
 * also be heap-allocated), and the struct proclist itself.
 */
void proclist_free(struct proclist *head) {
    for (struct procnode* curr = head -> head; curr != NULL; 
    curr = curr -> next){
        free(curr -> cmd);
        free(curr);
    }
    free(head);
}

/*
 * Create a new heap-allocated struct procnode, initialize it
 * with the pid and cmd passed as parameters, and add it to the
 * struct proclist.  
 * 
 * The cmd string *must* be copied to a newly heap-allocated
 * location.  (Hint: use strdup.)
 */
void proclist_add(struct proclist* head, pid_t pid, char *cmd) {
    struct procnode* newnode = malloc(sizeof(struct procnode));
    newnode -> pid = pid;
    newnode -> cmd = strdup(cmd);
    newnode -> next = head -> head;
    head -> head = newnode;
    head -> length += 1;
}

/*
 * Search the struct proclist for a struct procnode with a particular
 * process id (pid).  Return NULL if the pid isn't anywhere on the proclist,
 * or a pointer to the struct procnode for that pid.
 */
struct procnode* proclist_find(struct proclist* head, pid_t pid) {
    for (struct procnode* curr = head -> head; curr != NULL; 
    curr = curr -> next){
        if (curr -> pid == pid){
            return curr;
        }
    }
    return NULL;
}

/*
 * Remove the procnode within the proclist that has a particular
 * pid.  If a procnode with the pid doesn't exist on the proclist, do
 * nothing.
 * When removing, don't forget to deallocate any heap memory used
 * by the struct procnode being removed (including the cmd, which should
 * have been heap-allocated).
 */
void proclist_remove(struct proclist *head, pid_t pid) {
    if (head -> head -> pid == pid){
        struct procnode* target = head -> head;
        head -> head = target -> next;
        free(target -> cmd);
        free(target);
        head -> length -= 1;
        return;
    }
    for (struct procnode* curr = head -> head; curr -> next != NULL; 
    curr = curr -> next){
        if (curr -> next -> pid == pid){
            struct procnode* target = curr -> next;
            curr -> next = target -> next;
            free(target -> cmd);
            free(target);
            head -> length -= 1;
            return;
        }
    }
}

// Checks if the proclist is empty.

bool proclist_empty(struct proclist *head){
    if (head -> head == NULL){
        return true;
    }
    return false;
}

/*
 * Print some representation of the (active) processes on the proclist.
 * For example, if no processes are running, you can print something like:
 *

 Processes currently active: none

 *
 * If there are any processes active, you output might look like:

 Processes currently active:
        [30]: /bin/sleep
        [29]: /bin/sleep
        [28]: /bin/sleep

 */
void proclist_print(struct proclist *head) {
    printf("Processes currently active: ");
    if (proclist_empty(head)){
        printf("none\n");
        return;
    }
    for (struct procnode* curr = head -> head; curr != NULL; 
    curr = curr -> next){
        printf("\n\t\t[%d]: %s\n", curr -> pid, curr -> cmd);
    }
}
