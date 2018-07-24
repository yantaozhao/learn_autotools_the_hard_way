[TOC]

# How to run

```shell
% ls
main.cpp

autoscan
mv -i configure.scan configure.ac
touch Makefile.am
```

修改相应内容,然后:

```shell
autoreconf -if
./configure
make

./hiworld
```

------

# Syntax

## autoconf

典型的格式:

```text
Autoconf requirements
AC_INIT(package, version, bug-report-address)
information on the package
checks for programs
checks for libraries
checks for header files
checks for types
checks for structures
checks for compiler characteristics
checks for library functions
checks for system services
AC_CONFIG_FILES([file...])
AC_OUTPUT
```

- `AC_CONFIG_SRCDIR (unique-file-in-source-dir)`:
  帮助*configure*去正确地确定source code (srcdir)所在的目录.
  例如: `AC_CONFIG_SRCDIR([src/foo.c])`.
- `AC_CONFIG_HEADERS (header ..., [cmds], [init-cmds])`:
  - create *header* file(s) containing C preprocessor `#define` statements. 常用的文件名是 `config.h`, 例如: `AC_CONFIG_HEADERS([config.h])`.
  - 若不使用该命令,则不会创建文件, `#define` 会以 `-D` 形式被写进`Makefile`里的 `DEFS` 变量里.
- `AM_INIT_AUTOMAKE([OPTIONS])`: 例如:`AM_INIT_AUTOMAKE([-Wall -Werror foreign])`.
- `LT_INIT` : 需要放在 `AM_PROG_AR` 的后面.
- 检查程序是否满足要求:
  - AC_PROG_CC
  - AC_PROG_CC_C_O
  - AC_PROG_CXX
  - AM_PROG_AR
  - AC_PROG_RANLIB :
    (1,当你用 `_LIBRARIES` 生成`.a`库时,记得必须检查此项; 2,当使用`_LTLIBRARIES`生成库时,libtool会去判断是否使用ranlib,所以就不要再检查此项)
  - AC_PROG_LN_S
  - ~~AC_PROG_LIBTOOL~~
  - AC_PROG_INSTALL
- `AC_CONFIG_FILES (file..., [cmds], [init-cmds])`:
  create each *file* by copying an input file (by default *file.in*), substituting the output variable values.
  例如: `AC_CONFIG_FILES([Makefile])`, `AC_CONFIG_FILES([autoconf], [chmod +x autoconf])`.


## automake

这里分四个部分讲:
1. uniform naming scheme : prefix + primary
2. `_SOURCES`
3. 编译器FLAGS参数
4. 链接器参数

一. 统一命名法(uniform naming scheme)  
名字由多个 *片段(piece)* 拼接而成. 根据变量名能推导出 build的类型?将来install到哪里?

参考: https://www.gnu.org/software/automake/manual/html_node/Uniform.html

- build的类型? 其依据的piece叫 **primary**. 例如:
  - PROGRAMS : 可执行程序
  - LIBRARIES : 静态库(.a)
  - LTLIBRARIES : 共享库(.so)
  - HEADERS : 头文件
  - SCRIPTS
  - DATA
  - MANS

  对于每个*primary*, 对应有一个添加`EXTRA_`前缀的变量名(例如:`EXTRA_PROGRAMS`),这个变量用于 list objects that may or may not be built, depending on what *configure* decides.

  一个*primary*定义了一个所谓的*target*,这个*target*在接下来引用时需要进行拼写形式转换(即canonicalization),具体方法就是除了字母、数字、@、下划线外,其他的字符都转换为下划线.
  > 例如:
  > ```automake
  > lib_LIBRARIES = libfoo.a
  > libfoo_a_SOURCES = foo.cpp
  > ```

- install到哪里? 其依据的piece,是*primary*的 **prefix** ,该*prefix*在书写拼接变量名时要去掉`dir`词尾. 例如:
  - bindir
  - sbindir
  - includedir
  - libdir
  - `noinst_` : 被编译,但不需要install. (indicates that the objects in question should be built but not installed at all.)

  注意*prefix*在这里是去掉了`dir`词尾的 (即`bindir`写成`bin_`即可).  所以 `bin_PROGRAMS` 就表示:要编译成可执行文件,将来安装到*bindir*目录下.

二. `_SOURCES`

用于指定源代码文件: target`_SOURCES`

参考: https://www.gnu.org/software/automake/manual/html_node/Program-and-Library-Variables.html

三. 编译器FLAGS

有三个级别:
- target级别: (per-executable|per-library)`_CFLAGS`
- automake级别: `AM_CFLAGS`
- 用户user级别: `CFLAGS`

主要有:
- CC
- CXX
- _CPPFLAGS
- _CFLAGS
- _CXXFLAGS

区分: `CFLAGS`, `AM_CFLAGS`, target`_CFLAGS` 该用哪个?  
参考: https://www.gnu.org/software/automake/manual/html_node/Flag-Variables-Ordering.html  
> Automake总是只使用这三者中的两个: (target`_CFLAGS` || `AM_CFLAGS`) + `CFLAGS`.
>
> 看例子:
> ```c
> bin_PROGRAMS = foo bar
> foo_SOURCES = foo.c
> bar_SOURCES = bar.c
> foo_CPPFLAGS = -DFOO
> AM_CPPFLAGS = -DBAZ
> ```
> 这里将以如下方式编译:
> - foo.c的编译flags是: `$(foo_CPPFLAGS) $(CPPFLAGS)` . 因为其 target`_CFLAGS` 存在.
> - bar.c的编译flags是: `$(AM_CPPFLAGS) $(CPPFLAGS)`, 因为其 target`_CFLAGS` 不存在.
>
> 这就是automake默认的使用flag的顺序(Flag Variables Ordering).
>
> 还有一点: 在 Makefile.am 文件里, 应该总是**避免**使用和重定义`CPPFLAGS`的值.

四. 链接器参数

LDFLAGS同样是三个级别的: target`_LDFLAGS`,`AM_LDFLAGS`,和user级别`LDFLAGS`.
- _LDFLAGS
- ~~_LIBTOOLFLAGS~~

库名的指定,被拆分成了target级别的两个变量:
- _LDADD : for things that are being added to a program, 例如 prog_LDADD
- _LIBADD : for things that are being added to a library, 例如 library_LIBADD

  关于`_LDADD`指定库名, automake手册里推荐的用法是: 如果库是自己编译的,就显式地写出库名; 如果是第三方库,才用`-lfoo`的形式. (We recommend that you avoid using `-l` options in `LDADD` or `prog_LDADD` when referring to libraries built by your package. ... Use `-l` only to list third-party libraries.)

背景知识:
> 在 GNUmakefile / Makefile里 (参考gnu make manual):
>
> `LDFLAGS` : Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as `-L`.
>
> `LDLIBS` : Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’.
>
> Non-library linker flags, such as `-L`, should go in the `LDFLAGS` variable.
>
> Libraries (`-lfoo`) should be added to the `LDLIBS` variable instead.
