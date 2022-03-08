/* Inter Process Locks using System-V Semaphore
 *
 *
 *      Author  : Viki (a) Vignesh Natarajan
 *      Contact : neoviki.com
 */

#ifndef __NEOVIKI_SEM_LOCK_H__
#define __NEOVIKI_SEM_LOCK_H__
#define neoviki_semid_t int
/*

sem_name: 

    This name should be an unique name. multiple processes uses the same name to access the created semaphore.

    Ex: /tmp/test_app

*/

/*return: sem_id*/
neoviki_semid_t SEM_INIT (char *unique_name);
void SEM_LOCK           (neoviki_semid_t sem_id);
void SEM_UNLOCK         (neoviki_semid_t sem_id);
void SEM_DESTROY        (neoviki_semid_t sem_id);

#endif

