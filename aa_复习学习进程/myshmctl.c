#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<time.h>
#include<sys/shm.h>

#define ASSERT(res)if((res) < 0){perror(__FUNCTION__); exit(-1);}

void printPerm(struct ipc_perm *perm){

    printf("euid of owner = %d\n", perm->uid);
    printf("egid of owner = %d\n", perm->gid);
    printf("euid of creater = %d\n", perm->cuid);
    printf("egid of create = %d\n", perm->cgid);
    printf("mode = 0%o\n", perm->mode);  //%o表示八进制
}

void printShmid(struct shmid_ds *shmid){

    printPerm(&shmid->shm_perm);
    printf("segment size = %ld\n", shmid->shm_segsz);
    printf("last attach time = %s\n", ctime(&shmid->shm_atime));
    printf("last detach time = %s\n", ctime(&shmid->shm_dtime));
    printf("last change time = %s\n", ctime(&shmid->shm_ctime));
    printf("pid of create = %d\n", shmid->shm_cpid);
    printf("pid of last shmat/shmdt = %d\n", shmid->shm_lpid);
    printf("numer of attach = %ld\n", shmid->shm_nattch);
}

//创建内核对象
void create(){

    int id = shmget(0x8888, 123, IPC_CREAT | IPC_EXCL | 0664);
    printf("create id = %d\n", id);
    ASSERT(id);
}

//IPC_STAT命令使用，获取内核对象的信息
void show(){

    int id = shmget(0x8888, 0, 0);
    ASSERT(id);
    struct shmid_ds shmid;
    shmctl(id, IPC_STAT, &shmid);
    printShmid(&shmid);
}

//IPC_SET命令的使用，用来设置内核对象的信息
void set(){

    int id = shmget(0x8888, 0, 0);
    ASSERT(id);
    struct shmid_ds shmid;
    shmctl(id, IPC_STAT, &shmid);
    shmid.shm_perm.mode = 0600;
    shmctl(id, IPC_SET, &shmid);
    printf("set id = %d\n", id);
}

//使用IPC_RMID命令，删除内核对象
void rm(){

    int id = shmget(0x8888, 0, 0);
    ASSERT(id);
    ASSERT(shmctl(id, IPC_RMID, NULL));
    printf("remove id = %d\n", id);
}

//挂接和卸载
void at_dt(){

    int id = shmget(0x8888, 0, 0);
    ASSERT(id);
    char *buf = shmat(id, NULL, 0);
    printf("shmat %s\n", buf);
    sleep(5);
    ASSERT(shmdt(buf));
    printf("shmdt %s\n", buf);
}

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage: %s <option -c -v -s -d -a>\n", argv[0]);
        return -1;
    }

    if(!strcmp(argv[1], "-a"))
        at_dt();
    if(!strcmp(argv[1], "-v"))
        show();
    if(!strcmp(argv[1], "-s"))
        set();

    if(!strcmp(argv[1], "-d"))
        rm();

    if(!strcmp(argv[1], "-c"))
        create();

    return 0;
}
























