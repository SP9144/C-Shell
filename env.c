#include "headers.h"

void set(char *commands[], ll n){
    if(n == 1){
        printf("\033[0;31mError: Too less arguments\033[0m\n");
        return;
    }
    else if(n > 3){
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else if(n == 2){
        int x = setenv(commands[1], "\0", 1);
        if(x == -1){
            printf("\033[0;31mError: Unable to set\033[0m\n");
            perror("setenv");
            return;
        }
    }
    else{
        int x = setenv(commands[1], commands[2], 1);
        if(x == -1){
            printf("\033[0;31mError: Unable to set\033[0m\n");
            perror("setenv");
            return;
        }
    }
}

void unset(char *commands[], ll n){
    if(n < 2){
        printf("\033[0;31mError: Too less arguments\033[0m\n");
        return;
    }
    else if(n > 2){
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }
    else {
        int x = unsetenv(commands[1]);
        if(x == -1){
            printf("\033[0;31mError: Unable to unset\033[0m\n");
            perror("unsetenv");
            return;
        }
    }
}