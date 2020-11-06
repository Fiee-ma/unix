#include<pthread.h>
#include<stdio.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int ct = 0; // 条件变量

void *thread1(void *arg){

    while(1){
        pthread_mutex_lock(&lock);
        while(ct % 4 != 0)
            pthread_cond_wait(&cond, &lock);
        printf("%c", *(char *)arg);
        ++ct;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond);
    }
}

void *thread2(void *arg){

    while(1){
        pthread_mutex_lock(&lock);
        while(ct % 4 != 1)
            pthread_cond_wait(&cond, &lock);
        printf("%c", *(char *)arg);
        ++ct;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond);
    }
}

void *thread3(void *arg){

    while(1){
        pthread_mutex_lock(&lock);
        while(ct % 4 != 2)
            pthread_cond_wait(&cond, &lock);
        printf("%c", *(char *)arg);
        ++ct;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond);
    }
}

void *thread4(void *arg){

    while(1){
        pthread_mutex_lock(&lock);
        while(ct % 4 != 3)
            pthread_cond_wait(&cond, &lock);
        printf("%c", *(char *)arg);
        printf(" ");
        ++ct;
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond);
    }
}

int main(){

    pthread_t tid1, tid2, tid3, tid4;

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
