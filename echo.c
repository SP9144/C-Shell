#include "headers.h"

void echo(char *command, ll n) {
    
    if(n==1){                                           /* echo */
        return;
    }

    char* p;
    char string[2000]="";

    p = strstr(command, "echo ");
    strcpy(string, p+strlen("echo "));

    int len = strlen(string);

    if(string[0]=='\"' && string[len-1]=='\"'){         /* echo "<text>" */
        string[len-1]='\0';
        printf("%s\n", &string[1]);
    }
    else if(string[0]=='\'' && string[len-1]=='\''){    /* echo '<text>' */
        string[len-1]='\0';
        printf("%s\n", &string[1]);
    }
    else{                                               /* echo <text> */
        int i = 0;
        while (i < len)
        {
            if(string[i]==' ' && (string[i+1]==' ' || string[i-1]==' '))
            {
                for(int j=i;j<len;j++)
                string[j]=string[j+1];
                len--;
            }
            else
            {
                i++;
            }
        }
        printf("%s\n",string);
    }
    
}