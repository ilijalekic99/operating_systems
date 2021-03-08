/* program ilustruje dvosmernu komunikaciju izmedju procesa */
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

#define MAX_SIZE (256)
#define WR_END (1)
#define RD_END (0)

int main(){
	
	int par2cld[2];
	int cld2par[2];
	
	check_error(pipe(par2cld) != -1 ,"greska");
	check_error(pipe(cld2par) != -1 ,"greska");
	
	pid_t pid = fork();
	check_error(pid != -1, "greska");
	
	if(pid > 0){
		close(par2cld[0]);
		close(cld2par[1]);
		
		char* line = NULL;
		size_t lineLen = 0;
		check_error(getline(&line, &lineLen, stdin) != -1, "getline failed");
		check_error(lineLen < 256, "line too long");
		
		check_error(write(par2cld[WR_END], line, lineLen) != -1, "write failed");
		
		char buf[MAX_SIZE];
		int readBytes = 0;
		check_error((readBytes = read(cld2par[RD_END], buf,MAX_SIZE)) != -1, "read failed");
	
	check_error(write(STDOUT_FILENO, buf, readBytes) != -1, "read failed");
	
		free(line);
		close(par2cld[WR_END]);
		close(cld2par[RD_END]);
	}
	
	else { 
		
		close(par2cld[WR_END]);
		close(cld2par[RD_END]);
		
		
		char buf[MAX_SIZE];
		int bytesRead = 0;
		memset(buf, 0, MAX_SIZE);
		strcpy(buf, "Child: ");
		write(STDOUT_FILENO, buf, strlen(buf));
		
		bytesRead = read(par2cld[RD_END], buf, MAX_SIZE);
		check_error(bytesRead != -1, "read failed");
		
		check_error(write(STDOUT_FILENO, buf, bytesRead) != -1, "write failed");
		
		char* s = "SUCCESS\n";
		check_error(write(cld2par[WR_END], s, strlen(s)) != -1, "write failed");
		
		close(par2cld[RD_END]);
		close(cld2par[WR_END]);
		
		exit(EXIT_SUCCESS);
	}
	int status;
	check_error(wait(&status)!=-1, "wait failed");
	
	exit(EXIT_SUCCESS);
}
