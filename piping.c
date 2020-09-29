#include "headers.h"

void piping(char *command){
    char *sub_command[1000];
    ll n_command = 0;

    n_command = split_by(sub_command, command, "|");
    // for(ll k = 0; k < n_command; k++){
    //     printf("sub-command %lld: \"%s\"\n", k, sub_command[k]);
    // }

    int fds[2], pid;
    int input = 0;

    for(ll k = 0; k < n_command; k++){
        pipe(fds);
        pid = fork();

        if(pid == -1){
            printf("\033[0;31mError: Unable to fork\033[0m\n");
            perror("fork");
            return;
        }
        else if(pid == 0){
            dup2(input, 0);

            if(k+1 != n_command){
                dup2(fds[1], 1);
            }

            close(fds[0]);
            
            //*** Check Redirection ***
            int redirect;
            if(strstr(sub_command[k], ">") != NULL || strstr(sub_command[k], "<") != NULL ){
                redirect = 1;
            }

            if(redirect == 1){
                redirection(sub_command[k]);
            }
            else{
                execute_command(sub_command[k]);
            }

            exit(1);
        }
        else{
            wait(NULL);
            close(fds[1]);
            input = fds[0];
        }
    }
    
}
