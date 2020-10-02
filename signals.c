#include "headers.h"

void print_status(){
    
    int pid;
    int status;

    pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
    // if(pid == -1){
    //     printf("\033[0;31mError: Unable to waitpid\033[0m\n");
    //     return;
    // }

    for (int i = 1; i <= njobs; i++)
    {
        int x, y;

        x = WEXITSTATUS(status);
        y = WIFEXITED(status);

        // printf("%s, %d\n", names[i], pid);

        if(y && pid == pids[i] || (killjob_flag == 1 && pid == pids[i]) && overkill_flag == 0){
            if(x == 0){
                fprintf(stderr, "\nProcess %s with pid %d exited normally.\n", names[i], pid);
            }
            else{
                fprintf(stderr, "\nProcess %s with pid %d exited with status = %d.\n", names[i], pid, y);
            }
            prompt();
            fflush(stdout);
            return;

            // Delete from jobs array
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
        }
    }

    if (killjob_flag == 1)
        killjob_flag = 0;

    if(overkill_flag == 1){
        njobs = 0;
        overkill_flag = 0;
    }
}

void ctrlC(int sig_num){
    // printf("ctrl C\n");
    int pid = getpid();
    if (pid != shellID)
        return;

    if(curr_pid != -1){
        printf("sig curr %d %s\n", curr_pid, curr_name);
        int x; 
        x = kill(curr_pid, sig_num);
        printf("Killed 1\n");
        if(x == -1){
            printf("\033[0;31mError: Unable to kill\033[0m\n");
            return;
        }
        strcpy(curr_name, "");
    }
    else{
        // printf("Else\n");
        prompt();
        fflush(stdout);
        return;
    }
    // signal(SIGINT, ctrlC);
}

// void ctrlZ(int sig_num){

//     int pid = getpid();
//     if (pid != shellID)
//         return;
    
//     // printf("sig curr %d %s\n", curr_pid, curr_name);

//     if(curr_pid != -1){
//         int x; 
//         x = kill(curr_pid, SIGTTIN);
//         // printf("Killed 1\n");
//         if(x == -1){
//             printf("\033[0;31mError: Unable to kill\033[0m\n");
//             return;
//         }
//         x = kill(curr_pid, SIGTSTP);
//         // printf("Killed 2\n");
//         if(x == -1){
//             printf("\033[0;31mError: Unable to kill\033[0m\n");
//             return;
//         }

//         njobs += 1;
//         pids[njobs] = curr_pid;
//         strcpy(names[njobs], curr_name);

//         // printf("updated\n");

//         return;
//     }
//     signal(SIGTSTP, ctrlZ);
//     // printf("Cannot execute Ctrl+Z\n"); 

//     if(pid == shellID){
//         prompt();
//         fflush(stdout);
//     }

//     return;
// }

    //     int x; 
    //     x = kill(curr_pid, sig_num);
    //     printf("x: %d sig: %d Killed 1\n", x, sig_num);
    //     if(x == -1){
    //         printf("\033[0;31mError: Unable to kill\033[0m\n");
    //         return;
    //     }

    //     printf("\n");
    //     fflush(stdout);

    //     njobs += 1;
    //     pids[njobs] = curr_pid;
    //     strcpy(names[njobs], curr_name);
    //     printf("updated\n");
    // }
    // else{
    //     printf("\n");
    //     prompt();
    //     fflush(stdout);
    // }

