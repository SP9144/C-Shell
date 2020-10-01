#include "headers.h"

void print_status(){
    
    int pid;
    int status;

    pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
    if(pid == -1){
        printf("\033[0;31mError: Unable to waitpid\033[0m\n");
        return;
    }

    printf("HEre1\n");

    for (int i = 1; i <= njobs; i++)
    {
        int x, y;

        x = WEXITSTATUS(status);
        y = WIFEXITED(status);

        printf("HEre2\n");
        printf("%s, %d\n", names[i], pid);

        if(x && pid == pids[i]){
            printf("HEre3\n");
            if(y == 0){
                fprintf(stderr, "Process %s with pid %d exited normally\n", names[i], pid);
            }
            else{
                fprintf(stderr, "Process %s with pid %d exited with status = %d\n", names[i], pid, y);
            }
            fflush(stdout);
            prompt();
        }
    }
}