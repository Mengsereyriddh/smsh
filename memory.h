#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *smsh_malloc(size_t n); 
void *smsh_calloc(size_t n, size_t size); 
void *smsh_realloc(void *p, size_t n);
void smsh_freelist(char **arglist);
