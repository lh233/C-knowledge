C语言三个点...表示什么意思

1. 可变参数
2. 数组批量赋相同值
3.  一种数组赋值方法


## 1，可变参数
当参数个数可变的时候会使用三个点来表示，比如内核中的printk的定义：


```
static inline int printk(const char *fmt, ...)  
```


## 2.数组批量赋相同值
比如指定从某个下标到另外一个下标初始化为同一个值，比如


```
  1         
  2 #include <stdio.h>
  3 
  4 int main(){
  5     int table[7]={
  6     [3 ... 6]=7,
  7     };
  8     int i = 0;
  9     for(i=0;i<7;i++)
 10     {
 11         printf("table[%d]=%d\n",i,table[i]);
 12     }
 13 }

```
这里表示数组table 下标从3 开始到6的元素赋值为7. 如下：


![image](https://img-blog.csdnimg.cn/20201020182736571.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1NwcmluZ19FdA==,size_16,color_FFFFFF,t_70#pic_center)


## 3. 一种数组赋值方法
先用三点方法初始化数组，再用宏定义来对特定的值进行赋值，linux的系统调用就是使用这种方法来定义的系统调用号。


```
 69 const syscall_fn_t sys_call_table[__NR_syscalls] = {
 70     [0 ... __NR_syscalls - 1] = __arm64_sys_ni_syscall,
 71 #include <asm/unistd.h>
 } // 这个是linux系统代码实例，下面用一个相对简单的例子来理解这种方法

```
主函数，用[0 … 6] 对数组的所有变量赋值为7 。使用include方式包含对特定值的处理


```
  1                                     
  2 #include <stdio.h>
  3 
  4 int main(){
  5     int table[7]={
  6     [0 ... 6]=7,
  7     #include "b.h"
  8     };
  9     int i = 0;
 10     for(i=0;i<7;i++)
 11     {
 12         printf("table[%d]=%d\n",i,table[i]);
 13     }
 14 }

```
特定值处理头文件b.h ,_CALL(3,5) 表示对下标为3的赋值为5。


```
  2 #ifndef _CALL
  3 #define _CALL(x,y)
  4 #endif
  5 
  6 #undef _CALL
  7 #define _CALL(x,y) [x]=y,//这里是重新定义参数的形式
  8 
  9 _CALL(3,5)
 10 _CALL(4,9)

```
运行结果：
![image](https://img-blog.csdnimg.cn/20201020184848865.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1NwcmluZ19FdA==,size_16,color_FFFFFF,t_70#pic_center)