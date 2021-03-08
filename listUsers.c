/* Program stampa informacije o svim korisnicima iz passwd fajla
 *
 * Primer poziva:
 * ./list_users
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <pwd.h>

/* makro za obradu gresaka -> da ne bih stalno kucao if(...) */
#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			fprintf(stderr, "%s\n", userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

void printUser(struct passwd* userInfo);

int main(int argc, char** argv){
	check_error(argc == 1, "./userInfo");
	
	setpwent();
	
	struct passwd* currUser;
	while((currUser = getpwent()) != NULL){
		printUser(currUser);
	}
	
	endpwent();
	
exit(EXIT_SUCCESS);
}

void printUser(struct passwd* userInfo){
	fprintf(stdout, "###################################\n");
	fprintf(stdout, "Username: %s\n", userInfo->pw_name);
	fprintf(stdout, "User ID: %jd\n",(intmax_t)userInfo->pw_uid);
	fprintf(stdout, "Group ID: %jd\n",(intmax_t)userInfo->pw_gid);
	fprintf(stdout, "User info: %s\n",userInfo->pw_gecos);
	fprintf(stdout, "Homedir: %s\n",userInfo->pw_dir);
	fprintf(stdout, "Shell: %s\n", userInfo->pw_shell);
}
