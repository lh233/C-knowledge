## __attribute 语法的来源

GNU C 的一大特色就是__attribute__ 机制。attribute 可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。

其位置约束为： 放于声明的尾部“;” 之前

attribute 书写特征为: attribute 前后都有两个下划线，并切后面会紧跟一对原括弧，括弧里面是相应的\__attribute__ 参数。



attribute 语法格式为: attribute ((attribute-list))



-   当\__attribute__ 用于修饰对象时，它就如同C 语言语法体系结构的类型限定符，跟const , volatile , restrict 等属一类。
-   当\__attribute__ 用于修饰函数时，它就相当于一个函数说明符，跟inline，Noreturn 属同一类。
-   当\__attribute__ 用于修饰一个结构体，联合体或者枚举类型，该限定符只能放在类型标识符之前。

## __attribute 所支持的类型

当我们需要识别当前编译器能否支持GNU 语法拓展，我们可以使用 __GNU __ 宏作为区分

| 函数属性(Function Attribute) | 类型属性(Type Attributes) | 变量属性(Variable Attribute)  |
| ---------------------------- | ------------------------- | ----------------------------- |
| noreturn                     | aligned                   | alias                         |
| noinline                     | packed                    | at(address)                   |
| always_inline                | bitband                   | aligned                       |
| flatten                      |                           | deprecated                    |
| pure                         |                           | noinline                      |
| const                        |                           | packed                        |
| constructor                  |                           | weak                          |
| destructor                   |                           | weakref(“target”)             |
| sentinel                     |                           | section(“name”)               |
| format                       |                           | unused                        |
| format_arg                   |                           | used                          |
| section                      |                           | visibility(“visibility_type”) |
| used                         |                           | zero_init                     |
| unused                       |                           |                               |
| deprecated                   |                           |                               |
| weak                         |                           |                               |
| malloc                       |                           |                               |
| alias                        |                           |                               |
| warn_unused_result           |                           |                               |
| nonnull                      |                           |                               |
| nothrow (不抛出C++ 异常)     |                           |                               |
| aligned                      |                           |                               |





## 常用函数属性

### \__attribute__((noreturn))

表示没有返回值

-   这个属性告诉编译器函数不会返回，这可以用来抑制关于未达到代码路径的错误。 C库函数abort（）和exit（）都使用此属性声明：

使用例子：

一般情况：

```
cat test1.c
extern void exitnow();

int foo(int n)
{
        if ( n > 0 )
	{
                exitnow();
		/* control never reaches this point */
	}
        else
                return 0;
}

$ cc -c -Wall test1.c
test1.c: In function `foo':
test1.c:9: warning: this function may return with or without a value
```

但是我们使用上面的\__attribute__((noreturn))的话，就不会有warning产生：

```
$ cat test2.c
extern void exitnow() __attribute__((noreturn));

int foo(int n)
{
        if ( n > 0 )
                exitnow();
        else
                return 0;
}

$ cc -c -Wall test2.c
no warnings!
```



### \__attribute__((always_inline))

-   对于声明为内联的函数，会强制优化。所有加了attribute((always_inline))的函数再被调用时不会被编译成函数调用而是直接扩展到调用函数体内。

举个栗子:

```
__attribute__((always_inline)) void a(){
    print("a"); 
}

