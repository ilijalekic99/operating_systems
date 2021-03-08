/* Program brise sadrzaj fajla uz sakrivanje tragova.
 *
 * Primer poziva:
 * ./truncate test.txt
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <utime.h>

#define check_error(expr,userMsg)\
	do{ \
		if(!(expr)){ \
			fprintf(stderr, "%s\n", userMsg);\
			exit(EXIT_FAILURE); \
		} \
	} while(0)
	
	
int main(int argc, char** argv){
	check_error(argc == 2, "./userInfo userName");
	
	struct stat fInfo;	
	check_error(stat(argv[1],&fInfo) != -1, "stat failed");
	
	FILE *f = fopen(argv[1], "w");
	check_error(f != NULL, "file open failed");
		
	fclose(f);
	
	struct utimbuf vremena;
	vremena.actime = fInfo.st_atime;
	vremena.modtime = fInfo.st_mtime;
	

exit(EXIT_SUCCESS);
}
