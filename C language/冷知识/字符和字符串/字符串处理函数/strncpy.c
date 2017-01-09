
函数名:strncpy
原型：char * strncpy(char *dest, char *src, size_t n); 　
功能：将字符串src中最多n个字符复制到字符数组dest中(它并不像strcpy一样遇到NULL才停止复制，而是等凑够n个字符才开始复制），返回指向dest的指针。
#include <stdio.h>
#include <string.h>
int main(void)
{
char string[10];
char *str1 = "abcdefghi";
strncpy(string, str1,3);
   
printf("%s\n", string);
return 0;
}