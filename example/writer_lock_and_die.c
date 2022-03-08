#include <stdio.h>
#include <unistd.h>
#include "neoviki_semaphore_lock.h"

#define SEMAPHORE_NAME "/tmp/test.txt"

int main()
{
    int i;
    neoviki_sem_t *sem = SEM_CREATE(SEMAPHORE_NAME);
    
    SEM_LOCK(sem); 
    printf("writer\n");
    
    return 0;
}
