#include "prompt.h"
#include "headers.h"

void shell_loop(){
    do{
        // Print Prompt
        prompt();

        // Get Input Command 
        char *command = NULL;
        size_t len;
        getline(&command, &len, stdin);
        // printf("Command: %s\n", command);

        // Input handling
        


    }
    while(1);
}

int main(int argc, char **argv)
{  
    gethostname(hostname, sizeof(hostname));
    if(gethostname(hostname, sizeof(hostname)) != 0){
        printf("\033[0;31mError: Unable to retrieve Hostname\033[0m");
        strcpy(hostname, "hostname");
    }

    getlogin_r(username, sizeof(username));
    if(getlogin_r(username, sizeof(username)) != 0){
        printf("\033[0;31mError: Unable to retrieve Username\033[0m");
        strcpy(username, "username");
    }
    
    getcwd(home, sizeof(home));
    if(!getcwd(home, sizeof(home))){
        printf("\033[0;31mError: Unable to Shell Home\033[0m");
        perror("getcwd() error");
        exit(1);
    }

    printf("\033[1;33m\n****************************\n\tHELLO WORLD!!\n****************************\n\033[0m");
    printf("\033[1;32m\n**** Welcome to C-Shell ****\n\n\033[0m");

    shell_loop();

    return 0;
}
