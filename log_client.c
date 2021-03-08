/* Program ilustruje sinhronizaciju pristupa deljenoj memoriji
 * Klijent mapira postojeci blok deljene memorije i cita/pise po njemu.
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)
	
#define MAX_SIZE (1024)

typedef struct {
	sem_t writeLock;
	sem_t readLock;
	char buffer[MAX_SIZE];
}shmData;

void* GetSgmBlock(char* path, unsigned* size);

int main(int argc, char** argv){
	check_error(argc == 2,"...");
	
	unsigned size = 0;
	shmData* data = GetSgmBlock(argv[1],&size);
	
	char buffer[MAX_SIZE];
	
	do{
		check_error(sem_wait(&(data->readLock)) != -1, "...");
		
		strcpy(buffer,data->buffer);
		
		check_error(sem_post(&(data->writeLock)) != -1, "...");
		printf("%s\n",buffer);
	}while(strcmp(buffer,"quit"));
	
	check_error(munmap(data,size) != -1, "...");
	
	exit(0);
}

void* GetSgmBlock(char* path, unsigned* size){
	int memFd = shm_open(path,O_RDWR,0600);
	check_error(memFd != -1,"greska");
	
	struct stat fInfo;
	check_error(fstat(memFd, &fInfo) != -1, "greska");
	*size = fInfo.st_size;
	
	void* addr;
	check_error(MAP_FAILED != (addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0)), "greska");
	
	close(memFd);
	
	return addr;

}

