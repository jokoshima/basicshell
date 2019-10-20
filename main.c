#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "list.h"

#include <ctype.h>
#include <errno.h>


/*
 * The tokenify() function from lab 2, with one modification,
 * for you to use.
 *
 * The modification is that it also takes a second parameter,
 * which is the set of characters on which to "split" the input.
 * In lab 2, this was always " \t\n", but you can call tokenify
 * to split on other characters, too, with the implementation below.
 * Hint: you can split on ";" in order to separate the commands on 
 * a single command line.
 */
char** tokenify(const char *s, const char *sep) {
    char *word = NULL;

    // make a copy of the input string, because strtok
    // likes to mangle strings.  
    char *s1 = strdup(s);

    // find out exactly how many tokens we have
    int words = 0;
    for (word = strtok(s1, sep);
         word;
         word = strtok(NULL, sep)) words++ ;
    free(s1);

    s1 = strdup(s);

    // allocate the array of char *'s, with one additional
    char **array = (char **)malloc(sizeof(char *)*(words+1));
    int i = 0;
    for (word = strtok(s1, sep);
         word;
         word = strtok(NULL, sep)) {
        array[i] = strdup(word);
        i++;
    }
    array[i] = NULL;
    free(s1);
    return array;
}

void free_tokens(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array
}

void strip(char *str, char *buffer){
    int newsize = 0;
    for (int i=0; str[i] != '\0'; i++){
        if (!isspace(str[i])){
            buffer[newsize] = str[i];
            newsize++;
        }
    }
    buffer[newsize] = '\0';
}

int comment_position(char *str){
    for (int i=0; i<strlen(str); i++){
        if (str[i] == '#'){
            return i;
        }
    }
    // always occupied by \0
    return strlen(str);
}

int main(int argc, char **argv) {
    struct proclist *plist = proclist_new(); // you'll need this eventually
    char cmd_stripped[1024];
    // main loop for the shell
    while(true) {
        printf("do-> ");
        char in[1024];

        // tests for exit sequence (Ctrl-D)
        if (fgets(in, 1024, stdin) == NULL){
            proclist_free(plist);
            exit(0);
        }
        char **procs = tokenify(in, ";");
        for (int i=0; procs[i] != NULL; i++){

            // Comment handling
            procs[i][comment_position(procs[i])] = '\0';

            char **cmd = tokenify(procs[i], " \n\t");
            strip(cmd[0], cmd_stripped);
            
            // Multispace/no character check
            if (strlen(cmd_stripped) == 0){
                continue;
            }
            
            // Exit call
            if (strcmp(cmd_stripped, "exit") == 0){
                free_tokens(cmd);
                free_tokens(procs);
                proclist_free(plist);
                exit(0);
            }

            // Status call
            if (strcmp(cmd_stripped, "status") == 0){

            }

            // Main process call procedure
            //char **cmd = tokenify(procs[i], " \n\t");
            pid_t pid = fork();
            int childrv;
            int *p_a = &childrv;
            if (pid == 0){
                if (execv(cmd[0], cmd) < 0) {
                    fprintf(stderr, "execv failed: %s\n", strerror(errno));
                }
            }
            else{
                wait(p_a);
                printf("Child finished\n");
            }

            // Free the current command tokens
            free_tokens(cmd);
        }
        // Free the current line tokens
        free_tokens(procs);
    }
    proclist_free(plist); // clean up the process list
    return EXIT_SUCCESS;
}
