#include "headers.h"

void print_jobs(){
    // printf("njobs - func %d\n", njobs);
    for(int i = 1; i <= njobs; i++){

        int pid_job;
        char name[1000];
        char stat[2000] = "";

        pid_job = pids[i];
        strcpy(name, names[i]);

        //*** Stat File ***
        sprintf(stat, "/proc/%d/stat", pid_job);
        // printf("stat file: %s\n", stat);

        char buffer[2000] = "";
        int fd;

        fd = open(stat, O_RDONLY);

        if(fd == -1){
            printf("\033[0;31mError: Invalid PID\033[0m\n");
            return;
        }

        read(fd, buffer, sizeof(buffer));
        // printf("Stat buff:\n %s\n", buffer);

        ll n_stat = 0;
        char *list[100]; 
        list[0] = strtok(buffer, " ");
        while (list[n_stat] != NULL)
        {
            // printf("part %lld: %s\n", n_stat, list[n_stat]);
            n_stat++;
            list[n_stat] = strtok(NULL, " ");
        }
        // printf("status: %s\n", list[2]);

        if(strcmp(list[2], "T")==0)
        {
            printf("[%d] Stopped %s [%d]\n", i, name, pid_job);
        }
        else
        {
            printf("[%d] Running %s [%d]\n", i, name, pid_job);
        }
    }
}

void kjob(char *commands[], ll n){
    // printf("kjobs\n");
    int job_num, sig_num;

    if(n>3){                                
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n<3){                                
        printf("\033[0;31mError: Too less arguments\033[0m\n");
        return;
    }
    else{

        job_num = atoi(commands[1]);
        sig_num = atoi(commands[2]);

        if(job_num > njobs || job_num <= 0){
            printf("\033[0;31mError: No process found\033[0m\n");
            return;
        }
        
        if(sig_num == 9){
            killjob_flag = 1;
        }
        kill(pids[job_num], sig_num);
        
    }
}

void overkill(){
    for(int i=1; i<=njobs; i++)
    {
        kill(pids[i],9);
    }

    overkill_flag=1;
}