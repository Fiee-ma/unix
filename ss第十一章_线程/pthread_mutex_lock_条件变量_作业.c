#include<stdio.h>
#include<pthread.h>

int finished = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * do_homework(void *arg){

    //doing homework
    sleep(5);
    pthread_mutex_lock(&lock);
    finished = 1;
    pthread_mutex_unlock(&lock);
    //pthread_cond_signal(&cond);
    pthread_cond_broadcast(&cond);
}

void * check_homework(void *arg){

    //打电话
    sleep(1);
    //电话接通
    pthread_mutex_lock(&lock);
    printf("老师：作业写完了吗？\n");
    while(finished == 0){
        printf("学生：没写完呐！\n");
        printf("老师：好，你接着写吧！\n");
        printf("----------------------\n");
        pthread_cond_wait(&cond, &lock);     //当线程被唤醒之后，对lock进行加锁，但如果lock已经被锁住，那么线程将被阻塞，知道互斥量被解锁后才能继续进行
        printf("老师：作业写完了吗？\n");
    }
    printf("学生：写完了！\n");
    printf("老师开始检查－－\n");
    sleep(7);                              //所以在第一个线程执行完之后，第二个线程要等７秒钟后才能执行
    pthread_mutex_unlock(&lock);
}

int main(){

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, do_homework, NULL);
    pthread_create(&tid2, NULL, check_homework, NULL);
    pthread_create(&tid3, NULL, check_homework, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    return 0;
}

