#include "prompt.h"
#include "headers.h"

void prompt() { 
    char prompt[500000]=""; 
    char dir[200000]="";
    char* p; 

    getcwd(cwd, sizeof(cwd));

    if(strcmp(home, cwd) == 0){
        strcpy(dir, "~");
    }
    else{
        p = strstr(cwd, home);
        strcpy(dir, p+strlen(home));
    }

    printf("\033[0;30m\x1b[44m<%s@%s:%s>\033[0m ", username, hostname, dir);
}
