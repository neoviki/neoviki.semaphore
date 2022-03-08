#include <stdio.h>
#include <unistd.h>
#include "neoviki_semaphore_lock.h"

#define SEMAPHORE_NAME "/tmp/test.txt"
int main()
{
    int i;
    neoviki_semid_t sem_id =  SEM_INIT(SEMAPHORE_NAME);
    for(i=0;i<10;i++){
        SEM_LOCK(sem_id); 
        printf("reader\n");
        sleep(1);
        SEM_UNLOCK(sem_id);
    }
    
    return 0;
}
