/*
 * smsh.c
 * small shell 
 */

#include "smsh.h"
#include "memory.h"
#include "string_op.h"
#include "signal.h"
#include "process.h"
#include "vartable.h"


extern char **environ;


int main(void) {
	char *cmdline = NULL;
	char *prompt = DFL_PROMPT;
	char **arglist = NULL;
	int result = 0;
	
	smsh_env_to_tab(environ);

	// ignored shell signal.
	smsh_ignored_signal();
	
	// 1. get cmd.
	while ((cmdline = smsh_next_cmd(prompt, stdin)) != NULL) {
		// 2. split cmd
		if ((arglist = smsh_splitline(cmdline)) != NULL) {
			// 3. process cmd
			result = smsh_process(arglist);
			smsh_freelist(arglist);
		}
		
		free(cmdline);
	}

	return 0;
}

