/* program ilustruje komunikaciju dva procesa koji nisu u relaciju
 * roditelj-dete pomocu imenovanih pajpova 
 *
 * Server - salje poruke sve dok korisnik ne unese signal za kraj
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_SIZE (256)

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)\
	
int main(int argc, char** argv){
	check_error(argc == 2, "..");
	
	check_error(mkfifo(argv[1],0644) != -1, "mkfifo failed");
	
	int fd = open(argv[1], O_WRONLY);
	check_error(fd != -1, "failed");
	
	srand(time(NULL));
	char buf[MAX_SIZE];
	
	do{
		sprintf(buf, "%d\n",rand());
		printf("sending: %s\n", buf);
		
		check_error(write(fd,buf,strlen(buf)) != -1,"greska");
		printf("continue: (yes/no) ");
		scanf("%s",buf);
	}while(strcasecmp(buf, "no"));
	
	close(fd);
	exit(0);
}
