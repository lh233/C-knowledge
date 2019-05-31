Linux有三个关于目录切换的常用命令，分别是cd,pushd,popd。cd大家再熟悉不过了，今天学习了一下pushd的使用。

cd用于切换工作目录，但是如果你在两个目录之间需要频繁切换时，比如/etc/httpd/log/error和/home/testUser/Desktop/shell_test，那这样一直 cd cd会发疯的。所以pushd在此时是个好选择。


pushd的 功能是创建一个目录栈，你可以把你目前常见的几个目录压入栈中，并可以迅速地进行切换，非常方便。如：


```
[root@localhost etc]# pushd ~/Desktop/shell_test/
~/Desktop/shell_test    /etc
[root@localhost shell_test]#
```

可以看到我本来的工作目录是/etc，执行pushd ~/Desktop/shell_test/后将 ~/Desktop/shell_test/路径压入栈中，得到返回值。而且当前目录也跳转了。

此时，再输入pushd会将栈顶目录和下一目录对调。即：


```
[root@localhost shell_test]# pushd 
/etc    ~/Desktop/shell_test
[root@localhost etc]#
```


可以看到此时栈顶目录又变为/etc

至于popd，作用则是与pushd相反，将栈顶的目录弹出，此时除非再一次使用pushd压栈，否则pushd无法再找到已弹出的目录。


```

[root@localhost etc]# popd
~/Desktop/shell_test
[root@localhost shell_test]#
-----
#popd [+N|-N]还可以指定目录栈的哪个目录优先出栈
```


建议：在使用pushd时，最好是在三两个目录频繁切换的场景下，否则目录栈变得过多就失去了pushd的优势了。 

当然，在两个目录进行切换时，”cd -” 是一个不错的命令

### 如何在多个目录之间切换? 

用 pushd +n即可 

说明: 

- n是一个数字,有此参数时，是切换到堆栈中的第n个目录,并把此目录以堆栈循环的方式推到堆栈的顶部 需要注意: 堆栈从第0个开始数起



```
~/Hi3559A/work/REMO_HI3559AV100_SDK/Hi3559AV100_Remo_SDK ~/Hi3559A/work/REMO_HI3559AV100_SDK ~/Hi3559A/work/REMO_HI3559AV100_SDK/Hi3559AV100_SDK_V2.0.1.0/osdrv
```

第一个为2的数字，第二个为1的数字，第三个为0的数字