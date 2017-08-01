/*
 * signal operation for smsh.
 */

#include "signal.h"


/*
 * ignored shell SIGINT and SIGQUIT signal.
 */
void smsh_ignored_signal(void) {
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


/**
 * @synopsis  smsh_recovery_signal recovery SIGINT and SIGQUIT signal.
 */
void smsh_recovery_signal(void) {
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

