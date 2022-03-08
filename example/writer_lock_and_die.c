#include <stdio.h>
#include <unistd.h>
#include "neoviki_semaphore_lock.h"

#define SEMAPHORE_NAME "/tmp/test.txt"

int main()
{
    int i;
    neoviki_semid_t sem_id = SEM_INIT(SEMAPHORE_NAME);
    
    SEM_LOCK(sem_id); 
    printf("writer\n");
    
    return 0;
}
