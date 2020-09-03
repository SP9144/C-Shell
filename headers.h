#ifndef __HEADER_H
#define __HEADER_H

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 

#define ll long long int 

// Host and username buffers
char hostname[200];
char username[200];

// Pseudo-home for Shell
char home[2000];
char cwd[2000];

void shell_loop();                      /* Main shell loop */
void prompt();                          /* Print Prompt */
void cd(char *command[],ll n);          /* cd: Change Directory */
void pwd(ll n);                         /* pwd: Present Working Directory */

#endif