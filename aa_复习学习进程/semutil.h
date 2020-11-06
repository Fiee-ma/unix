#ifndef __SEMUTIL_H__
#define __SEMUTIL_H__

#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>

#define ASSERT(err, res)if((res) < 0){perror(#err); exit(-1);}

/*
 * Creat
 * 创建和获取信号量ipc内核对象id
 * count > 0表示创建，count = 0表示获取
 */
int C(int count);

/*
 * Set
 * 初始化semnum个信号量的值为val
 */
void S(int id, int semnum, int val);

/*
 * Get
 * 获取第semnum个信号量的值为val
 */

int G(int id, int semnum);

/*
 * Delete
 * 删除信号量内核对象
 */
void D(int id);

/*
 * 请求第semnum个信号量，将其值-1
 */
void P(int id, int semnum);

/*
 * 归还第semnum个信号量，并将其值+1
 */
void V(int id, int semnum);

#endif //__SEMUTIL_H__
