void b()
{
  a();
}
```

编译以后就是:

```
void b()
{
      print("a"); 
｝
```





### \__attribute__((noinline))

-   与上面的相反，声明为非内联函数



### \__attribute__((flatten))

-   用此修饰的函数，在函数中调用的每一个函数都将尽可能地做内联处理。而用flatten 属性修饰的函数，是否内联处理，就要根据编译器当前的编译选项以及当前上下文来定。



### \__attribute__((pure))
用pure属性修饰的函数用来说明该函数除了返回值之外没有其他任何 效果，并且该函数所返回的值仅仅依赖于函数的形参以及/或全局对象。用 pure属性所修饰的函数可以用来辅助编译器做消除公共子表达式以及帮助 做循环优化，使用这种函数就好比使用算术操作符一般。

 

### \__attribute__((constructor))

确保此函数在 在main函数被调用之前调用；

constructor和destructor会在ELF文件中添加两个段-.ctors和.dtors。当动态库或程序在加载时，会检查是否存在这两个段，如果存在执行对应的代码。

例子：

```
int main(int argc, char * argv[]) {
    @autoreleasepool {
        printf("main function");
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
__attribute__((constructor)) static void beforeFunction()
{
    printf("beforeFunction\n");
}
```

然后运行,发现打印如下:

```
beforeFunction
main function
```

***带有优先级的参数***

按照文档中所说,我们还可以给属性设置优先级.这些函数并不非要写到main.m文件中,无论写到哪里,结果都是一样的.但是,为了更显式的让阅读者看到这些定义,至少,还是在main.m文件中留个声明.

声明和实现分离的写法如下:

```
//声明
__attribute__((constructor(101))) void before1(); // 里面的数字越小优先级越高，1 ~ 100 为系统保留

//实现
void before1()
{
    printf("before1\n");
}
```

下面我仅仅用作测试,就不分开写了:

```
static  __attribute__((constructor(101))) void before1()
{
    
    printf("before1\n");
}
static  __attribute__((constructor(102))) void before2()
{
    
    printf("before2\n");
}
static  __attribute__((constructor(102))) void before3()
{
    
    printf("before3\n");
}
```



###  \__attribute__((destructor))

确保此函数在 在main函数被调用之后调



### \__attribute__((const))
用const属性修饰的函数与用pure属性修饰的十分类似，不过const属性比pure更严格，它要求函数不能读全局对象。此外，用const属性修饰的函数的参数不能是一个指针类型，而且在用const属性修饰的函数内往往不能调用一个非const属性的函数。

也就是说调用其他文件的外部函数才能成立；



### \__attribute__((sentinel))
提醒程序员“此可变参数函数需要一个NULL作为最后一个参数。

\__attribute__((sentinel))的作用是提醒程序员：“此可变参数函数需要一个NULL作为最后一个参数。”，而这个NULL参数一般被叫做“哨兵参数”。

例子：

```
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

void foo(char *first, ...)
{
    char *p = (char *)malloc(100), *q = first;
    va_list args;

    va_start(args, first);
    while(q)
    {
        strcat(p, q);
        q = va_arg(args, char *);
    }
    va_end(args);
    printf("%s\n", p);

    free(p);

    return ;
}

int main(void)
{
    foo("Hello", "World");

    return 0;
}
```

使用

```
gcc main.c -Wall
```

编译没有任何警告。但是很显然，调用foo()时最后一个参数应该是个NULL以表明“可变参数就这么多”。
程序的运行结果：

```
HelloWorldm1�i�
```

显然是错误的。
另：这段程序在某些时候可能运行正常，那是因为在当时的情况下内存中存放”World”字符串的后面正好是个0（也就是NULL）。
将调用foo()的地方改为

```
foo("Hello", "World", NULL);
```

才是正确的写法。

但是为什么这种问题编译器不发出警告？那是因为你没有让编译器发出这类问题的警告，因为不是所有可变参数函数都需要哨兵参数，比如printf()。

```
/* 第一个参数中规定了有两个待打印项，所以打印时会取"string"和1，
 * 多写的"another_string"会被忽略。
 * printf()在被调用时明确知道此次调用需要多少个参数，所以也就无需哨兵参数的帮忙。
 */
printf("%s %d\n", "string", 1，"another_string");
```

所以\__attribute__((sentinel))的功能就在于此。我们把上面的程序改一下，加一句foo()的声明：

```
void foo(char *first, ...) __attribute__((sentinel));
```

这样你再不写哨兵参数，在编译时编译器就会发出警告了：

```
main.c: In function ‘main’:
main.c:28:5: warning: missing sentinel in function call [-Wformat=]
foo(“Hello”, “World”);
^
```





### \__attribute__((format))
format属性可以给被声明的函数加上类似printf或者scanf的特征，它可以使编译器检查函数声明和函数实际调用参数之间的格式化字符串是否匹配。format属性告诉编译器，按照printf, scanf等标准C函数参数格式规则对该函数的参数进行检查。这在我们自己封装调试信息的接口时非常的有用。

format的语法格式为：

```
format (archetype, string-index, first-to-check)
```

例子：

```
#include <stdio.h>
#include <stdarg.h>
 
#if 1
#define CHECK_FMT(a, b)	__attribute__((format(printf, a, b)))
#else
#define CHECK_FMT(a, b)
#endif
 
void TRACE(const char *fmt, ...) CHECK_FMT(1, 2);
 
void TRACE(const char *fmt, ...)
{
	va_list ap;
 
	va_start(ap, fmt);
 
	(void)printf(fmt, ap);
 
	va_end(ap);
}
 
int main(void)
{
	TRACE("iValue = %d\n", 6);
	TRACE("iValue = %d\n", "test");
 
	return 0;
}
```

注意：需要打开警告信息即（-Wall）。
编译结果如下所示：

```
main.cpp: In function ‘int main()’:
main.cpp:26:31: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘const char*’ [-Wformat=]
  TRACE("iValue = %d\n", "test");
```

如果不使用\__attribute__ format则不会有警告。



### \__attribute__((section(“name”))) 

于是本文的大体意思就清晰了，\__attribute__((section("section_name")))，其作用是将作用的函数或数据放入指定名为"section_name"对应的段中。

MDK给出的帮助文档如下，他将\__attribute__的用法归类到编译器特性里，以变量和函数的两种用法做区分。

1.编译时为变量指定段

```
__attribute__((section("name")))
RealView Compilation Tools for µVision Compiler Reference Guide Version 4.0 
 
Home > Compiler-specific Features > Variable attributes > __attribute__((section("name"))) 
 
4.5.6. __attribute__((section("name")))
Normally, the ARM compiler places the objects it generates in sections like data and bss. However, you might require additional data sections or you might want a variable to appear in a special section, for example, to map to special hardware. The section attribute specifies that a variable must be placed in a particular data section. If you use the section attribute, read-only variables are placed in RO data sections, read-write variables are placed in RW data sections unless you use the zero_init attribute. In this case, the variable is placed in a ZI section.
 
Note
This variable attribute is a GNU compiler extension supported by the ARM compiler.
 
Example
/* in RO section */
const int descriptor[3] __attribute__ ((section ("descr"))) = { 1,2,3 };
/* in RW section */
long long rw[10] __attribute__ ((section ("RW")));
/* in ZI section *
long long altstack[10] __attribute__ ((section ("STACK"), zero_init));/
```



2.编译时为函数指定段

```
__attribute__((section("name")))
RealView Compilation Tools for µVision Compiler Reference Guide Version 4.0 
 
Home > Compiler-specific Features > Function attributes > __attribute__((section("name"))) 
 
4.3.13. __attribute__((section("name")))
The section function attribute enables you to place code in different sections of the image.
 
Note
This function attribute is a GNU compiler extension that is supported by the ARM compiler.
 
Example
In the following example, Function_Attributes_section_0 is placed into the RO section new_section rather than .text.
 
void Function_Attributes_section_0 (void)
    __attribute__ ((section ("new_section")));
void Function_Attributes_section_0 (void)
{
    static int aStatic =0;
    aStatic++;
}
In the following example, section function attribute overrides the #pragma arm section setting.
 
#pragma arm section code="foo"
  int f2()
  {
      return 1;
  }                                  // into the 'foo' area
  __attribute__ ((section ("bar"))) int f3()
  {
      return 1;
  }                                  // into the 'bar' area
  int f4()
  {
      return 1;
  }                                  // into the 'foo' area
#pragma arm section
```





### \__attribute__((aligned))

该属性设定一个指定大小的对齐格式（以字节 为单位），例如：

```
struct S {
short b[3];
} __attribute__ ((aligned (8)));

typedef int int32_t __attribute__ ((aligned (8)));
```

该声明将强制编译器确保（尽它所能）变量类 型为struct S 或者int32_t 的变量在分配空间时采用8 字节对齐方式。
如上所述，你可以手动指定对齐的格式，同 样，你也可以使用默认的对齐方式。如果aligned 后面不紧跟一个指定的数字值，那么编译器将依据你的目标机器情况使用最大最有益的对齐方式。例如：

```
struct S {
        short b[3];
} __attribute__ ((aligned));
```



### \__attribute__((used))

used的作用是告诉编译器，我声明的这个符号是需要保留的。被used修饰以后，意味着即使函数没有被引用，在Release下也不会被优化。如果不加这个修饰，那么Release环境链接器会去掉没有被引用的段。具体的描述可以看gun的官方文档。

1、通知编译器在目标文件中保留一个静态函数，即使它没有被引用。

2、标记为attribute__((used))的函数被标记在目标文件中，以避免链接器删除未使用的节。

3、静态变量也可以标记为used，方法是使用\__attribute__((used))。

4、例程

```
static int lose_this(int);
static int keep_this(int) __attribute__((used)); // retained in object file
static int keep_this_too(int) __attribute__((used)); // retained in object file
```



### \__attribute__((unused))

\__attribute__((unused))表示可能没有使用，告诉编译器在编译此类型函数或变量时不需报警告。

![](https://img-blog.csdnimg.cn/20191121185113820.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3lhbmxhaWZhbg==,size_16,color_FFFFFF,t_70)



### \__attribute__((weak))

 我们不确定外部模块是否提供一个函数func，但是我们不得不用这个函数。



####  一、问题声明

```
extern int func(void);   //声明函数，告诉编译器不要管
...................
 
int a = func();  //使用函数
 
...................
```

这会导致2个结果：

1：外部存在这个函数func，并且EXPORT_SYMBOL(func)，那么在我自己的模块使用这个函数func，正确。

2：外部其实不存在这个函数，那么我们使用func，程序直接崩溃。



#### 二、如何解决

```
所以这个时候，__attribute__((weak)) 派上了用场。

在自己的模块中定义：

int  __attribute__((weak))  func(......)
{
return 0;
}
```

将本模块的func转成弱符号类型，如果遇到强符号类型（即外部模块定义了func），那么我们在本模块执行的func将会是外部模块定义的func。类似于c++中的重载

如果外部模块没有定义，那么，将会调用这个弱符号，也就是在本地定义的func，直接返回了一个1（返回值视具体情况而定）

相当于增加了一个默认函数。

原理：

注:    连接器发现同时存在弱符号和强符号，有限选择强符号，如果发现不存在强符号，只存在弱符号，则选择弱符号。如果都不存在：静态链接，恭喜，编译时报错，动态链接：对不起，系统无法启动。 
weak属性只会在静态库(.o .a )中生效，动态库(.so)中不会生效。
举个例子：

```
strong.c  //生成libstrong.so
 
#include <stdio.h>
void real_func()
{
    printf("int real func\n");
}
 
 
weak.c //生成libweak.so
 
#include <stdio.h>
void real_func() __attribute__((weak));
void real_func()
{
    printf("fake func\n");
}
 
main.c //
 
#include <stdio.h>
extern void real_func();
void main()
{
        real_func();
}
```

如果 

gcc main.c -lstrong -lweak

那么输出结果"real func"。

如果 

gcc main.c -lweak -lstrong

那么输出结果为"fake func"。

可见，对于动态库，weak属性毫无作用，且main中调用哪个real_func()，取决于顺序。

如果将strong.c 和 weak.c编译成.a或者.o

gcc main.c strong.o weak.o

或者

gcc main.c weak.o strong.o

那么输出结果都是"real func"。

所以，如果在so中使用weak属性，那么任何不符合预期的情况，都是可能出现的。



### \__attribute__((malloc))

attribute((malloc)) 是由如此标记的函数返回的块不得包含任何指向其他对象的指针.目的是帮助编译器估计哪些指针可能指向同一个对象：该属性告诉GCC它不必担心你的函数返回的对象可能包含指向它正在跟踪的其他东西的指针.



### \__attribute__((deprecated))

在开发一些库的时候，API的接口可能会过时，为了提醒开发者这个函数已经过时。可以在函数声明时加上attribute((deprecated))属性，如此，只要函数被使用，在编译是都会产生警告，警告信息中包含过时接口的名称及代码中的引用位置。

attribute可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。
attribute语法格式为：attribute ((attribute))
注意： 使用attribute的时候，只能函数的声明处使用attribute，

```
#include <stdio.h>
#include <stdlib.h>

#ifdef __GNUC__
#    define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if GCC_VERSION_AT_LEAST(3,1)
#    define attribute_deprecated __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#else
#    define attribute_deprecated
#endif


/* Variable Attribute */
attribute_deprecated int  variable_old = 0;

/* Function Attribute */
attribute_deprecated void function_old(void);

void function_old(void)
{
    printf("old function.\n");
    return;
}

int main(void)
{
    variable_old++;

    function_old();

    return EXIT_SUCCESS;
}
```

在编译时会出现类似警告：

```
# gcc attribute_deprecated.c -o test
attribute_deprecated.c: In function ‘main’:
attribute_deprecated.c:33: warning: ‘variable_old’ is deprecated (declared at attribute_deprecated.c:20)
attribute_deprecated.c:35: warning: ‘function_old’ is deprecated (declared at attribute_deprecated.c:25)
```



### \__attribute__((alias(source_name))

source_name 原函数或者属性名称,(需要主要别名的参数，返回值定义，必须和原来的函数相匹配)

例子：

-   函数别名定义例子

```
void oldFunc(void)
{
    printf("%s\n", __FUNCTION__);
}
void newFunc(void) __attribute__((alias("oldFunc")));
 
int main(int argc, char *argv[])
{
    newFunc(); // calls foo
}
/** 程序输出结果
 oldFunc
*/
```

-   变量别名定义

```
#include <stdio.h>
int oldVar = 1;
extern int newVar __attribute__((alias("oldVar"))); 
int main(int argc, char *argv[])
{
    printf("oldVar = %d\n", oldVar); // prints 1
}
/** 程序输出结果
newname = 1
*/
```



### \__attribute__((warn_unused_result))

在编程过程中，有的函数我们需要确保函数的返回值必须被使用。但是如果函数使用者直接调用函数且不使用函数的返回值的话，g++ 不会给出warning。这样可能会导致很难寻觅的bug。如调用realloc函数，函数调用者必须使用函数的返回值获得重新分配内存的指针。
利用g++ common function attributes 中提供的warn_unused_result 可以保证函数的返回值在没有被使用的时候提示warning，如果在编译选项添加-Werror, 则在编译时就会提示编译错误。



例子：

```
/*************************************************************************
    > File Name: warn_unused_result.cpp
    > Author: ce39906
    > Mail: ce39906@163.com
    > Created Time: 2018-08-24 14:04:00
 ************************************************************************/

__attribute__ ((warn_unused_result))
int f(int x)
{
    return x / 2;
}

__attribute__ ((warn_unused_result))
double f1()
{
    return 0.;
}

class EmptyClass
{
};

__attribute__ ((warn_unused_result))
EmptyClass f2()
{
    return EmptyClass();
}

class NotEmptyClass
{
    int a;
};

__attribute__ ((warn_unused_result))
NotEmptyClass f3()
{
    return NotEmptyClass();
}

int main()
{
    // cause unused_result warning
    f(3);
    // no unused_result warning
    int x = f(3);
    (void) x;
    // cause unused_result warning
    f1();
    // cause unused_result warning
    f2();
    // no unused_result warning. WHY??
    f3();

    return 0;
}
```



编译:

```
g++ -Wall -Wextra warn_unused_result.cpp -o warn_unused_result
```



编译输出如下

![](https://myblog-1256683296.cos.ap-beijing.myqcloud.com/unused_result_warn.jpg)



### \__attribute__((nonnull))

告诉编译器，那些参数不能为NULL ro nil 所以参数类型必须是指针类型

```
- (int)addNum1:(int *)num1 num2:(int *)num2  __attribute__((nonnull (1,2))){//1,2表示第一个和第二个参数不能为空
    return  *num1 + *num2;
}
 
- (NSString *)getHost:(NSURL *)url __attribute__((nonnull (1))){//第一个参数不能为空
    return url.host;
}

```



### \__attribute__((nothrow))

告诉编译器该函数不能抛出错误

