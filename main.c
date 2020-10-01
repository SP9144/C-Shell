#include "headers.h"

ll split_by(char *list[], char *command, char *delim){
    
    ll n = 0; 
    list[0] = strtok(command, delim);
    while (list[n] != NULL)
    {
        // printf("command %lld: %s\n", n, list[n]);
        n++;
        list[n] = strtok(NULL, delim);
    }
    return n;
}

void execute_command(char *list_command){
    //*** Dividing current command ***
    char *curr_command[1000];
    char cmd[2000];
    ll n_curr_command = 0;
    strcpy(cmd, list_command);
    n_curr_command = split_by(curr_command, cmd, " \t\n\r");
    
    // printf("number of subcommands: %lld\n", n_curr_command);
    // for(ll j = 0; j < n_curr_command; j++){
    //     printf("subcommand %lld: %s\n", j, curr_command[j]);
    // }

    if(strcmp(curr_command[0], "exit") == 0){                       /* exit */
        printf("Exiting\n");
        exit(0);
    }
    else if(strcmp(curr_command[0], "cd") == 0){                    /* cd */
        if(!strcmp(curr_command[n_curr_command-1], "&"))
            cd(curr_command, n_curr_command-1);
        else
            cd(curr_command, n_curr_command);
    }
    else if(strcmp(curr_command[0], "pwd") == 0){                   /* pwd */
        if(!strcmp(curr_command[n_curr_command-1], "&"))
            pwd(n_curr_command-1);
        else
            pwd(n_curr_command);
    }
    else if(strcmp(curr_command[0], "echo") == 0){                  /* echo */
        if(!strcmp(curr_command[n_curr_command-1], "&"))
            echo(list_command, n_curr_command-1);
        else
            echo(list_command, n_curr_command);
    }
    else if(strcmp(curr_command[0], "ls") == 0){                    /* ls */
        if(!strcmp(curr_command[n_curr_command-1], "&"))
            ls(curr_command, n_curr_command-1);
        else
            ls(curr_command, n_curr_command);
    }
    else if(strcmp(curr_command[0], "pinfo") == 0){                 /* pinfo */
        if(!strcmp(curr_command[n_curr_command-1], "&"))
            pinfo(curr_command, n_curr_command-1);
        else
            pinfo(curr_command, n_curr_command); 
    }
    else if(strcmp(curr_command[0], "history") == 0){               /* history */
        if(!strcmp(curr_command[n_curr_command-1], "&"))
            history(curr_command, n_curr_command-1);
        else
            history(curr_command, n_curr_command);
    }
    else if(strcmp(curr_command[0], "setenv") == 0){                /* setenv */
        set(curr_command, n_curr_command);
    }
    else if(strcmp(curr_command[0], "unsetenv") == 0){              /* unsetenv */
        unset(curr_command, n_curr_command);
    }
    else if(strcmp(curr_command[0], "jobs") == 0){                  /* jobs */
        print_jobs();
    }
    else if(strstr(list_command, "&")){                             /* background processes - & */
        background(curr_command, n_curr_command);
    }
    else{                                                           /* foreground processes*/
        foreground(curr_command, n_curr_command);
        // printf("\033[0;31mError: command not found\033[0m\n");
    }
}

void shell_loop(){
    do{
        //*** Print Prompt ***
        prompt();

        //*** Signals ***
        signal(SIGCHLD, print_status);

        //*** Get Input Command ***
        char *command = NULL;
        size_t len;
        getline(&command, &len, stdin);
        // printf("Command: %s\n", command);

        //*** Update history with command***
        update_history(command);

        //*** Input handling - list of commands - ';' ***
        char *list_command[10000];
        ll n_command = 0;
        n_command = split_by(list_command, command, ";\n");
        
        // printf("number of commands: %lld\n", n_command);
        // for(ll k = 0; k < n_command; k++){
        //         printf("command %lld: %s\n", k, list_command[k]);
        //     }

        //*** Execute Commands ***
        for(ll i = 0; i < n_command; i++){

            // printf("command %lld: %s\n", i, list_command[i]);
            //*** Check Piping ***
            int pipe;
            if(strstr(list_command[i], "|") != NULL){
                pipe = 1;
            }

            if(pipe == 1){
                piping(list_command[i]);
                continue;
            }

            
            //*** Check Redirection ***
            int redirect;
            if(strstr(list_command[i], ">") != NULL || strstr(list_command[i], "<") != NULL ){
                redirect = 1;
            }

            if(redirect == 1){
                redirection(list_command[i]);
                continue;
            }
            
            execute_command(list_command[i]);

            // printf("njobs - loop %d\n", njobs);
        }
    }
    while(1);
}

int main(int argc, char **argv)
{  
    strcpy(lwd, home);

    njobs = 0;
    for(int i=0; i<1000; i++)
    {
        strcpy(names[i], "");
        pids[i] = 0;
    }

    gethostname(hostname, sizeof(hostname));
    if(gethostname(hostname, sizeof(hostname)) != 0){
        printf("\033[0;31mError: Unable to retrieve Hostname\033[0m\n");
        perror("gethostname(): ");
        strcpy(hostname, "hostname");
    }


    getlogin_r(username, sizeof(username));
    if(getlogin_r(username, sizeof(username)) != 0){
        printf("\033[0;31mError: Unable to retrieve Username\033[0m\n");
        perror("getlogin_r(): ");
        strcpy(username, "username");
    }
    
    getcwd(home, sizeof(home));
    if(!getcwd(home, sizeof(home))){
        printf("\033[0;31mError: Unable to Shell Home\033[0m\n");
        perror("getcwd(): ");
        exit(1);
    }
    
    read_history();

    printf("\033[1;33m\n****************************\n\tHELLO WORLD!!\n****************************\n\033[0m");
    printf("\033[1;32m\n**** Welcome to C-Shell ****\n\n\033[0m");

    shell_loop();
    // prompt();

    return 0;
}