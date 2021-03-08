/* program kreira child proces i ilustruje razlikovanje grana
 * child i parent procesa
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/wait.h>

#define check_error(expr, msg)\
	do {\
		if (!(expr)) {\
			perror(msg);\
			exit(EXIT_FAILURE); \
		} \
	} while(0)

int main(void){
	
	pid_t pid = fork();
	
	check_error(pid != -1, "fork failed");
	
	if(pid > 0){
		printf("Parent: pid = %jd, child id = %jd\n" , (intmax_t)getpid(), (intmax_t)pid);
	}
	else{
		printf("Child: pid = %jd, parend id = %jd\n",(intmax_t)getpid(), (intmax_t)getppid());
		exit(EXIT_SUCCESS);
	}
	
	check_error(wait(NULL) != -1, "wait null");
	printf("Ovo stampa samo parent\n");

exit(EXIT_SUCCESS);
}
