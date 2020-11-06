#include<unistd.h>
#include<stdio.h>

int main(){

    int b;
    short int a;
    long int c;
    long long int d;
    printf("short int = %d", sizeof(a));
    printf("int = %d", sizeof(b));
    printf("long int = %d", sizeof(c));
    printf("long long int = %d", sizeof(d));

    return 0;
}
