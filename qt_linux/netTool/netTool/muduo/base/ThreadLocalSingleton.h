// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREADLOCALSINGLETON_H
#define MUDUO_BASE_THREADLOCALSINGLETON_H

#include "muduo/base/noncopyable.h"

#include <assert.h>
#include <pthread.h>

namespace muduo
{

template<typename T>
class ThreadLocalSingleton : noncopyable
{
 public:
  ThreadLocalSingleton() = delete;
  ~ThreadLocalSingleton() = delete;

  static T& instance()
  {
    if (!t_value_)
    {
      t_value_ = new T();
      deleter_.set(t_value_);
    }
    return *t_value_;
  }

  static T* pointer()
  {
    return t_value_;
  }

 private:
  static void destructor(void* obj)
  {
    assert(obj == t_value_);
    //这句话其实就是定义了一个固定大小的char型数组，数组名为type_must_be_complete`
    //数组大小还能为负数？当然不能，于是就会报错，而且是编译期错误，于是就将一个动态运行时错误在编译时就发现了。
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;
    delete t_value_;
    t_value_ = 0;
  }
/*
1、创建一个键  pthread_key_create

2、为一个键设置线程私有数据  pthread_setspecific

3、从一个键读取线程私有数据void *pthread_getspecific(pthread_key_t key);

4、线程退出（退出时，会调用destructor释放分配的缓存，参数是key所关联的数据）

5、删除一个键  pthread_key_delete
*/  
  class Deleter
  {
   public:
    Deleter()
    {
      pthread_key_create(&pkey_, &ThreadLocalSingleton::destructor);
    }

    ~Deleter()
    {
      pthread_key_delete(pkey_);
    }

    void set(T* newObj)
    {
      assert(pthread_getspecific(pkey_) == NULL);
      pthread_setspecific(pkey_, newObj);
    }

    pthread_key_t pkey_;
  };

  static __thread T* t_value_;////__thread的效果是每个线程一个备份
  static Deleter deleter_;

};

template<typename T>
__thread T* ThreadLocalSingleton<T>::t_value_ = 0;

template<typename T>
typename ThreadLocalSingleton<T>::Deleter ThreadLocalSingleton<T>::deleter_;//

}  // namespace muduo
#endif  // MUDUO_BASE_THREADLOCALSINGLETON_H
