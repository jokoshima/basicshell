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


int main(int argc, char **argv) {
    struct proclist *plist = proclist_new(); // you'll need this eventually

    // main loop for the shell
    while(true) {


    }

    proclist_free(plist); // clean up the process list
    return EXIT_SUCCESS;
}