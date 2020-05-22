// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_BLOCKINGQUEUE_H
#define MUDUO_BASE_BLOCKINGQUEUE_H

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"

#include <deque>
#include <assert.h>

namespace muduo
{
//BlockingQueue即阻塞队列
//当然其最常用的还是用于实现生产者与消费者模式：
/*
offer(E e)：如果队列没满，立即返回true； 如果队列满了，立即返回false-->不阻塞   ---------未实现
put(E e)：如果队列满了，一直阻塞，直到队列不满了或者线程被中断-->阻塞
poll()：如果没有元素，直接返回null；如果有元素，出队------——————————————————————————————未实现
take()：如果队列空了，一直阻塞，直到队列不为空或者线程被中断-->阻塞
*/

template<typename T>
class BlockingQueue : noncopyable
{
 public:
  BlockingQueue()
    : mutex_(),
      notEmpty_(mutex_),
      queue_()
  {
  }

  void put(const T& x)
  {
    MutexLockGuard lock(mutex_);
    queue_.push_back(x);
    notEmpty_.notify(); // wait morphing saves us
    // http://www.domaigne.com/blog/computing/condvars-signal-with-mutex-locked-or-not/
  }

  void put(T&& x)
  {
    MutexLockGuard lock(mutex_);
    queue_.push_back(std::move(x));
    notEmpty_.notify();
  }

  T take()
  {
    MutexLockGuard lock(mutex_);
    // always use a while-loop, due to spurious wakeup
    while (queue_.empty())
    {
      notEmpty_.wait();
    }
    assert(!queue_.empty());
    //std::move 并不会真正地移动对象，真正的移动操作是在移动构造函数、移动赋值函数等完成的，
    //std::move 只是将参数转换为右值引用而已（相当于一个 static_cast）。
    T front(std::move(queue_.front()));//强行拷贝减少析构等操作
    queue_.pop_front();//删除容器的第一个元素
    return front;
  }

  size_t size() const
  {
    MutexLockGuard lock(mutex_);
    return queue_.size();
  }

 private:
  mutable MutexLock mutex_;
  Condition         notEmpty_ GUARDED_BY(mutex_);
  std::deque<T>     queue_ GUARDED_BY(mutex_);
};

}  // namespace muduo

#endif  // MUDUO_BASE_BLOCKINGQUEUE_H
