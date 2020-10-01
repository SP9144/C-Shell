#include "headers.h"

void cd(char *command[], ll n){
    char path[2000];

    if(n>2){                                /* cd arg1 arg2: INVALID */
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n==1){                          /* cd: goes to ~ */

        getcwd(lwd, sizeof(lwd));

        strcpy(path, "");
        strcat(path, home);
    }
    else if(command[1][0]=='~'){            /* cd ~/<path> */

        getcwd(lwd, sizeof(lwd));
        
        //*** Initialise complete path ***
        strcpy(path, "");
        strcat(path, home);
        strcat(path, &command[1][1]);
        // printf("Path: %s\n", path);
    }
    else if(command[1][0]=='-'){            /* cd - */

        strcpy(path, lwd);

        char* p;
        char rel_path[2000]="";

        if(strstr(path, home)){                 /* path: relative to home*/
            p = strstr(path, home);
            strcpy(rel_path, "~");
            strcat(rel_path, p+strlen(home));
        }
        else{                                   /* path: outside of shell home */
            strcpy(rel_path, path);     
        }  
        printf("%s\n", rel_path);
        
        getcwd(lwd, sizeof(lwd));

    }
    else{                                   /* cd <relative path> */
        
        getcwd(lwd, sizeof(lwd));

        strcpy(path, "");
        strcat(path, command[1]);
        // printf("Path: %s\n", path);
    }

    int val = chdir(path);
    // printf("val: %d\n", val);
    if(val == -1){                          /* INVALID PATH */
        printf("\033[0;31mError: Invalid path\033[0m\n");
        perror("cd");
    }
}