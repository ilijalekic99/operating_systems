#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#define check_error(expr,userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define MAX_SIZE (1024)

int main(int argc, char** argv) {
	
	check_error(argc == 3, "...");
	
	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) != -1, "stat");
	
	int fdSrc = open(argv[1], O_RDONLY);
	check_error(fdSrc != -1, "...");
	int fdDest = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
	check_error(fdDest != -1, "...");
	
	int readBytes = 0;
	char buffer[MAX_SIZE];
	while ((readBytes = read(fdSrc, buffer, MAX_SIZE)) > 0) {
			
		check_error(write(fdDest, buffer, readBytes) != -1, "...");
	}
	
	check_error(readBytes != -1, "....");
	
	close(fdSrc);
	close(fdDest);
	
	check_error(unlink(argv[1]) != -1, "....");
	
	check_error(chmod(argv[2], fInfo.st_mode) != -1, "...");
	
	exit(EXIT_SUCCESS);
}
