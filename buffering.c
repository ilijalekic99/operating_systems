/* program ilustruje razlicite modove baferisanja 
 * kao i preusmeravanje fajol deskriptora
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)
	
int main(int argc, char** argv) {
	check_error(argc == 2, "greska");
	check_error(setvbuf(stdout,NULL,_IOFBF,0) == 0, "greska");
	
	printf("%s","NEKA PORUKA");
	
	int fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0664);
	check_error(fd != -1, "greska");
	
	int fdCpy = dup(STDOUT_FILENO);
	check_error(fdCpy != -1,"...");
	
	check_error(dup2(fd,STDOUT_FILENO) != -1, "...");
	printf("ova poruka ide u fajl\n");
	
	check_error(dup2(fdCpy,STDOUT_FILENO) != -1, "...");
	close(fd);
	
exit(0);
}
