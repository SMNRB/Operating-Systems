#include "osheader.h"

int main(int argc, char** argv) {
	
	key_t key = 12345;
	size_t size = 128;
	int smID;
	int* adress;
		
	// Create shared memory
	if((smID = shmget(key, size,  IPC_CREAT | IPC_EXCL)) == -1) {
		perror("shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	// Attach shared memory
	if((adress = shmat(smID, NULL, 0)) == -1) {
		perror("shmat failed\n");
		exit(EXIT_FAILURE);
	}
	/*
	memcpy(&adress, 0 , sizeof(int));
	
	if((FILE* resultFifo = mkfifo("RESULT_FIFO", O_CREAT | 0666 )) == -1) {
		perror("mkfifo failed\n");
		exit(EXIT_FAILURE);
	}
	*/
	// Detach shared memory
	if(shmdt(adress) == -1) {
		perror("shmdt\n");
		exit(EXIT_FAILURE);
	}
	
	// Delete shared memory	
	if(shmctl(smID, IPC_RMID, NULL ) == -1) {
		perror("shmctl failed\n");
		exit(EXIT_FAILURE);
	}
	
	return EXIT_SUCCESS;
}
