// Writes in the memory
#include <sys/ipc.h> // For inter-process communication
#include <sys/shm.h> // For shared memory operations
#include <stdio.h>

int main()
{
    // Generate a unique key for shared memory
    key_t key = ftok("shmfile", 65);

    // Create a shared memory segment with read/write permissions
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // returns shmid
                                                     // tells OS to create a new
                                                     // segment if not already present
    // Attach the shared memory segment to the process's address space
    char *str = (char *)shmat(shmid, (void *)0, 0);

    printf("Write Data: ");
    fgets(str, 1024, stdin);

    printf("Data written in memory: %s\n", str);

    // detach from shared memory
    shmdt(str);

    return 0;
}