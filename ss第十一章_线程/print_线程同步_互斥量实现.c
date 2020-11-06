#include<stdio.h>
#include<pthread.h>

int ct = 1; //全局计数器
pthread_mutex_t lock;

void * thread1(void *arg){

    while(1){
        pthread_mutex_trylock(&lock);
        while(ct == 1){
            printf("%c", *(char *)arg);
            ++ct;
        }
        pthread_mutex_unlock(&lock);
    }
}

void * thread2(void *arg){

    while(1){
        pthread_mutex_trylock(&lock);
        while(ct == 2){
            printf("%c", *(char *)arg);
            ++ct;
        }
        pthread_mutex_unlock(&lock);
    }
}

void * thread3(void *arg){

    while(1){
        pthread_mutex_trylock(&lock);
        while(ct == 3){
            printf("%c", *(char *)arg);
            ++ct;
        }
        pthread_mutex_unlock(&lock);
    }
}

void * thread4(void *arg){

    while(1){
        pthread_mutex_trylock(&lock);
        while(ct == 4){
            printf("%c\t", *(char *)arg);
            ct = 1;
        }
        pthread_mutex_unlock(&lock);
    }
}

int main(){

    pthread_t tid1, tid2, tid3, tid4;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&tid1, NULL, thread1, "A");
    pthread_create(&tid2, NULL, thread2, "B");
    pthread_create(&tid3, NULL, thread3, "C");
    pthread_create(&tid4, NULL, thread4, "D");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    return 0;
}
