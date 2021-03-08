/* Program pokusava da kreira direktorijum na putanji koju korisnik
 * sa pravima pristupa koje bi korisnik zeleo.
 * Putanja i prava pristupa se prosledjuje kao argumenti
 * komandne linije.
 *
 * Primer poziva:
 * ./mkdir dir1 0777
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
	
	if(argc != 3){
		fprintf(stderr,"./2 dirPath privilages");
		exit(EXIT_FAILURE);
	}
	
	long mode = strtol(argv[2],NULL,8);
	
	if(mkdir(argv[1],mode) == -1){
		fprintf(stderr, "mkdir faiiled\n");
		exit(EXIT_FAILURE);
	}

exit(EXIT_SUCCESS);
}
