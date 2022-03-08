#include <stdio.h>
#include <unistd.h>
#include "neoviki_semaphore_lock.h"

#define SEMAPHORE_NAME "/tmp/test.txt"
int main()
{
    __SEM_DESTROY__(SEMAPHORE_NAME);
    return 0;
}
