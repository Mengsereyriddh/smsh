#ifndef _CONTROLFLOW_H_
#define _CONTROLFLOW_H_

#include <stdio.h>

#include "smsh.h"

enum states { SMSH_NEUTRAL, SMSH_WANT_THEN, SMSH_THEN_BLOCK, SMSH_WANT_ELSE, SMSH_ELSE_BLOCK };

enum results { SMSH_SUCCESS, SMSH_FAIL };


static int smsh_if_state = SMSH_NEUTRAL;
static int smsh_if_result = SMSH_SUCCESS;
static int smsh_last_state = 0;

int smsh_syn_err(char *);
int smsh_is_ctl_cmd(char *);
int smsh_do_ctl_cmd(char **);
int smsh_is_ok_execute();


#endif // _CONTROLFLOW_H_
