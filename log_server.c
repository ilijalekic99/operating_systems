/* PRogram ilustruje sinhronizaciju pristupa deljenoj memoriji
 * Server kreira blok deljene memorije i inicijalizuje semafore
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <sys/mman.h>
#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define MAX_SIZE (1024)

#define LOCAL_SEM (0)
#define PROC_SEM  (!LOCAL_SEM)


typedef struct {
	sem_t writeLock;
	sem_t readLock;
	char buffer[MAX_SIZE];
} shmData;


void* createShmBlock(char* path, unsigned size);

int main(int argc, char** argv){
	
	check_error(argc == 2, "...");
	
	shmData* data = createShmBlock(argv[1], sizeof(shmData));
	
	check_error(-1!=sem_init(&(data->writeLock),PROC_SEM,1), "...");
	check_error(-1!=sem_init(&(data->readLock),PROC_SEM,0), "...");	
	
	char buffer[MAX_SIZE];

	do {
		
		scanf("%s", buffer);
		check_error(sem_wait(&(data->writeLock))!=-1, "..");
		strcpy(data->buffer,buffer);
		check_error(sem_post(&(data->readLock)) != -1,"..");
	} while(strcmp(buffer, "quit"));	
	
	check_error(munmap(data, sizeof(shmData))!=-1,"..");
	check_error(shm_unlink(argv[1])!=-1, "...");
	
	exit(EXIT_SUCCESS);
}

void* createShmBlock(char* path, unsigned size) {
	
	int memFd = shm_open(path, O_RDWR | O_CREAT, 0600);
	check_error(memFd != -1, "shm_open failed");
	
	check_error(ftruncate(memFd, size) != -1, "ftruncate failed");
	
	void* addr;
	check_error(MAP_FAILED != (addr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, memFd, 0)), "...");
		close(memFd);
		return addr;
}
