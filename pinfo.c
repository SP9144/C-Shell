#include "headers.h"

void pinfo(char *command[], ll n){
    int pid;

    char stat[2000] = "";
    char exe[2000] = "";
    char rel_exe_path[2000]="";

    if(n>2){                                /* pinfo arg1 arg2: INVALID */
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n==1){                          /* pinfo: pinfo of shell */
        pid = getpid();
    }
    else{
        pid = atoi(command[1]);
    }
    // printf("pid: %d\n", pid);

    // *** Stat File ***
    sprintf(stat, "/proc/%d/stat", pid);
    // printf("stat file: %s\n", stat);

    char buffer[2000] = "";
    int fd;

    fd = open(stat, O_RDONLY);

    if(fd == -1){
        printf("\033[0;31mError: Invalid PID\033[0m\n");
        perror("pinfo: ");
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
    // printf("VM amount: %s\n", list[23]);

    // *** Exe File ***
    sprintf(exe, "/proc/%d/exe", pid);
    // printf("exe file: %s\n", exe); 

    int e;
    char exe_path[2000] = "";
    e = readlink(exe, exe_path, sizeof(exe_path));
    if (e == -1)
    {
        printf("\033[0;31mError: Couldn't open file\033[0m\n");
        perror("pinfo: ");
        return;
    }
    else
    {
        char* p; 
        if(strstr(exe_path, home)){
            p = strstr(exe_path, home);
            strcpy(rel_exe_path, "~");
            strcat(rel_exe_path, p+strlen(home));
        }
        else{
            strcpy(rel_exe_path, exe_path);
        }  
        // printf("exe file patj: %s\n", rel_exe_path);
    }
    
    // *** Output ***
    printf("pid -- %d\n", pid);
    printf("Process Status -- %s\n", list[2]);
    printf("memory -- %s\n", list[23]);
    printf("Executable Path -- %s\n", rel_exe_path);

}