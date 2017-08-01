#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define DFL_PROMPT	"cdeveloper@linux:smsh$ "

#define smsh_is_delim(x) 	((x) == ' ' || (x) == '\t')

void smsh_cd(char *dir);

void smsh_prompt(void);

void smsh_exit(void);
#endif // _UTILS_H_
