/* Program ilustruje neblokirajuci IO na vestacki nacin
 * Cilj zadatka je da proveri da li je neki drugi proces otvorio
 * imenovani pajp. 
 *
 * Podrazumevano ovo je blokirajuca operaciju, koja moze da se zavrsi
 * bez blokiranja upotrebom neblokirajuceg IO, tj. navodjenjem O_NONBLOCK
 * flaga prilikom otvaranja fajlova.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)
	
int hasReadEnd(const char* path);

int hasWriteEnd(const char* path);

int main(int argc, char** argv) {
	check_error(argc == 3, "...");
	
	if(!strcmp(argv[1],"-r");){
		int retVal = hasReadEnd(argv[2]);
		printf("Readend: %s\n",retVal == 1 ? "Yes" : "NO");
	}
	else if(!strcmp(argv[1], "-w")){
		int retVal = hasWriteEnd(argv[2]);
		printf("Write end: %s\n ",retVal == 1 ? "Yes" : "No");
	}
	else{
		check_error(0,"greska");
	}
exit(0);	
}
