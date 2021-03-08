/* Program ilustruje obradu signala */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)\

int shouldTerminate = 0;

void SigIntHandler(int signum){

	printf("uhvacen");
}

void SigTermHandler(int signum){
	printf("uhvacen");
	shouldTerminate = 1;
}


int main(int argc, char** argv){
	printf("PID: %d\n",(int)getpid());
	
		check_error(signal(SIGINT,SigIntHandler)!= SIG_ERR, "signal failed");
		check_error(signal(SIGTERM,SigTermHandler)!=SIG_ERR, "signal failed");
	do{
		
		printf("gotvo");
		pause();
		
	}while(!shouldTerminate);
	
	
	exit(0);
}
