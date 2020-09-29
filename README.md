# CUB : C++ Unified Base Library

***

## Introduction

`CUB` is a C\++ unified base library for writting better and effective `C++` codes! It includes below main components:
- Some grammer sugar that wrappered `C++` keywords for a better cross-platform C++ programming style.
- A [DCI](https://en.wikipedia.org/wiki/Data,_context_and_interaction) programming frame for implementing composed programming in C++ easily!
- Memory utils. For example: memory allocator,  AutoMsg, TransData ...
- Data structures (eg. array, list, map) for self memory government demands! It's useful for embeded programming.
- Some algorithm for bits operator, loop, bound...
- Design pattern, such as Singleton and State pattern.
- Concurrency tools, such as thread pool, lock utils... 
- Log, an implementation of log for CUB.

To learn more, visit the doc folder! View the source code of tests of CUB in the test folder for learning how to use every library elements in details!

## Install and Test

### Get CUB

~~~ bash
git clone git@github.com:ccup/cub.git
~~~

### Build CUB

~~~ bash
cd cub
./ccup.sh -ub
~~~

### Install CUB

~~~ bash
cd cub
./ccup.sh -i
~~~

You can also install CUB manually, just copy "cub/include" and "cub/build/src/libcub.a" to your special installation path.

### Test CUB

Following the below instructions to test CUB:

~~~ bash
cd cub
./ccup.sh -ubt
~~~

To test CUB, script will auto download [cctest](https://github.com:ccup/cctest) which is an elegant C\++ xUnit framework. Try to intall cut by following the [cctest tutoral](https://github.com/ccup/cctest/blob/master/README.md)!

### Supported Platform:

- [MAC OS X] supported
- [Linux] supported
- [Windows] not supported

### Supported Compilers:

- [CLANG] 3.4 or later.
- [GCC] 4.8 or later.
- [MSVC] not supported.

## Finally

Some component of CUB such as "sched" which based on std::thread need C\++11 suport, therefor compile all the components of CUB should enable the C\++11 compiling flag and link with pthread!
