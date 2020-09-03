#include "headers.h"

void prompt() { 
    char prompt[500000]=""; 
    char dir[200000]="";
    char* p; 

    getcwd(cwd, sizeof(cwd));

    if(strcmp(home, cwd) == 0){         /* path: cwd = home */
        strcpy(dir, "~");
    }
    else if(strlen(cwd)<strlen(home)){  /* path: cd .. when in home */
        chdir(cwd);
        strcpy(dir, cwd);
    }
    else{                               /* path: relative to home*/
        p = strstr(cwd, home);
        strcpy(dir, "~");
        strcat(dir, p+strlen(home));
    }

    printf("\033[0;30m\x1b[44m<%s@%s:%s>\033[0m ", username, hostname, dir);
}
