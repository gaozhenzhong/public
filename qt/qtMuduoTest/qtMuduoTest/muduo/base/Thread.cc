// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "muduo/base/Thread.h"
#include "muduo/base/CurrentThread.h"
#include "muduo/base/Exception.h"
#include "muduo/base/Logging.h"

#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace muduo
{
namespace detail
{
/*
在linux下每一个进程都一个进程id，类型pid_t，可以由 getpid（）获取。
POSIX线程也有线程id，类型pthread_t，可以由 pthread_self（）获取，线程id由线程库维护。

但是各个进程独立，所以会有不同进程中线程号相同节的情况。那么这样就会存在一个问题，我的进程p1中的线程pt1要与进程p2中的线程pt2通信怎么办，
进程id不可以，线程id又可能重复，所以这里会有一个真实的线程id唯一标识，tid。glibc没有实现gettid的函数，所以我们可以通过linux下的系统调用 syscall(SYS_gettid) 来获得。
*/
pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void afterFork()
{
  muduo::CurrentThread::t_cachedTid = 0;
  muduo::CurrentThread::t_threadName = "main";
  CurrentThread::tid();
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer
{
 public:
  ThreadNameInitializer()
  {
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
    pthread_atfork(NULL, NULL, &afterFork);//https://blog.csdn.net/codinghonor/article/details/43737869
  }
};

ThreadNameInitializer init;

struct ThreadData
{
  typedef muduo::Thread::ThreadFunc ThreadFunc;
  ThreadFunc func_;
  string name_;
  pid_t* tid_;
  CountDownLatch* latch_;

  ThreadData(ThreadFunc func,
             const string& name,
             pid_t* tid,
             CountDownLatch* latch)
    : func_(std::move(func)),
      name_(name),
      tid_(tid),
      latch_(latch)
  { }

  void runInThread()
  {
    *tid_ = muduo::CurrentThread::tid();
    tid_ = NULL;
    latch_->countDown();
    latch_ = NULL;

    muduo::CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();
    ::prctl(PR_SET_NAME, muduo::CurrentThread::t_threadName);
    try
    {
      func_();
      muduo::CurrentThread::t_threadName = "finished";
    }
    catch (const Exception& ex)
    {
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
      abort();
    }
    catch (const std::exception& ex)
    {
    /*
	std::exception：标准异常类的基类，其类的声明在头文件<exception>中。所有标准库的异常类均继承于此类，
	因此通过引用类型可以捕获所有标准异常。
	std::exception类定义了无参构造函数、拷贝构造函数、拷贝赋值运算符、一个虚析构函数和一个名为what的无参虚成员。
	其中what函数返回一个const char*，该指针指向一个以null结尾的字符数组，并且确保不会抛出任何异常，
	该字符串的目的是提供关于异常的一些文本信息。除析构函数外，其它函数均通过关键字noexcept说明此函数不会抛出异常。
	*/
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      abort();
    }
    catch (...)
    {
    //这里会拦截住所有try里没有被前面捕获的错误，但是你不知道是什么错误
	//如果有前边的catch，这个...一般不会运行到
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
      throw; // rethrow
    }
  }
};

void* startThread(void* obj)
{
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->runInThread();
  delete data;
  return NULL;
}

}  // namespace detail

void CurrentThread::cacheTid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = detail::gettid();
    t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}
//当全局变量在局部函数中与其中某个变量重名，那么就可以用::来区分，
bool CurrentThread::isMainThread()
{
  return tid() == ::getpid();
}
/*
sleep()-------以秒为单位
#include<unistd.h>
unsigned int sleep(unsigned int seconds);
return：若进程暂停到参数seconds 所指定的时间，成功则返回0，若有信号中断则返回剩余秒数。
在linux中，sleep是通过nanosleep实现的。在一些其他系统中（例如POSIX.1），它是通过alarm()来实现的。

usleep()----以微秒为单位
#include<unistd.h>
unsigned int usleep(unsigned int useconds);
return：若进程暂停到参数seconds 所指定的时间，成功则返回0，若有信号中断则返回剩余微秒数。

nanosleep( )---------以纳秒为单位
#include<time.h>
 struct timespec
{
  time_t  tv_sec;          秒seconds 
  long    tv_nsec;         纳秒nanoseconds 
};
int nanosleep(const struct timespec *req, struct timespec *rem);
return: 若进程暂停到参数*req所指定的时间，成功则返回0，若有信号中断则返回-1，并且将剩余微秒数记录在*rem中。
req->tv_sec是以秒为单位，而tv_nsec以毫微秒为单位（10的-9次方秒）。
由于调用nanosleep是是进程进入TASK_INTERRUPTIBLE,这种状态是会相应信号而进入TASK_RUNNING状态的。
*/
void CurrentThread::sleepUsec(int64_t usec)
{
  struct timespec ts = { 0, 0 };
  ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
  ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
  ::nanosleep(&ts, NULL);
}
//Thread+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
AtomicInt32 Thread::numCreated_;

Thread::Thread(ThreadFunc func, const string& n)
  : started_(false),
    joined_(false),
    pthreadId_(0),
    tid_(0),
    func_(std::move(func)),
    name_(n),
    latch_(1)
{
  setDefaultName();
}


/*
创建一个线程默认的状态是joinable, 如果一个线程结束运行但没有被join,则它的状态类似于进程中的Zombie Process,
即还有一部分资源没有被回收（退出状态码），所以创建线程者应该pthread_join来等待线程运行结束，并可得到线程的退出代码，
回收其资源（类似于wait,waitpid)
但是调用pthread_join(pthread_id)后，如果该线程没有运行结束，调用者会被阻塞，在有些情况下我们并不希望如此，
比如在Web服务器中当主线程为每个新来的链接创建一个子线程进行处理的时候，主线程并不希望因为调用pthread_join而阻塞
（因为还要继续处理之后到来的链接），这时可以在子线程中加入代码
pthread_detach(pthread_self())
或者父线程调用
pthread_detach(thread_id)（非阻塞，可立即返回）
这将该子线程的状态设置为detached,则该线程运行结束后会自动释放所有资源。

*/
Thread::~Thread()
{
  if (started_ && !joined_)
  {//以防万一的操作
    pthread_detach(pthreadId_);
  }
}

void Thread::setDefaultName()
{
  int num = numCreated_.incrementAndGet();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

void Thread::start()
{
  assert(!started_);
  started_ = true;
  // FIXME: move(func_)
  detail::ThreadData* data = new detail::ThreadData(func_, name_, &tid_, &latch_);
  /*
  若线程创建成功，则返回0。若线程创建失败，则返回出错编号，并且*thread中的内容是未定义的。
  第一个参数为指向线程标识符的指针。
  第二个参数用来设置线程属性。
  第三个参数是线程运行函数的起始地址。
  最后一个参数是运行函数的参数。

  */
  if (pthread_create(&pthreadId_, NULL, &detail::startThread, data))
  {
    started_ = false;
    delete data; // or no delete?
    LOG_SYSFATAL << "Failed in pthread_create";
  }
  else
  {
    latch_.wait();
    assert(tid_ > 0);
  }
}

int Thread::join()
{
  assert(started_);
  assert(!joined_);
  joined_ = true;
  return pthread_join(pthreadId_, NULL);//挂起了，在等待1号线程结束
}

}  // namespace muduo
