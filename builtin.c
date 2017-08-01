/*
 * contains the switch and the functions for bulitin commands.
 */

#include "builtin.h"
#include "vartable.h"

/**
 * @synopsis  smsh_builtin_cmd: run a builtin cmd.
 *
 * @param arg: cmd arg
 * @param res: 
 *
 * @return 1 : if arg[0] is builtin, 0 : if not 
 */
int smsh_builtin_cmd(char **args, int *res) {
	int is_builtin_cmd = 0;

	// list val
	if (strcmp(args[0], "set") == 0) {
		smsh_list_val();
		*res = 0;
		is_builtin_cmd = 1;	
	// add val	
	} else if (strchr(args[0], '=') != NULL) { 
		*res = smsh_assign(args[0]);
		//printf("smsh_builtin_cmd: *res = %d\n", *res);
		// smsh_assign is success.
		if (*res != -1)
			is_builtin_cmd = 1;	
	// export val
	} else if (strcmp(args[0], "export") == 0) {
		if ((args[1] != NULL) && smsh_okname(args[1]))
			*res = smsh_export_val(args[1]);
		else
			*res = 1;
		is_builtin_cmd = 1;
	}
	
	return is_builtin_cmd;
}


/**
 * @synopsis  smsh_store_val 
 *
 * @param val: name=val
 *
 * @return -1 if val is illegal, or result of smsh_store_val
 */
int smsh_assign(char *val) {
	char *split = strchr(val, '=');
	*split = '\0';

	if (smsh_okname(val)) {
		*split = '=';
		return smsh_store_val(val);
	} else {
		printf("smsh_assign else.\n");
		*split = '=';
		return -1;
	}
}


/**
 * @synopsis  smsh_okname determines if a val name is legal
 *
 * @param name: val name
 *
 * @return  1: yes, 0: no
 */
int smsh_okname(char *name) {
	//for (char *p = name; *p; p++) {
	char *p = name;

	// bug!!!
	//if ((isdigit(*p) && (p == name)) || (isalnum(*p)) || (*p == '_')) {
	if ((isdigit(*p) && (p == name)) || (*p == '_')) {
		printf("for: invalid name.\n");
		return 0;
	}
	
	/*
	if (name != NULL) {
		printf("ok name != NULL.\n");
		return 1;
	} else {
		printf("name = NULL.\n");
		return 0;
	}
	*/

	// name don't equal to NULL !
	return (name != NULL);
}


