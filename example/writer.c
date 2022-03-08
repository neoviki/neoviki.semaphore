#include <stdio.h>
#include <unistd.h>
#include "neoviki_semaphore_lock.h"

#define SEMAPHORE_NAME "/tmp/test.txt"

int main()
{
    int i;
    neoviki_sem_t *sem = SEM_CREATE(SEMAPHORE_NAME);
    
    for(i=0;i<10;i++){
        SEM_LOCK(sem); 
        printf("writer\n");
        sleep(5);
        SEM_UNLOCK(sem);
    }
    
    SEM_CLOSE(sem);
    return 0;
}
