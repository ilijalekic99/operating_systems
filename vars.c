/* program ilustruje potpuno kopiranje adresnih prostora prilikom kreiranja 
 * child procesa i nezavisnost promenljivih u parent u child granama 
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
	int x = 10;
	int y = 50;
	
	printf("pre forka: x(%d), y(%d)\n",x,y);
	
	pid_t pid = fork();
	
	check_error(pid != -1, "fork failed");
	
	if(pid > 0){
		x += 5;
		y -= 5;
	}
	else{
		x-=5;
		y+=5;
		printf("chiled: x(%d), y(%d)\n",x,y);
		exit(EXIT_SUCCESS);
	}
		
	check_error(wait(NULL) != -1 , "wait failed");
	
exit(EXIT_SUCCESS);	
}
