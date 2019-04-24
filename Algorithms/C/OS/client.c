
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/types.h>
#include <semaphore.h>

void main()
{
    //client writes the shared memory
    //creating the semaphore
    sem_t *x2;
    sem_t *x1;
    x1 = sem_open("sSem4", O_CREAT, 0666, 0);
    x2 = sem_open("cSem4", O_CREAT, 0666, 1);
    //reading shared memory
    int i = 0;
    key_t key = ftok("sharedmem", 65);
    //shared memory id
    int shmid = shmget(key, 2 * sizeof(char), IPC_CREAT | 0666);
    //attach to the segment
    char *str = (char *)shmat(shmid, NULL, 0);
    while (i < 5)
    {
        sem_wait(x2);
        //unique key generate

        //sever data read
        printf("Data input for memory");
        *str = (char)(i) + 65;
        printf("Data written in memory");
        //detach from shared memory
        i++;
        sem_post(x1);
    }
    sem_unlink("sSem4");
    sem_unlink("cSem4");
    shmdt(str);
    //destroy the shared memory if null
    //sem_destroy(&x2);
}