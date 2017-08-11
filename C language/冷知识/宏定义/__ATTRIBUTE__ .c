#include <stdio.h>
struct p
{
	int a;
	char b;
	short c;
}__attribute__((aligned(4))) pp;



struct m
{
	char a;
	int b;
	short c;
}__attribute__ ((aligned(4))) mm;


struct o
{
	int a;
	char b;
	short c;
}oo;


struct x
{
	int a;
	char b;
	struct p px;
	short c;
}__attribute__((aligned(8))) xx;

int main(int argc, char * argv[])
{
	printf("pp = %d, mm = %d\n", sizeof(pp), sizeof(mm));
	printf("oo = %d, xx = %d\n", sizeof(oo), sizeof(xx));
	return 0;


}

/*
运行结果：
pp = 8, mm = 12
oo = 8, xx = 24
sizeof(pp):
sizeof(a)+sizeof(b)+sizeof(c)=4+1+1=6<8 所以sizeof(pp)=8


sizeof(mm):
但是 a 后面需要用 3 个字节填充，但是 b 是 4 个字节，所以 a 占用 4 字节， b 占用 4 个字节，而 c 又要占用 4 个字节。所以 sizeof(mm)=12

sizeof(oo):
sizeof(a)+sizeof(b)+sizeof(c)=4+1+2=7
因为默认是以4 字节对齐，所以sizeof(oo)=8


sizeof(xx):
sizeof(a)+ sizeof(b)=4+1=5
sizeof(pp)=8; 即xx 是采用8 字节对齐的，所以要在a ，b 后面添3 个空余字节，然后才能存储px ，
4+1+（3)+8+1=17







*/
