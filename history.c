#include "headers.h"

void read_history(){

    char path[2000]="";
    strcpy(path, home);
    strcat(path, "/history.txt");

    char *command = NULL;
    size_t len;

    FILE *file_ptr = NULL;
    file_ptr = fopen(path, "r");

    if(file_ptr == -1){
        printf("\033[0;31mError: history.txt not found\033[0m\n");
        perror("fopen");
    }

    // for(int i=0; i<20; i++){
    //     getline(&command, &len, file_ptr);
    //     strcpy(hist[i], command);
    //     printf("%d %s\n", i, hist[i]);
    // }

    int i=0;
    while(getline(&command, &len, file_ptr) != -1){
        strcpy(hist[i], "");
        strcpy(hist[i], command);
        i++;
    }

    // for(int i=0; i<20; i++){
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

    if(file_ptr == -1){
        printf("\033[0;31mError: history.txt not found\033[0m\n");
        perror("fopen");
    }

    for(int i=0; i<20; i++){

        fprintf(file_ptr, "%s", hist[i]);
    }
    fclose(file_ptr);
}

void update_history(char *command){
    for(int i=1; i<20; i++){
        strcpy(hist[i-1], hist[i]);
    }
    strcpy(hist[20-1],command);

    // for(int i=0; i<20; i++){
    //     printf("%s\n", hist[i]);
    // }
    
    write_history();

}

void history(char *command[], ll n){
    int n_cmds;
    if(n>2){                               
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n==1){                          
        n_cmds = 10;
    }
    else{
        if(atoi(command[1]) > 20){
            n_cmds = 20;
        }
        n_cmds = atoi(command[1]);
    }

    for(int i=20-n_cmds; i<20; i++){
        printf("%s", hist[i]);
    }
}