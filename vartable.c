/*
 * var table for smsh.
 */

#include "vartable.h"
#include "memory.h"


#define MAXVARS 200

struct var {
	char *name_val;
	int global;
};

// var table
static struct var vtab[MAXVARS];

// vtab index
static int g_vindex = 0;

/**
 * @synopsis  smsh_store_val store a val: name=value
 *
 * @param val: a name=value string 
 *
 * @return 1 if ok, 0 if fail  
 */
int smsh_store_val(char *val) {
	memset((void *)&vtab[g_vindex], sizeof(struct var), 0);
	int prv_index = g_vindex;

	// alocate memory
	char * copy_str = (char *)smsh_malloc(strlen(val) + 1);
	
	// copy val
	strcpy(copy_str, val);
	
	// set vtab
	vtab[g_vindex].name_val = copy_str;
	vtab[g_vindex].global = 1;
	
	// add g_vindex
	g_vindex++;

	// return 
	return (vtab[prv_index].name_val != NULL);
}

/**
 * @synopsis  smsh_export_val show val
 *
 * @param val: only val name
 *
 * @return 1 : ok, 0 : fail 
 */
int smsh_export_val(char *val) {
	for (int i = 0; i < g_vindex; i++) {
		if (strstr(vtab[i].name_val, val) != NULL) {
			printf("%s\n", vtab[i].name_val);
			return 1;
		}
	}

	return 0;
}

/**
 * @synopsis  smsh_list_val show all val in vtab.
 */
void smsh_list_val(void) {
	for (int i = 0; i < g_vindex; i++) 
		printf("%s\n", vtab[i].name_val);
}


/**
 * @synopsis  smsh_free_val free val memory
 */
void smsh_free_val(void) {
	for (int i = 0; i < g_vindex; i++) {
		free(vtab[i].name_val);
	}
}



/**
 * @synopsis  smsh_env_to_tab conver environ to tab.
 *
 * @param env
 */
void smsh_env_to_tab(char **env) {
	g_vindex = 0;
	for (int i = 0; env[i]; i++) {
		// alocate memory
		char * copy_str = (char *)smsh_malloc(strlen(env[i]) + 1);

		// copy val
		strcpy(copy_str, env[i]);

		// set vtab
		vtab[g_vindex].name_val = copy_str;
		vtab[g_vindex].global = 1;

		// add g_vindex
		g_vindex++;
	}

	for (int i = g_vindex; i < MAXVARS; i++) {
		vtab[i].name_val = NULL;
		vtab[i].global = 0;
	}
}


/**
 * @synopsis  smsh_tab_to_env 
 *
 * @return   
 */
char **smsh_tab_to_env(void) {
	// allocate env table
	char **env = (char **)smsh_malloc(g_vindex * sizeof(char *));
	for (int i = 0; i < g_vindex; i++)
		env[i] = vtab[i].name_val;
	env[g_vindex] = NULL;
	return env;
}

