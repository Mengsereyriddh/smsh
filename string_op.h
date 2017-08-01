#ifndef _STRING_OP_H_
#define _STRING_OP_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "utils.h"


char *smsh_newstr(char *s, int len); 

char **smsh_splitline(char *line);

#endif // _STRING_OP_H_
