/*
 * command processing layer.
 */

#include "process.h"
#include "signal.h"
#include "controlflow.h"
#include "memory.h"
#include "builtin.h"
#include "vartable.h"
#include "utils.h"


extern char **environ;

void smsh_pre_handle_args(char **args) {
	if (strcmp(args[0], "echo") == 0) {
		// echo "hello world"
		//      hello worldd"
		// hello world
		if (args[1][0] == '\"') {
			char *prv = args[1];
			char *cur = prv + 1;
			for (int i = 0; i < strlen(args[1]); i++)
				*prv++ = *cur++;
			*prv = '\0';
			printf("args[1] = %s\n", args[1]);
		}
	}

}

/**
 * @synopsis  smsh_process process user command.
 *
 * @param args: cmd params
 *
 * @return result of processing cmd  
 */
int smsh_process(char **args) {
	int res = 0;
	
	if (args[0] == NULL) {
		res = 0;
	} else if (strcmp(args[0], "cd") == 0) {
		smsh_cd(args[1]);
	} else if (strcmp(args[0], "exit") == 0) {
		smsh_exit();
	} else if (smsh_is_ctl_cmd(args[0])) {
		res = smsh_do_ctl_cmd(args);
	} else if (smsh_is_ok_execute()) {
		if (!smsh_builtin_cmd(args, &res)) {
			// pre handle args
			//smsh_pre_handle_args(args);
			res = smsh_execute(args);
		}
	}
	
	return res;
}


/*
 * run a program passing it argv.
 */
int smsh_execute(char *argv[]) {
	int pid = 0;
	int child_info = -1;
	
	/* do nothing. */
	if (argv[0] == NULL)
		return 0;

	if ((pid = fork()) == -1) {
		perror("fork");
	} else if (pid == 0){
		environ = smsh_tab_to_env();
		smsh_recovery_signal();
		execvp(argv[0], argv);
		perror("cannot exe command");
		exit(1);
	} else {
		if (-1 == wait(&child_info))
			perror("wait");
	}
	
	return child_info;
}


/*
 * read next command line from fp.
 * return allocated string holding command line
 */
char *smsh_next_cmd(char *prompt, FILE *fp) {
	char *buf = NULL;
	int bufspace = 0;
	int pos = 0;
	char in_c = 0;

	smsh_prompt();

	while ((in_c = getc(fp)) != EOF) {
		/* need more space. */
		if ((pos + 1) >= bufspace) {
			if (bufspace == 0)
				buf = smsh_malloc(BUFSIZ);
			else
				buf = smsh_realloc(buf, bufspace + BUFSIZ);
			bufspace += BUFSIZ;
		}

		/* command is end. */
		if (in_c == '\n')
			break;

		/* add to buffer. */
		buf[pos++] = in_c;
	}
	
	/* no input and enter. */
	if ((EOF == in_c) && (0 == pos))
		return NULL;

	buf[pos] = '\0';
	
	return buf;
}



