#include "utils.h"
#include "vartable.h"

#include <unistd.h>


/**
 * @synopsis  smsh_cd 
 *
 * @param dir
 */
void smsh_cd(char *dir) {
	if ((NULL == dir) || (strcmp(dir, "") == 0) || (strcmp(dir, "~/") == 0)) {
		chdir(getenv("HOME"));
	} else {
		if (chdir(dir) == -1) 
			printf("smsh: cd: %s: No such file or directory\n", dir); 
	}
}


/**
 * @synopsis  smsh_prompt 
 */
void smsh_prompt(void) {
	// get user name -> orange
	char *user_name = getenv("USER");

	// get pwd -> /home/orange/testdir/somedir
	//char *pwd = getenv("PWD");
	char *pwd = getenv("PWD");

	char buf[50];
	char *cwd = getcwd(buf, sizeof(buf));
	//printf("cwd = %s\n", cwd);	

	// get home dir -> /home/orange
	char *home_dir = getenv("HOME");
	//printf("home_dir = %s\n", home_dir);
	
	// get computer name -> ubuntu
	char *session_name = getenv("DESKTOP_SESSION");
	
	char *show_dir = NULL;
	if (strlen(cwd) < strlen(home_dir)) {
		show_dir = cwd;
	} else {
		show_dir = cwd + strlen(home_dir);
	}
	
	//printf("show_dir = %s\n", show_dir);	
	
	// cat all to prompt: 
	// orange@ubuntu:~/testdir/somedir$
	// user_name + @ + session_name + ~: + show_dir

	char prompt[100] = { 0 };
	strcat(prompt, user_name);
	strcat(prompt, "@");
	strcat(prompt, session_name);
	
	if (strlen(cwd) < strlen(home_dir))
		strcat(prompt, ":");
	else
		strcat(prompt, ":~");

	strcat(prompt, show_dir);
	strcat(prompt, "$ ");
	
	printf("%s", prompt);
}




/**
 * @synopsis  smsh_exit 
 */
void smsh_exit(void) {
	smsh_free_val();
	exit(0);
}












