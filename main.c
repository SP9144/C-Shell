#include "prompt.h"
#include "headers.h"

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
    printf("\033[1;33m\n**** Welcome to C-Shell ****\n\n\033[0m");

    prompt();
}
