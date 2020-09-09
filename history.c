#include "headers.h"

int hist_limit = 20;

void read_history(){

    char path[2000]="";
    strcpy(path, home);
    strcat(path, "/history.txt");

    char *command = NULL;
    size_t len;

    FILE *file_ptr = NULL;
    file_ptr = fopen(path, "r");

    if(fopen(path, "r") == NULL){
        printf("\033[0;31mError: history.txt not found\033[0m\n");
        perror("fopen");
    }

    // for(int i=0; i<hist_limit; i++){
    //     getline(&command, &len, file_ptr);
    //     strcpy(hist[i], command);
    //     printf("%d %s\n", i, hist[i]);
    // }

    int i=0;
    while(getline(&command, &len, file_ptr) != -1){
        strcpy(hist[i++], command);
    }

    // for(int i=0; i<hist_limit; i++){
    //     printf("%d: ", i);
    //     printf("%s\n", hist[i]);
    // }
    
    fclose(file_ptr);
}

void write_history(){

    char path[2000]="";
    strcpy(path, home);
    strcat(path, "/history.txt");

    FILE *file_ptr = NULL;
    file_ptr = fopen(path, "w");

    if(file_ptr == NULL){
        printf("\033[0;31mError: history.txt not found\033[0m\n");
        perror("fopen");
    }

    for(int i=0; i<hist_limit; i++){

        fprintf(file_ptr, "%s", hist[i]);
    }
    fclose(file_ptr);
}

void update_history(char *command){
    for(int i=1; i<hist_limit; i++){
        strcpy(hist[i-1], hist[i]);
    }
    strcpy(hist[hist_limit-1],command);

    // for(int i=0; i<hist_limit; i++){
    //     printf("%s\n", hist[i]);
    // }
    
    write_history();

}

void history(char *command[], ll n){
    int n_cmds;                                                     /* history n "text" */
    if(n>2){                               
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n==1){                                                  /* history n */          
        n_cmds = 10;
    }
    else{   
        n_cmds = atoi(command[1]);                                                        /* history [n>20] */
        if(n_cmds > hist_limit){
            n_cmds = hist_limit;
        }
    }

    for(int i=hist_limit-n_cmds; i<hist_limit; i++){
        printf("%s", hist[i]);
    }
}