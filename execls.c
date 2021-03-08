/* program ilustruje upotrebu execlp */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define check_error(expr, msg)\
	do {\
		if (!(expr)) {\
			perror(msg); \
			exit(EXIT_FAILURE);\
		}\
	}while(0)

int main(int argc, char** argv){
	check_error(argc == 3, "...");
	
	pid_t pid = fork();
	check_error(pid != -1, "fork failed");
	
	if(pid == 0){
		
		check_error(execlp("gcc", "gcc", "-std=c99", argv[1], "-o", argv[2], NULL) != -1, "exec failed");	
		
		exit(EXIT_FAILURE);
	}
	int status = 0;
	
	check_error(waitpid(pid,&status, 0) != -1, "greska");
	
	if (WIFEXITED(status)) {

		if (WEXITSTATUS(status) == EXIT_SUCCESS){
		}
			printf("Prevodjenje uspesno\n");
		else {
			printf("Prevodjenje neuspesno\n");
		}
	}
	
	exit(EXIT_SUCCESS);
}
