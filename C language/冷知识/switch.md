```
#include<stdio.h>
main()
{
  int k;
  scanf("%d",&k);
  switch(k)
  {
  	 printf("hello world\n");	//注意这里不会执行到
     case 1: printf("a"); break;
     case 2: printf("b"); break;
     default: printf("c"); break;
  }
} 
```

