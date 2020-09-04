#ifndef __HEADER_H
#define __HEADER_H

#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>

#define ll long long int 

// Host and username buffers
char hostname[200];
char username[200];

// Pseudo-home for Shell
char home[2000];
char cwd[2000];

void shell_loop();                      /* Main shell loop */
void prompt();                          /* Print Prompt */
void cd(char *command[], ll n);         /* cd: Change Directory */
void pwd(ll n);                         /* pwd: Present Working Directory */
void echo(char *command, ll n);         /* echo: Print to stdout */
void ls(char *command[], ll n);           /* ls: List files */

#endif