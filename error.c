/*
 * handle error for smsh.
 */


#include "error.h"
	
/*
 * print error msg.
 */
void smsh_fatal(char *s1, char *s2, int n) {
	fprintf(stderr, "Error: %s, %s\n", s1, s2);
	exit(n);
}

