/* Inter Process Locks using Semaphore
 *
 *
 *      Author  : Viki (a) Vignesh Natarajan
 *      Contact : neoviki.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "neoviki_semaphore_lock.h"
#include <errno.h>
#include <time.h>
#define DEBUG 1
#define SEM_MODE 0644
#define SEM_INIT_VALUE 0
 
void __SEM_DESTROY__(char *sem_name);

neoviki_sem_t *SEM_CREATE(char *unique_name)
{
    if(DEBUG) printf("SHM_CREATE()\n");
   
    neoviki_sem_t *sem = (neoviki_sem_t *) calloc(1, sizeof(neoviki_sem_t));
    if(!sem) printf("OOM\n");
    sem->name = unique_name;

    __SEM_DESTROY__(sem->name);
    /*create a semaphore in locked state*/
    sem->ptr = sem_open(sem->name, O_CREAT, SEM_MODE, SEM_INIT_VALUE);
    if(sem->ptr == SEM_FAILED){
        printf("error: sem create\n");
        free(sem);
        assert(0);
    }
    
    SEM_UNLOCK(sem);
    if(DEBUG) printf("SHM_CREATE() : success\n");
    return sem;
}

neoviki_sem_t *SEM_OPEN(char *unique_name)
{
    if(DEBUG) printf("SHM_OPEN()\n");
    
    neoviki_sem_t *sem = (neoviki_sem_t *) calloc(1, sizeof(neoviki_sem_t));
    if(!sem) printf("OOM\n");
    sem->name = unique_name;

    sem->ptr = sem_open(sem->name, 0, SEM_MODE, SEM_INIT_VALUE);
    if(sem->ptr == NULL){
        printf("error: sem open\n");
        free(sem);
        assert(0);
    }
    
    if(DEBUG) printf("SHM_OPEN() : success\n");
    return sem;
}

void SEM_LOCK(neoviki_sem_t *sem)
{
    if(DEBUG) printf("SHM_LOCK\n");
    int ret;
    if(!sem) return; 
    if(!sem->ptr){
        printf("error: SEM_LOCK : sem->ptr = null\n");
        return;
    }

    sem_wait(sem->ptr);
    if(DEBUG) printf("SHM_LOCK : success\n");
    return;
}

void SEM_LOCK_UNTIL(neoviki_sem_t *sem, int nsec)
{
    struct timespec ts;
    int ret;

    if(!sem) return; 
    if(!sem->ptr){
        printf("error: SEM_LOCK_UNTIL : sem->ptr = null\n");
        return;
    }

 
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        printf("error: clock_gettime\n");
        assert(0);
    }
    ts.tv_sec += nsec;

    while ((ret = sem_timedwait(sem->ptr, &ts)) == -1 && errno == EINTR)
        continue;     
}

void SEM_UNLOCK(neoviki_sem_t *sem)
{
    if(DEBUG) printf("SHM_UNLOCK\n");
    if(!sem) return;
    
    if(!sem->ptr){
        printf("error: SEM_UNLOCK :  sem->ptr = null\n");
        return;
    }


    sem_post(sem->ptr);
    if(DEBUG) printf("SHM_UNLOCK : success\n");
}

void SEM_CLOSE(neoviki_sem_t *sem)
{
    if(DEBUG) printf("SHM_CLOSE :\n");
    int ret;
    if(!sem) return;

    if(!sem->ptr){
        return;
    }


    ret = sem_close(sem->ptr);
    sem->ptr = NULL;

    if(errno == EBUSY){
        printf("SEM_CLOSE: error, There are currently processes blocked on the semaphore\n");
        free(sem); 
        return;
    }

    if(errno == EINVAL){
        printf("SEM_CLOSE: error, semaphore descriptor is not valid\n");
        free(sem); 
        return;
    }
    
    free(sem); 
    if(DEBUG) printf("SHM_CLOSE : success\n");
}

/* private method ( add static later, testing )
 */
void __SEM_DESTROY__(char *sem_name)
{
    if(DEBUG) printf("__SEM_DESTROY__\n");
    int ret;
    if(!sem_name) return;
    /* The semaphore is destroyed once all the processes that opened this semaphore closes it. New process cannot open the semmaphore
     */

    /*we need to link with -pthread during compilation, if you use SEM_DESTROY*/
    ret = sem_unlink(sem_name);

    if(errno == EACCES){
        printf("SEM_DESTROY: permission error\n");
        return;
    }

    if(errno == ENAMETOOLONG){
        printf("SEM_DESTROY: error, sem->name greater than NAME_MAX\n");
        return;
    }

    if(errno == ENOENT){
        printf("SEM_DESTROY: error, semaphore does not exist.\n");
        return;
    }
    if(DEBUG) printf("__SEM_DESTROY__: success\n");
}
