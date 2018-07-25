build shared library, linking against other **convenience libraries**.

# how to run

## build library

```shell
cd mylibs
autoreconf -if
./configure
make
```

依赖关系: myso_2nd_libs里是我们想要的最终的共享库(.so), 而myso_2nd_libs又要链接依赖my_1nd_libs里的"`.a`库"(注意其**不是静态库**,仅仅是个`.a`后缀的文件而已,准确地讲叫 *libtool convenience library* 便利库).  
这里的*libtool convenience library*,我们通过观察make命令的输出信息可知,这个`.a`文件其实是`-fPIC`过的`.o`文件的归档.

为了创建 *libtool convenience library*: 我们在automake里需使用 *directory-less* + primary 式的变量 如 `noinst_LTLIBRARIES`, 而非 `lib_LTLIBRARIES`; 并且不能指定`-rpath`或`-static`.
参考:  
https://www.gnu.org/software/automake/manual/html_node/Libtool-Convenience-Libraries.html  
https://www.gnu.org/software/libtool/manual/html_node/Static-libraries.html  


总结1:

| 1 库 | 2 linking against | 可行性 | 是否有object文件拷贝操作 |
| --- | --- | :---: | --- |
| static library (.a)  | static library (.a)      | YES | 2的objects被拷贝进1里 |
| shared library (.so) | static library (.a)      | 失败 | X |
| static library (.a)  | shared library (.so)     | YES | 2的objects*没有*被拷贝进1里 |
| shared library (.so) | shared library (.so)     | YES | 2的objects*没有*被拷贝进1里 |
| static library (.a)  | convenience library (ca) | YES | 2的objects被拷贝进1里 |
| shared library (.so) | convenience library (ca) | YES | 2的objects被拷贝进1里 |


总结2:

> 在目录my_1nd_libs里, 如果:
>
> 一. `directory-less_LTLIBRARIES`(例如`noinst_LTLIBRARIES`) 情况下:
>
> - `xxx_la_LDFLAGS`不赋值, 或`xxx_la_LDFLAGS = -shared`等 (非`-rpath`,`-static`): 生成的是convenience library. 虽然也是以`.a`后缀,但并不是静态库. (通过观察make命令的输出信息可知其是`-fPIC`过的`.o`文件的归档.)
> - `xxx_la_LDFLAGS = -static` : 生成真正的static library (.a).
>
> 二. `lib_LTLIBRARIES` 情况下:
>
> - `xxx_la_LDFLAGS = -shared` : 生成真正的shared library (.so).
> - `xxx_la_LDFLAGS = -static` : 生成真正的static library (.a).
>
> 也即: `directory-less_LTLIBRARIES`, 且不指定为`-rpath`或`-static`时, 那么生成的是convenience library.


## build a test program

作为验证, 我们build一个测试程序,链接前面已经build出的共享库.

```shell
cd TEST
autoreconf -if
./configure
make

ldd hiworld

./hiworld
```
