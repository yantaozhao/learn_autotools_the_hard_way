[TOC]

way 2: executable file built with multi files in subdir

# automake

- `nodist_`
- `BUILT_SOURCES` : 仅在make all/check/install这几个target的时候起效.
- `foo.$(OBJEXT): dependencies` : 手动记录依赖文件

See:  
https://www.gnu.org/software/automake/manual/html_node/Fine_002dgrained-Distribution-Control.html  
https://www.gnu.org/software/automake/manual/html_node/Built-Sources-Example.html  
