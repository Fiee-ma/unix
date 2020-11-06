#include<time.h>
#include<stdio.h>

int main(){

    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t t = time(NULL); //获取当前时间
    printf("time_t = %d\n", t);

    struct tm *tt = gmtime(&t); //转换成格林尼治时间
    printf("gmtime:\n");
    printf("%d-%d-%d", (tt->tm_year + 1900), (tt->tm_mon + 1), tt->tm_mday);
    printf("%s %d:%d:%d\n", wday[tt->tm_wday], tt->tm_hour, tt->tm_min, tt->tm_sec);

    tt = localtime(&t); //转换成当地时间
    printf("localtime:\n");
    printf("%d-%d-%d", (tt->tm_year + 1900), (tt->tm_mon + 1), tt->tm_mday);
    printf("%s %d:%d:%d\n", wday[tt->tm_wday], tt->tm_hour, tt->tm_min, tt->tm_sec);

    time_t ttt = mktime(tt); //将当地时间转换回time_t类型
    printf("mktime:\n");
    printf("time_t = %d", ttt);

    return 0;
}
