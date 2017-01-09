//头文件string.h
strcpy

拷贝一个字符串到另一个
程序例:
#include <stdio.h>
#include <string.h>
int main(void)
{
char string[10];
char *str1 = "abcdefghi";
strcpy(string, str1);
   
printf("%s\n", string);
return 0;
}

