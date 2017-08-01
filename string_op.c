/*
 * string operation for smsh.
 */


#include "string_op.h"


/*
 * copy str that length equal to len.
 */
char *smsh_newstr(char *s, int len) {
	char *str = smsh_malloc(len + 1);
	str[len] = '\0';
	strncpy(str, s, len);
	return str;
}



/*
 * split a line into array of white space separated tokens
 */
char **smsh_splitline(char *line) {
	char **args = smsh_calloc(BUFSIZ, sizeof(char *));
	int spots = BUFSIZ / sizeof(char *);
	int bufspace = BUFSIZ;
	int argnum = 0;
	char *cp = line;

	if (NULL == line) 
		return NULL;

	while (*cp) {
		while (smsh_is_delim(*cp))
			cp++;
		if (*cp == '\n')
			break;
		
		/* args need expand? */
		if (argnum + 1 >= spots) {
			args = smsh_realloc(args, bufspace + BUFSIZ);
			bufspace += BUFSIZ;
			spots += (BUFSIZ / sizeof(char *));
		}

		char *start = cp;
		int len = 1;
		/* get a item. */
		while ((*++cp != '\0') && !(smsh_is_delim(*cp)))
			len++;
		
		/* copy a item to args. */
		args[argnum++] = smsh_newstr(start, len);
	}

	args[argnum] = NULL;
	return args;
}


