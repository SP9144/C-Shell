#include "headers.h"

void pwd(ll n) { 
        char path[2000 ]= ""; 
        getcwd(path, sizeof(path));
        printf("%s\n", path);
}