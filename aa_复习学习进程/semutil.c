#include"semutil.h"

int C(int count){

    int id;
    if(count > 0)
        id = semget(0x8888, count, IPC_CREAT | IPC_EXCL | 0664);
    else
        id = semget(0x8888, 0, 0);
    ASSERT(semget, id);

    return id;
}

void S(int id, int semnum, int val){

    ASSERT(semctl, semctl(id, semnum, SETVAL, val));
}

void D(int id){

    ASSERT(semctl, semctl(id, 0, IPC_RMID));
}

void P(int id, int semnum){

    struct sembuf op1 = {semnum, -1, 0};
    ASSERT(semop, semop(id, &op1, 1));
}

void V(int id, int semnum){

    struct sembuf op1 = {semnum, 1, 0};
    ASSERT(semop, semop(id, &op1, 1));
}

int G(int id, int semnum){

    return semctl(id, semnum, GETVAL);
}




















