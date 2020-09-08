#include "headers.h"

void background(char *commands[], ll n){
    
    int pid;
    pid = fork();

    if(pid == -1){
        printf("\033[0;31mError: Unable to fork\033[0m\n");
        perror("fork: ");
        return;
    }
    else if(pid == 0){

        int sub_pid = fork();
        
        if(sub_pid == 0){
            int x;
            x = execvp(commands[0], commands);
            if(x == -1){
                printf("\033[0;31mError: Unable to execute\033[0m\n");
                perror("execvp: ");
                return; 
            }
        }
        else{
            int status;
            waitpid(sub_pid, &status, 0);

            if(WIFEXITED(status)){
                int x;
                x = WEXITSTATUS(status);
                if(x == 0){
                    printf("%s with pid %lld exited normally\n", commands[0], n);
                }
                else{
                    printf("\033[0;31mError: Command not found\033[0m\n");
                    perror("WEXITSTATUS: ");
                    return;
                }
            }
            else{
                printf("%s with pid %lld exited abnormally\n", commands[0], n);
            }
        }

    }
}