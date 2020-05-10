// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "muduo/base/CurrentThread.h"

#include <cxxabi.h>
#include <execinfo.h>
#include <stdlib.h>

namespace muduo
{
namespace CurrentThread
{
/*
_thread
_thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。
__thread变量每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。
线程共享进程的数据，如果想要每个线程都有一份独立的数据，那么可以使用__thread关键字修饰数据。 __thread只能用于修饰POD类型的数据，不能修饰class，
因为它无法调用构造函数和析构函数。__thread可以修饰全局变量、函数内的静态变量，不能修饰函数内的局部变量或class的普通成员变量。

t_cachedTid表示线程的真实id。 POSIX的thread库提供了pthread_self获取当前线程的标识符，类型为pthread_t，这是一个结构体，
用起来不便。线程的真实id是一个整数，可以通过系统调用syscall(SYS_gettid)获得，在muduo中封装为gettid()函数。
调用系统调用开销比较大，因此可以使用一个变量t_cachedTid来存储，在线程第一次使用tid时通过系统调用获得，存储在t_cacheTid中，以后使用时不再需要系统调用了。
t_tidString[32] 用string类型表示tid，便于输出日志。
t_tidStringLength string类型tid的长度。
t_threadName 线程的名字。
*/
__thread int t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "unknown";
static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");


/* Store up to SIZE return address of the current program state in
   ARRAY and return the exact number of values stored.  */
//int backtrace(void **array, int size);
 
/* Return names of functions from the backtrace list in ARRAY in a newly
   malloc()ed memory block.  */
//char **backtrace_symbols(void *const *array, int size);
 
/* This function is similar to backtrace_symbols() but it writes the result
   immediately to a file.  */
//void backtrace_symbols_fd(void *const *array, int size, int fd);

//编译参数添加rdynamic 才可以看到函数名
string stackTrace(bool demangle)
{
  string stack;
  const int max_frames = 200;
  void* frame[max_frames];
  int nptrs = ::backtrace(frame, max_frames);
  char** strings = ::backtrace_symbols(frame, nptrs);
  if (strings)
  {
    size_t len = 256;
    char* demangled = demangle ? static_cast<char*>(::malloc(len)) : nullptr;
    for (int i = 1; i < nptrs; ++i)  // skipping the 0-th, which is this function
    {
      if (demangle)
      {
        // https://panthema.net/2008/0901-stacktrace-demangled/
        // bin/exception_test(_ZN3Bar4testEv+0x79) [0x401909]
        char* left_par = nullptr;
        char* plus = nullptr;
        for (char* p = strings[i]; *p; ++p)
        {
          if (*p == '(')
            left_par = p;
          else if (*p == '+')
            plus = p;
        }

        if (left_par && plus)
        {
          *plus = '\0';
          int status = 0;
          char* ret = abi::__cxa_demangle(left_par+1, demangled, &len, &status);
          *plus = '+';
          if (status == 0)
          {
            demangled = ret;  // ret could be realloc()
            stack.append(strings[i], left_par+1);
            stack.append(demangled);
            stack.append(plus);
            stack.push_back('\n');
            continue;
          }
        }
      }
      // Fallback to mangled names
      stack.append(strings[i]);
      stack.push_back('\n');
    }
    free(demangled);
    free(strings);
  }
  return stack;
}

}  // namespace CurrentThread
}  // namespace muduo
