#include "headers.h"

void cd(char *command[],ll n){
    char path[2000];

    if(n>2){                                /* cd arg1 arg2: INVALID */
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n==1){                          /* cd: goes to ~ */
        strcpy(path, home);
    }
    else if(command[1][0]=='~'){            /* cd ~/<path> */

        //*** Initialise complete path ***
        strcpy(path, home);
        strcat(path, &command[1][1]);
        // printf("Path: %s\n", path);
    }
    else{                                   /* cd <relative path> */
        strcpy(path, command[1]);
        // printf("Path: %s\n", path);
    }

    int val = chdir(path);
    if(val == -1){                          /* INVALID PATH */
        printf("\033[0;31mError: Invalid path\033[0m\n");
        perror("cd");
    }
}