#include "headers.h"

void remove_spaces(char *string){
    int i, j = 0;

    for (i = 0; string[i]; i++) 
        if (string[i] != ' ' && string[i] != '\n' && string[i] != '\t') 
            string[j++] = string[i]; 
     
    string[j] = '\0';
    printf("spaces : \"%s\"\n", string);
}

void redirection(char *command, char *sub_commands[], ll n){
    
    int input = 0, output = 0, append = 0;    
    
    char *output_list[2];
    char *input_list[2];
    input_list[0] = command;

    char *output_file = NULL;
    char *input_file = NULL;

    int input_fd, output_fd;
    int actual_stdout = dup(STDOUT_FILENO);
    int actual_stdin = dup(STDIN_FILENO);

    if(strstr(command, "<") != NULL){
        input = 1;
        // printf("Input\n");
    }

    if(strstr(command, ">>") != NULL){
        append = 1;
        // printf("Append\n");
    }
    else if(strstr(command, ">") != NULL){
        output = 1;
        // printf("Output\n");
    }

    if(output == 1 || append == 1){
        output_list[0] = strtok(command, ">");
        output_list[1] = strtok(NULL, ">");
        input_list[0] = output_list[0];
    }
    printf("0: %s, 1: %s\n", output_list[0], output_list[1]);

    if(input == 1){
        input_list[0] = strtok(input_list[0], "<");
        input_list[1] = strtok(NULL, "<");
    
        // printf("0: %s, 1: %s\n", input_list[0], input_list[1]);
    }

    int nargs = 0; 
    char *args[100];

    args[nargs] = strtok(input_list[0], " ");
    while (args[nargs] != NULL)
    {
        nargs++;
        args[nargs] = strtok(NULL, " ");
    }
    args[nargs] = NULL;

    // for(int i=0; i<nargs; i++){
    //     printf("%s\n", args[i]);
    // }

    int pid;
    pid = fork();

    if(pid == -1){
        printf("\033[0;31mError: Unable to fork\033[0m\n");
        perror("fork");
        return;
    }
    else if(pid == 0){
        if(input == 1){

            input_file = strtok(input_list[1], " \n\t");
            // printf("input file: \"%s\"\n", input_file);

            if(input_file == NULL){
                printf("\033[0;31mError: File for input redirection not specified\033[0m\n");
                return;
            }

            input_fd  = open(input_file, O_RDONLY);
            if (input_fd < 0)
            {
                printf("\033[0;31mError: Unable to open file for input redirection\033[0m\n");
                perror("open:");
                return;
            }

            dup2(input_fd, 0);
            close(input_fd);
        }

        if(output == 1){

            output_file = strtok(output_list[1], " \t\n");
            printf("output file: \"%s\"\n", output_file);

            if(output_file == NULL){
                printf("\033[0;31mError: File for output redirection not specified\033[0m\n");
                return;
            }
            
            output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0)
            {
                printf("\033[0;31mError: Unable to open file for output redirection\033[0m\n");
                perror("open:");
                return;
            }

            dup2(output_fd, 1);
            close(output_fd);
        }

        if(append == 1){
            output_file = strtok(output_list[1], " \t\n");
            printf("output file: \"%s\"\n", output_file);

            if(output_file == NULL){
                printf("\033[0;31mError: File for output redirection not specified\033[0m\n");
                return;
            }

            output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (output_fd < 0)
            {
                printf("\033[0;31mError: Unable to open file for output redirection\033[0m\n");
                perror("open:");
                return;
            }

            dup2(output_fd, 1);
            close(output_fd);
        }

        int x = execvp(args[0], args);
        if(x == -1){
            printf("\033[0;31mError: Unable to execute\033[0m\n");
            perror("execvp");
            return; 
        }

        dup2(actual_stdin, 0);
        close(actual_stdin);
        
        dup2(actual_stdout, 1);
        close(actual_stdout);
    }
    else{
        int status;
        while (wait(&status) != pid);
    }
}