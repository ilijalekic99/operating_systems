/* Program ilustruje upotrebu sistemskog poziva lseek 
 * i pozicioniranje fajl ofseta.
 * 
 * Primer poziva:
 * ./file_size.c test.txt
 *
 * BITNO:
 * Posledica pozicioniranja fajl ofseta na kraj je da 
 * cemo saznati kolika je velicina fajla. Ali to nije cilj
 * zadatka!
 *
 * JOS BITNIJE:
 * Ovako se ne ispituje velicina fajla. Nikada!!!
 * Za to se koristi sistemski poziv stat.
 */


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr,"./file_size path\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1],O_RDONLY);
	if(fd == -1){
		fprintf(stderr,"./file_size path\n");
		exit(EXIT_FAILURE);
	}
	
	off_t fsize = lseek(fd,0,SEEK_END);
	
	if(fsize == (off_t) - 1){
		fprintf(stderr,"./file_size path\n");
		exit(EXIT_FAILURE);
	}
	
	printf("File size: %jdB\n",(intmax_t)fsize);
	close(fd);
	
	exit(EXIT_SUCCESS);

return 0;
}
