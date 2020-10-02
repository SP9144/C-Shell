#include "headers.h"

void bg(char *commands[], ll n){
    // printf("bg\n");
    if(n>2){                                
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n<2){                                
        printf("\033[0;31mError: Too less arguments\033[0m\n");
        return;
    }
    else{

        int job_num;
        job_num = atoi(commands[1]);
        // printf("%d %d \n", job_num, njobs);

        if(job_num > njobs || job_num <= 0){
            printf("\033[0;31mError: No process found\033[0m\n");
            return;
        }
        else{
            kill(pids[job_num], SIGTTIN);  
            kill(pids[job_num], SIGCONT);
        }
    }
}

void fg(char *commands[], ll n){
    // printf("fg\n");
    if(n>2){                                
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n<2){                                
        printf("\033[0;31mError: Too less arguments\033[0m\n");
        return;
    }
    else{
        int job_num;
        int status; 

        job_num = atoi(commands[1]);
        // printf("%d %d \n", job_num, njobs);

        if(job_num > njobs || job_num <= 0){
            printf("\033[0;31mError: No process found\033[0m\n");
            return;
        }
        else{
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, pids[job_num]);

            curr_pid = pids[job_num];
            strcpy(curr_name, names[job_num]);
            // printf("fg: %d, %s\n", curr_pid, curr_name);

            kill(pids[job_num], SIGCONT);

            // Delete from jobs array
            int pid = pids[job_num];
            for (int i = 1; i <= njobs; i++)
            {
                if (pids[i] == pid)
                {
                    for (int j = i; j < njobs; j++){
                        pids[j] = pids[j + 1];
                        strcpy(names[j], names[j+1]);
                    }
                }
                njobs -= 1;
            }

            waitpid(-1, NULL, WUNTRACED); 

            tcsetpgrp(STDIN_FILENO,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);
        }
    }
}

