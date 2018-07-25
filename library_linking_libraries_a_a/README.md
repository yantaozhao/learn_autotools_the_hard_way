build static library, linking against other static libraries.

# how to run

## build library

依赖关系: mya_2nd_libs里是我们想要的最终的静态库, 而mya_2nd_libs又要链接依赖mya_1nd_libs里的静态库.

注意: 虽然mya_1nd_libs里的库是`noinst_LTLIBRARIES`,但因为`libchecker_la_LDFLAGS = -static`指定了`-static`,所以它是一个**真正的**静态库static library.
这点我们可以通过观察make命令的输出信息获知.



```shell
cd myalibs
autoreconf -if
./configure
make
```

## build a test program

作为验证, 我们build一个测试程序,链接前面已经build出的静态库.

```shell
cd TEST
autoreconf -if
./configure
make

ldd hiworld

./hiworld
```
