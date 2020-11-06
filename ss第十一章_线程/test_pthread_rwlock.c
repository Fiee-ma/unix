#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

pthread_rwlock_t link;

void * t_hand()
{


        int i = 0;
        while(1)
        {
                printf("++++++++++++++++++++++++++\n");
                pthread_rwlock_rdlock(&link);
                printf("---------------------------\n");
                pthread_rwlock_unlock(&link);
                printf("=========================== i = %d \n",i++);
                sleep(1);
                if( i == 7)
                    break;

        }

        pthread_rwlock_unlock(&link);

}




int main(int argc, char ** argv)
{
    int ret = 0;
    printf(" EBUSY = %d, EINVAL = %d, EAGAIN = %d, EDEADLK = %d\n", EBUSY, EINVAL, EAGAIN, EDEADLK);

    pthread_rwlock_init(&link,NULL);


    pthread_t pid ;

    pthread_rwlock_rdlock(&link);

    pthread_create(&pid,NULL,t_hand,NULL);

    sleep(1);

    printf("before wrlock\n");
    pthread_rwlock_wrlock(&link);
    printf("after wrlock\n");

    sleep(10);

}
