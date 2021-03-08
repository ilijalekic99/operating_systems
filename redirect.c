/* Program ilustruje pokretanje ls komande i brojanje linije iz parent-a */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

int main(int argc, char** argv){
	int cld2par[2];
	check_error(pipe(cld2par) != -1, "...");
	
	pid_t pid = fork();
	check_error(pid != -1,"greska");
	
	if(pid > 0){
		close(cld2par[1]);
		
		char* line = NULL;
		size_t lineLen = 0;
		int lineCnt = 0;
		
		FILE *f = fdopen(cld2par[0],"r");
		
		while(getline(&line,&lineLen,f) != -1){
			lineCnt++;
			printf("%d : %s", lineCnt, line);
		}
	}
	else{
		close(cld2par[0]);
		//check_error(dup2(cld2par[1],STDOUT_FILENO) != -1, "...");
		
		check_error(execl("ls","ls","-l",NULL) != 1, "...");
		
		exit(0);
	}
	int status = 0;
	check_error(wait(&status) != -1, "...");
	
	if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)){
		printf("OK\n");
	}
	else printf("Not ok\n");
exit(0);
}
