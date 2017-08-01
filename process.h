#ifndef _PROCESS_H_
#define _PROCESS_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int smsh_process(char **args);

int smsh_execute(char *argv[]); 

char *smsh_next_cmd(char *prompt, FILE *fp); 

#endif //_PROCESS_H_
