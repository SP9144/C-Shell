#ifndef __HEADER_H
#define __HEADER_H

#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/wait.h>
#include <sys/types.h>

#define ll long long int 

// Host and username buffers
char hostname[200];
char username[200];

// Pseudo-home for Shell
char home[2000];
char cwd[2000];

// History
char hist[20][1000];

void shell_loop();                                      /* Main shell loop */
void prompt();                                          /* Print Prompt */
void cd(char *command[], ll n);                         /* cd: Change Directory */
void pwd(ll n);                                         /* pwd: Present Working Directory */
void echo(char *command, ll n);                         /* echo: Print to stdout */
void ls(char *command[], ll n);                         /* ls: List files */
void pinfo(char *command[], ll n);                      /* pinfo: Process Information */
void read_history();                                    /* Read history from history.txt */
void write_history();                                   /* Write history to history.txt */
void update_history(char *command);                     /* Update history */
void history(char *command[], ll n);                    /* Display history */    
void foreground(char *commands[], ll n);                /* Run process in foreground */
void background(char *commands[], ll n);                /* Run process in background */

#endif