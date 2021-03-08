/* Program nadovezuje sadrzaj fajla na standardni izlaz 
 *
 * Primer poziva:
 * ./cat_file test.txt
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (1024)

int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr,"./catfile path");
		exit(EXIT_FAILURE);
	}
	
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		fprintf(stderr,"./catfile path");
		exit(EXIT_FAILURE);
	}
	
	char* buf = malloc(MAX_SIZE);
	if(buf == NULL)
		exit(EXIT_FAILURE);
		
	int bytesRead = 0;
	
	while((bytesRead = read(fd, buf, MAX_SIZE)) > 0){
		if(write(STDOUT_FILENO, buf, bytesRead) != bytesRead){
			fprintf(stderr, "write failed\n");
			exit(EXIT_FAILURE);
		}
	}
	if(bytesRead == -1){
		fprintf(stderr, "read failed\n");
		exit(EXIT_FAILURE);
	}
	
	free(buf);
	close(fd);
	exit(EXIT_SUCCESS);
}
