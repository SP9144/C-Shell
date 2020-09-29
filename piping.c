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

            //*** Dividing current command ***
            char *curr_command[1000];
            char cmd[2000];
            ll n_curr_command = 0;

            strcpy(cmd, sub_command[k]);
            n_curr_command = split_by(curr_command, cmd, " \t\n\r");
            // printf("number of subcommands: %lld\n", n_curr_command);
            // for(ll j = 0; j < n_curr_command; j++){
            //     printf("subcommand %lld: %s\n", j, curr_command[j]);
            // }
            
            //*** Check Redirection ***
            int redirect;
            if(strstr(sub_command[k], ">") != NULL || strstr(sub_command[k], "<") != NULL ){
                redirect = 1;
            }

            if(redirect == 1){
                redirection(sub_command[k]);
            }
            else if(strcmp(curr_command[0], "exit") == 0){                  /* exit */
                printf("Exiting\n");
                exit(0);
            }
            else if(strcmp(curr_command[0], "cd") == 0){                    /* cd */
                if(!strcmp(curr_command[n_curr_command-1], "&"))
                    cd(curr_command, n_curr_command-1);
                else
                    cd(curr_command, n_curr_command);
            }
            else if(strcmp(curr_command[0], "pwd") == 0){                   /* pwd */
                if(!strcmp(curr_command[n_curr_command-1], "&"))
                    pwd(n_curr_command-1);
                else
                    pwd(n_curr_command);
            }
            else if(strcmp(curr_command[0], "echo") == 0){                  /* echo */
                if(!strcmp(curr_command[n_curr_command-1], "&"))
                    echo(sub_command[k], n_curr_command-1);
                else
                    echo(sub_command[k], n_curr_command);
            }
            else if(strcmp(curr_command[0], "ls") == 0){                    /* ls */
                if(!strcmp(curr_command[n_curr_command-1], "&"))
                    ls(curr_command, n_curr_command-1);
                else
                    ls(curr_command, n_curr_command);
            }
            else if(strcmp(curr_command[0], "pinfo") == 0){                 /* pinfo */
                if(!strcmp(curr_command[n_curr_command-1], "&"))
                    pinfo(curr_command, n_curr_command-1);
                else
                    pinfo(curr_command, n_curr_command); 
            }
            else if(strcmp(curr_command[0], "history") == 0){               /* pinfo */
                if(!strcmp(curr_command[n_curr_command-1], "&"))
                    history(curr_command, n_curr_command-1);
                else
                    history(curr_command, n_curr_command);
            }
            else if(strstr(sub_command[k], "&")){                              /* background processes - & */
                background(curr_command, n_curr_command);
            }
            else{                                                           /* foreground processes*/
                foreground(curr_command, n_curr_command);
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
