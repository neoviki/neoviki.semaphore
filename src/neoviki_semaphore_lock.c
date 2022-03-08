/* Inter Process Locks using System V - Semaphore
 *
 *
 *      Author  : Viki (a) Vignesh Natarajan
 *      Contact : neoviki.com
 */

#include "neoviki_semaphore_lock.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/sem.h>

#define DEBUG 1
#define SEM_NUM     0
#define SEM_FLAG    0

key_t get_key(char *sem_name)
{   
    key_t key;
    key = ftok(sem_name , 'N');
    if(key == -1){
        perror("ftok");
        exit(1);
    }
    return key;
}

neoviki_semid_t SEM_INIT(char *unique_name)
{
    if(DEBUG) printf("SHM_INIT()\n");
    int n_semaphores = 1;
    neoviki_semid_t sem_id;

    if(!unique_name) printf("SEM_INIT: error semaphore name\n");

    /*create a semaphore in locked state*/
    sem_id = sem_get(get_key(unique_name), n_semaphores, 0666 | IPC_CREAT);
    if(sem_id == -1){
        perror("sem_get");
        exit(1);
    }
    
    if(DEBUG) printf("SHM_INIT() : success\n");
    return sem_id;
}

void SEM_LOCK(neoviki_semid_t sem_id)
{
    int ret;
    int nsops = 1;
    struct sembuf sb;
    sb.sem_num  =  SEM_NUM;    /* semaphore number */
    sb.sem_op   = -1;    /* semaphore operation */
    sb.sem_flg  =  SEM_FLAG;    /* operation flags */

    if(DEBUG) printf("SHM_LOCK\n");
    
    ret = sem_op(sem_id, &sb, nsops);
    
    if(ret == -1){
        perror("sem_op");
        exit(1);
    }

    if(DEBUG) printf("SHM_LOCK : success\n");
    return;
}

void SEM_UNLOCK(neoviki_semid_t sem_id)
{
    int ret, nsops = 1;
    struct sembuf sb;
    
    if(DEBUG) printf("SHM_UNLOCK\n");
    
    sb.sem_num  =  SEM_NUM;    /* semaphore number */
    sb.sem_op   =  1;    /* semaphore operation */
    sb.sem_flg  =  SEM_FLAG;    /* operation flags */

    ret = sem_op(sem_id, &sb, nsops);
    
    if(ret == -1){
        perror("sem_op");
        exit(1);
    }

    if(DEBUG) printf("SHM_UNLOCK : success\n");
}

/* All Blocked process will be released
 */
void SEM_DESTROY(neoviki_semid_t sem_id)
{
    if(DEBUG) printf("SEM_DESTROY\n");
    int ret;
    int semnum = 0;
    union semun arg;

    /* Immediately remove the semaphore set, awakening all
       processes blocked in semop(2) calls on the set (with an
       error return and errno set to EIDRM).  The effective user
       ID of the calling process must match the creator or owner
       of the semaphore set, or the caller must be privileged.
       The argument semnum is ignored.
     
       Reference: https://man7.org/linux/man-pages/man2/semctl.2.html
     */


    ret = semctl(sem_id, SEM_NUM, IPC_RMID, arg); 

    if(ret == -1){
        perror("semctl");
        exit(1);
    }

    if(DEBUG) printf("SEM_DESTROY: success\n");
}
