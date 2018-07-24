[TOC]

Way 1: executable file built with multi files in subdir

# automake

在configure.ac里通过`AM_INIT_AUTOMAKE`给的OPTIONS值是全局起效. 而在Makefile.am里通过`AUTOMAKE_OPTIONS`给的OPTIONS值是makefile级起效的.
且`AUTOMAKE_OPTIONS`里的OPTIONS值,优先于`AM_INIT_AUTOMAKE`里的.

- AUTOMAKE_OPTIONS:
  - foreign : 严格等级, 一般就用foreign
  - subdir-objects : 准许在子文件夹中,生成对应于source file的object文件.
