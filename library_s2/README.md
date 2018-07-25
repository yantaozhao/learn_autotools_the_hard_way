build libraries using autoconf+automake+libtool

注意: put `LT_INIT` after `AM_PROG_AR`


# how to run

```shell
% ls
func.h  func.cp

autoscan
mv -i confugure.scan confugure.ac
touch Makefile.am
```


修改 Makefile.am 内容后, `autoreconf -if` 时报告各种错误, 按照提示的信息不断修改 confugure.ac 和 Makefile.am 直至成功:

```shell
autoreconf -if

./configure
make

tree -a
```
