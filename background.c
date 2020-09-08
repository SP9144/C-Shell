#include "headers.h"

void background(char *commands[], ll n){
    
    int pid;
    pid = fork();

    char *subset[10000];

    for(ll i =0; i < n-1; i++){
        subset[i] = commands[i];
    }

    if(pid == -1){
        printf("\033[0;31mError: Unable to fork\033[0m\n");
        perror("fork: ");
        return;
    }
    else if(pid == 0){

        int sub_pid = fork();
        
        if(sub_pid == 0){
            int x;
            x = execvp(commands[0], subset);
            if(x == -1){
                printf("\033[0;31mError: Unable to execute\033[0m\n");
                perror("execvp: ");
                return; 
            }
        }
        else{
            int status;
            waitpid(sub_pid, &status, 0);

            int stat = WIFEXITED(status);
            if(stat){
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