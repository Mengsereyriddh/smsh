#ifndef _VARTABLE_H_
#define _VARTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smsh_store_val(char *val);

int smsh_export_val(char *val);

void smsh_list_val(void);

void smsh_free_val(void);

void smsh_env_to_tab(char **env);

char **smsh_tab_to_env(void);

#endif // _VARTABLE_H_

