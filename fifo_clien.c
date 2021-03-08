/* program ilustruje komunikaciju dva procesa koji nisu u relaciju
 * roditelj-dete pomocu imenovanih pajpova 
 *
 * Klijent - cita poruke sve dok server ne zatvori svoju stranu pajpa
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (256)

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)\

int main(int argc, char** argv){
	check_error(argc == 2, "greska");
	
	int fd = open(argv[1], O_RDONLY);
	check_error(fd != -1, "failed");
	
	do{
		char buffer[MAX_SIZE];
		int bytesRead = 0;
		
		bytesRead = read(fd, buffer, MAX_SIZE);
		
		check_error(bytesRead != -1, "greska");
		
		if(bytesRead == 0)
			break;
		buffer[bytesRead] = 0;
		
		printf("RECIVED: %d\n", atoi(buffer));
	}while(1);
	
	close(fd);
	
	exit(0);
}
