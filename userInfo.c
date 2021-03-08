/* Program stampa informacije o korisniku na osnovu njegovog
 * korisnickog imena. Korisnicko ime se prosledjuje kao argument
 * komendne linije 
 *
 * Primer poziva:
 * ./user_info korisnik
 */
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
	
int main(int argc, char** argv) {

	check_error(argc == 2, "./userInfo userName");

	struct passwd* userInfo;

	userInfo = getpwnam(argv[1]);
	
	check_error(userInfo != NULL, "user name doesn't exist");

	struct passwd* userInfo_copy 
			= malloc(sizeof(struct passwd));
	check_error(userInfo_copy != NULL, "malloc failed");
	memcpy(userInfo_copy, userInfo, sizeof(struct passwd));

	fprintf(stdout, "Username: %s\n", userInfo_copy->pw_name);
	fprintf(stdout, "User ID: %jd\n", (intmax_t)userInfo_copy->pw_uid);
	fprintf(stdout, "Group ID: %jd\n", (intmax_t)userInfo_copy->pw_gid);
	fprintf(stdout, "User Info: %s\n", userInfo_copy->pw_gecos);
	fprintf(stdout, "Homedir: %s\n", userInfo_copy->pw_dir);
	fprintf(stdout, "Shell: %s\n", userInfo_copy->pw_shell);

	free(userInfo_copy);
	exit(EXIT_SUCCESS);
}
