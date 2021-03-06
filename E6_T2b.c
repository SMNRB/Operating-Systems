#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>

union senum                         // Declaration of union because otherwise compile Error
{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int main(void)
{
    int pid[99];
    int shmId;
    key_t key = 1000;
    size_t size = sizeof(int);
    
    shmId = shmget(key, size, IPC_CREAT | 0666);            // Gets a semaphore set. The value returned is its id, for use with other calls.
    if(shmId == -1)
    {
        perror("shmget failed");
        exit(1);
    }
    
    int semId;
    semId = semget(key, sizeof(int*), IPC_CREAT | 0666);
    if(semId == -1)
    {
        perror("semget failed");
        exit(1);
    }
    
    union senum arg;
    arg.val = 1;                                            // Set union member val = 1
    if(semctl(semId, 0, SETVAL, arg) == -1)
    {
        perror("semctl failed");
        exit(1);
    }
    
    struct sembuf sb = {0, -1, 0};                          // Defines an operation to be performed by the semop() call
    
    for(int i = 0; i < 100; i++)
    {
        pid[i] = fork();
    
        if(pid[i] < 0)
        {
            printf("fork() failed\n");
            exit(1);
        }    
        else if(pid[i] == 0)
        {
            int* data = shmat(shmId, (void*)0,0);        
        
            if(semop(semId,&sb,1) == -1)                    // Performs a semaphore operation (i.e.   incrementing,  decrementing,  etc.)   on the selected members of a
semaphore set
            {
                perror("semop failed");
                exit(1);
            }
        
            for(int useless = 0; useless < 100; useless++)
            {
                *data = *data + 1;
            }
                    
            sb.sem_op = 1;
            
            if(semop(semId, &sb, 1) == -1)
            {
                perror("semop failed");
                exit(1);
            }
        
            exit(0);
        }

        wait(NULL);

    }
        int* data = shmat(shmId, (void*)0,0);
    
    FILE* fifo = fopen("RESULT_FIFO", "w");
    
    if(fifo == NULL)
    {
        perror("fopen failed");
        exit(1);
    }
            
    fprintf(fifo, "%d", *data);
            
    printf("Data in shared memory: %d\n", *data);
            
    if(shmdt(data) == -1)                
    {
        perror("shmdt(data) failed");
        exit(1);
    }
    
    if(fclose(fifo) == -1)
    {
        perror("fclose failed");
        exit(1);
    }

    return EXIT_SUCCESS;
}
