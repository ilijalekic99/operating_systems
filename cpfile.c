/* Program kopira fajl sa mesta A na mesto B.
 * Putanje se prosledjuju kao argumenti komandne linije
 *
 * Primer poziva:
 * ./cp_file srcFile destFile
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (1024)

/* makro za obradu gresaka - da ne bih stalno kucao if (...) */
#define check_error(expr, msg) \
	do { \
		if (!(expr)) {\
			fprintf(stderr, "%s\n", msg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)

int main(int argc, char** argv){
	
	check_error(argc == 3, "./cpfile srcPath desPath\n");
	
	int srcFd = open(argv[1], O_RDONLY);
	check_error(srcFd == -1, "open failed");
	
	int destFd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	check_error(destFd == -1, "open failed");
	
	char* buf = malloc(MAX_SIZE);
	check_error(buf != NULL, "malloc failed");
	
	int bytesRead = 0;
	
	while((bytesRead = read(srcFd,buf,MAX_SIZE)) > 0){
		check_error(write(destFd,buf,bytesRead) == bytesRead, "write failed");
	}
	
	check_error(bytesRead != -1, "read failed");
	
	free(buf);
	close(srcFd);
	close(destFd);
	
exit(EXIT_SUCCESS);
return 0;
}
