#include "prompt.h"
#include "headers.h"
// #include "execute_com.c"

ll split_by(char *list[], char *command, char *delim){
    
    ll n = 0; 
    list[n] = strtok(command, delim);
    while (list[n] != NULL)
    {
        // printf("command %lld: %s\n", n, list[n]);
        n++;
        list[n] = strtok(NULL, delim);
    }
    return n;
}

void shell_loop(){
    do{
        // Print Prompt
        prompt();

        // Get Input Command 
        char *command = NULL;
        size_t len;
        getline(&command, &len, stdin);
        // printf("Command: %s\n", command);

        // Input handling - list of commands - ';'
        char *list_command[10000];
        ll n_command = 0;
        n_command = split_by(list_command, command, ";\n");
        // printf("number of commands: %lld\n", n_command);

        // Execute Commands
        for(ll i = 0; i < n_command; i++){
            char *curr_command[1000];
            ll n_curr_command = 0;
            n_curr_command = split_by(curr_command, command, " \t\n\r");

            for(ll j = 0; j < n_command; j++){
                printf("command %lld: %s\n", j, curr_command[j]);
            }
        }
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
    // prompt();

    return 0;
}
