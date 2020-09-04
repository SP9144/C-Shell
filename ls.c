#include "headers.h"
char path[2000];

void print_ls(int flag_a, int flag_l, int ndir){
    printf("a: %d, l: %d, ndir: %d\n", flag_a, flag_l, ndir);
    printf("path: %s\n", path);
}

void ls(char *command[], ll n) {

    int flag_a = 0, flag_l = 0;

    if(n==1)
    {
        strcpy(path, cwd);
        strcat(path, "/.");
        print_ls(flag_a, flag_l, 1);
    }
    else
    {
        ll i=1;
        int nflags=0; // *** number of flags ***
        while(i<n){
            if(command[i][0] == '-'){
                nflags++;
                if(strcmp(command[i], "a")){
                    flag_a = 1;
                }
                if(strcmp(command[i], "l")){
                    flag_l = 1;
                }
            }
            i++;
        }

        getcwd(cwd, sizeof(cwd));

        i=1;
        while(i<n)
        {
            if(!(command[i][0] == '-')){
                if(command[i][0]=='~')                  /* path: ~/<path> */
                {
                    //*** Initialise complete path ***
                    strcpy(path, home);
                    strcat(path, &command[i][1]);
                    // printf("Path: %s\n", path);
                }
                else
                {                                       /* path: <relative path> to cwd */  
                    strcpy(path, cwd);
                    strcat(path, "/");
                    strcat(path, command[i]);
                    // printf("Path: %s\n", path);
                }
                print_ls(flag_a, flag_l, n-1-nflags);
            }
            i++;
        }
    }
    
}
