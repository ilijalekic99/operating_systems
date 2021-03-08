/* Program otvara fajl u modu koji zeli korisnik.
 * Putanja do fajla i zeljeni mod se prosledjuju kao 
 * argumenti komandne linije.
 *
 * Primer poziva:
 * ./open_file test.txt r+ 
 */
 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

/* funkcija klonira fopen poziv, samo koristi file deskriptore 
 * arg1: putanja do fajla
 * arg2: mod u kome treba otvoriti fajl
 * ret:  fajl deskriptor pridruzen fajlu
 */
 
int my_fopen(const char* path, const char* mode);

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "./1 filePath fmode\n");
		exit(EXIT_FAILURE);
	}
	
	int fd = my_fopen(argv[1],argv[2]);
	
	close(fd);
	exit(EXIT_SUCCESS);
	
return 0;
}

int my_fopen(const char* path, const char* mode){
    static mode_t fmode = 0777;
    
    int flags = 0;
    
    switch(mode[0]){
    	case 'r':
    		flags |= mode[1] == '+' ? O_RDWR : O_RDONLY;
    		break;
    	
    	case 'w':
    		flags |= mode[1] == '+' ? O_RDWR : O_WRONLY;
    		flags |= O_TRUNC;
    		flags |= O_CREAT;
    		break;
    	
    	case 'a':
    		flags |= mode[1] == '+' ? O_RDWR : O_WRONLY;
    		flags |= O_APPEND;
    		flags |= O_CREAT;
    		break;
    	default:
    		fprintf(stderr,"wrong mode\n");
    		exit(EXIT_FAILURE);
    		break;
    }
	
	int fd = open(path,flags,fmode);
	
	if(fd == -1){
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	return fd;
}
