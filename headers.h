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
#include <signal.h>
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
char lwd[2000];
int shellID;

// History
char hist[20][1000];

// Jobs
int njobs;
int pids[1000];
char names[1000][1000];

int killjob_flag;
int overkill_flag;

int curr_pid;
char curr_name[1000];

// Signals
int ctrlc_flag;
int ctrlz_flag;

// Functions
void shell_loop();                                              /* Main shell loop */
ll split_by(char *list[], char *command, char *delim);          /* Split command by delim */
void execute_command(char *list_command);                       /* Executes in-built commands */
void prompt();                                                  /* Print Prompt */
void cd(char *command[], ll n);                                 /* cd: Change Directory */
void pwd(ll n);                                                 /* pwd: Present Working Directory */
void echo(char *command, ll n);                                 /* echo: Print to stdout */
void ls(char *command[], ll n);                                 /* ls: List files */
void pinfo(char *command[], ll n);                              /* pinfo: Process Information */
void read_history();                                            /* Read history from history.txt */
void write_history();                                           /* Write history to history.txt */
void update_history(char *command);                             /* Update history */
void history(char *command[], ll n);                            /* Display history */    
void foreground(char *commands[], ll n);                        /* Run process in foreground */
void background(char *commands[], ll n);                        /* Run process in background */
void redirection(char *command);                                /* Redirection */
void piping(char *command);                                     /* Piping */
void set(char *commands[], ll n);                               /* setenv: Set env variable */
void unset(char *commands[], ll n);                             /* unsetenv: Unset env variable */
void print_status();
void ctrlC(int sig_num);
void ctrlZ(int sig_num);
void print_jobs();
void kjob(char *commands[], ll n);
void overkill();
void bg(char *commands[], ll n);
void fg(char *commands[], ll n);


#endif