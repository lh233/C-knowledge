#include<stdio.h>
#include<string.h>
int main(){
    // 也可以改成 char str[] = "http://see.xidian.edu.cn/cpp/u/xitong/";
    char *str = "http://see.xidian.edu.cn/cpp/u/xitong/";
    char *substr = "see";
    char *s = strstr(str, substr);
    printf("%s\n", s);
    return 0;
}

/*
运行结果：
see.xidian.edu.cn/cpp/u/xitong/
*/
