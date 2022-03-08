#include <stdio.h>
typedef struct{
    char *name;
    char *ptr;
}neoviki_sem_t;
int main()
{
    neoviki_sem_t sem;
    sem.name = "test";
    printf("%s", sem.name);
}
