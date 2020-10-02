#include "headers.h"

void background(char *commands[], ll n){
    
    int pid;
    pid = fork();

    char *subset[10000];

    for(ll i =0; i < n; i++){ /* If command is `emacs & hi` */
        while(strcmp(commands[i], "&")){
            subset[i] = commands[i];
            i++;
        }
        break;
    }

    if(pid == -1){
        printf("\033[0;31mError: Unable to fork\033[0m\n");
        perror("fork");
        return;
    }
    else if(pid == 0){

        int x;
        x = execvp(subset[0], subset);
        if(x == -1){
            printf("\033[0;31mError: Unable to execute\033[0m\n");
            perror("execvp");
            return; 
        }
    }
    else{
        njobs++;
        pids[njobs]=pid;
        strcpy(names[njobs], commands[0]);
        // printf("bg: %d,  %s, %d\n", njobs, names[njobs], pids[njobs]);
    }
}