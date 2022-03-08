/* Inter Process Locks using Semaphore
 *
 *
 *      Author  : Viki (a) Vignesh Natarajan
 *      Contact : neoviki.com
 */

#ifndef __NEOVIKI_SEM_LOCK_H__
#define __NEOVIKI_SEM_LOCK_H__
#include <semaphore.h>
/*

sem_name: 

    This name should be an unique name. multiple processes uses the same name to access the created semaphore.

    Ex: /tmp/test_app

*/
typedef struct{
    sem_t *ptr;
    char  *name;
}neoviki_sem_t;

/* Destroy previous named semaphore and create new
 */

neoviki_sem_t *SEM_CREATE (char *unique_name);
neoviki_sem_t *SEM_OPEN   (char *unique_name);
void SEM_LOCK       (neoviki_sem_t *sem);
void SEM_LOCK_UNTIL (neoviki_sem_t *sem, int nsec);
void SEM_UNLOCK     (neoviki_sem_t *sem);
void SEM_CLOSE      (neoviki_sem_t *sem);

#endif

