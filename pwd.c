#include "headers.h"

void pwd(ll n) { 

    if(n==1){
        char path[2000 ]= ""; 
        getcwd(path, sizeof(path));
        printf("%s\n", path);
    }
    else{
        printf("\033[0;31mError: Too many arguments\033[0m\n");
        return;
    }  
}