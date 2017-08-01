/*
 * manager memory for smsh.
 */

#include "memory.h"

extern void smsh_fatal(char *s1, char *s2, int n); 

/*
 * smsh malloc: add some error msg.
 */
void *smsh_malloc(size_t n) {
	void *memory = NULL;
	if ((memory = malloc(n)) == NULL)
		smsh_fatal("out of memory", "", 1);
	return memory;
}

/*
 * smsh calloc: add some error msg.
 */
void *smsh_calloc(size_t n, size_t size) {
	void *memory = NULL;
	if ((memory = calloc(n, size)) == NULL)
		smsh_fatal("out of memory", "", 1);
	return memory;
}



/*
 * smsh remalloc: add some msg.
 */
void *smsh_realloc(void *p, size_t n) {
	void *memory = NULL;
	if ((memory = realloc(p, n)) == NULL)
		smsh_fatal("smsh_remalloc failed", "", 1);
	return memory;
}


/*
 * free the list returned by smsh_splitline.
 */
void smsh_freelist(char **arglist) {
	char **cp = arglist;
	while (*cp)
		free(*cp++);

	/* Don't forget free self. */
	free(arglist);
}


