/*
 * process "if - then - else - fi" control flow.
 */

#include "controlflow.h"


extern int smsh_process(char **arglist);
extern void smsh_fatal(char *s1, char *s2, int n);

/**
 * @synopsis  smsh_is_ok_execute determine the shell shoule exe a cmd.
 *
 * @return  yes: 1, no: 0 
 */
int smsh_is_ok_execute() {
	int res = 1;

	if (smsh_if_state == SMSH_WANT_THEN) {
		smsh_syn_err("then expected");
		res = 0;
	} else if (smsh_if_state == SMSH_THEN_BLOCK && smsh_if_result == SMSH_SUCCESS) {
		res = 1;
	} else if (smsh_if_state == SMSH_THEN_BLOCK && smsh_if_result == SMSH_FAIL) {
		res = 0;
	} else if (smsh_if_state == SMSH_ELSE_BLOCK && smsh_if_result == SMSH_SUCCESS) {
		res = 0; 
	} else if (smsh_if_state == SMSH_ELSE_BLOCK && smsh_if_result == SMSH_FAIL) {
		res = 1;
	} else {
		// do nothing...
	}

	return res;
}


/**
 * @synopsis  smsh_is_ctl_cmd to report if the cmd is a shell cmd.
 *
 * @param s: cmd
 *
 * @return yes: 1, no: 0
 */
int smsh_is_ctl_cmd(char *s) {
	return ((strcmp(s, "if") == 0) || (strcmp(s, "then") == 0) || (strcmp(s, "else") == 0) || (strcmp(s, "fi") == 0));
}


/**
 * @synopsis  smsh_do_ctl_cmd to exe control cmd.
 *
 * @param args: control cmd
 *
 * @return  ok: 1, syntax error: -1 
 */
int smsh_do_ctl_cmd(char **args) {
	char *cmd = args[0];
	int res = -1;

	if (strcmp(cmd, "if") == 0) {
		if (smsh_if_state != SMSH_NEUTRAL) 
			res = smsh_syn_err("if unexpected");
		else {
			smsh_last_state = smsh_process(args + 1);
			smsh_if_result = (smsh_last_state == 0 ? SMSH_SUCCESS : SMSH_FAIL);
			smsh_if_state = SMSH_WANT_THEN;
			
			res = 0;
		}
	} else if (strcmp(cmd, "then") == 0) {
		if (smsh_if_state != SMSH_WANT_THEN) {
			res = smsh_syn_err("then unexpected");
		} else {
			smsh_if_state = SMSH_THEN_BLOCK;
			res = 0;
		}
	} else if (strcmp(cmd, "else") == 0) {
		if (smsh_if_state != SMSH_THEN_BLOCK) {
			res = smsh_syn_err("else unexpected");
		} else {
			smsh_if_state = SMSH_ELSE_BLOCK;
			res = 0;
		}
	} else if (strcmp(cmd, "fi") == 0) {
		if ((smsh_if_state != SMSH_ELSE_BLOCK) && (smsh_if_state != SMSH_THEN_BLOCK)) {
			res = smsh_syn_err("fi unexpected");
		} else {
			smsh_if_state = SMSH_NEUTRAL;
			res = 0;
		}
	} else {
		smsh_fatal("internal error processing:", cmd, 2);
	}
	
	return res;
}



/**
 * @synopsis  smsh_syn_err handles syntax in ctl struct.
 *
 * @param msg
 *
 * @return   
 */
int smsh_syn_err(char *msg) {
	smsh_if_state = SMSH_NEUTRAL;
	fprintf(stderr, "syntax error: %s\n", msg);
	return -1;
}


