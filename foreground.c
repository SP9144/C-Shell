#include "headers.h"

void foreground(char *commands[], ll n){
    int pid;
    pid = fork();


    if(pid == -1){
        printf("\033[0;31mError: Unable to fork\033[0m\n");
        perror("fork");
        return;
    }
    else if(pid == 0){
        int x = execvp(commands[0], commands);
        if(x == -1){
            printf("\033[0;31mError: Unable to execute\033[0m\n");
            perror("execvp");
            return; 
        }
    }
    else{
        curr_pid = pid;
        strcpy(curr_name, commands[0]);
        // printf("fore curr %d %s\n", curr_pid, curr_name);

        int status;
        waitpid(pid, &status, 0);               /* 0 => same gid as parent */
    }
}