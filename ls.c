#include "headers.h"
char path[2000];
char dir[2000];

void print_ls(int flag_a, int flag_l, int ndir){    // *** ls OUTPUT ***

    // printf("a: %d, l: %d, ndir: %d\n", flag_a, flag_l, ndir);
    // printf("path: %s\n", path);

    struct dirent **namelist;
    int nfiles;

    nfiles = scandir(path, &namelist, NULL, alphasort);

    if(nfiles == -1)    // *** INVALID DIR or UNACCESSIBLE ***
    {
        printf("\033[0;31mError: Invalid or Unaccessible Directory\033[0m\n");
        perror("ls: ");
        return;
    }

    if(ndir > 1){
        printf("%s:\n", dir);
    }


    if(flag_a == 1 && flag_l == 0){
        int i = 0;
        while (i<nfiles)    // *** list of files in dir ***
        {
            printf("%s ", namelist[i++]->d_name);
        }
        printf("\n");
        if(ndir > 1){
            printf("\n");
        }
    }
    else if(flag_a == 0 && flag_l == 0){
        int i = 0;
        while (i<nfiles)    // *** list of files in dir ***
        {
            if(namelist[i]->d_name[0] != '.')
            {
                printf("%s ", namelist[i]->d_name);
            }
            i++;
        }
        printf("\n");
        if(ndir > 1){
            printf("\n");
        }
    }

}

void ls(char *command[], ll n) {    // *** ls INPUT ***

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
                // printf("Flag detected\n");
                nflags++;
                if(strcmp(command[i], "-la")==0 || strcmp(command[i], "-al")==0){   /* -al or la */   
                    flag_l = 1;
                    flag_a = 1;
                }                
                else if(command[i][1]=='l'){                                        /* -l */
                    flag_l = 1;
                }
                else if(command[i][1]=='a'){                                        /* -a */
                    flag_a = 1;
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

                    strcpy(dir, path);
                }
                else
                {                                       /* path: <relative path> to cwd */  
                    strcpy(path, cwd);
                    strcat(path, "/");
                    strcat(path, command[i]);
                    // printf("Path: %s\n", path);

                    strcpy(dir, command[i]);
                }
                print_ls(flag_a, flag_l, n-1-nflags);
            }
            i++;
        }

        if(n-1-nflags == 0){
            strcpy(path, cwd);
            strcat(path, "/.");
            print_ls(flag_a, flag_l, 1);
        }
    } 
}
