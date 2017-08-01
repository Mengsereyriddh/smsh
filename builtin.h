#ifndef _BUILTIN_H_
#define _BUILTIN_H_


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int smsh_assign(char *val); 

int smsh_okname(char *name);

int smsh_builtin_cmd(char **args, int *res); 

#endif // _BUILTIN_H_
