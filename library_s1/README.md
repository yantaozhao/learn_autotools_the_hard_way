build libraries using only libtool


# how to run

`sudo apt-get install libtool-bin`

```shell
libtool --tag=CXX --mode=compile g++ -g -c func.cpp

libtool --tag=CXX --mode=link g++ -g -o libmymath.la func.lo
# or:
libtool --tag=CXX --mode=link g++ -g -o libmymath.la -rpath /usr/local/lib func.lo

libtool --mode=clean rm -f *.o *.lo *.la
```

> 关于`-rpath`库的路径 (比如这里的 /usr/local/lib), 可参考 `man ldconfig`

注意观察有无 `-rpath` 时的区别.
