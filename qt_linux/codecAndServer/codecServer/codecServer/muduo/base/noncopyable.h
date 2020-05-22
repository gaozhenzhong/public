#ifndef MUDUO_BASE_NONCOPYABLE_H
#define MUDUO_BASE_NONCOPYABLE_H

namespace muduo
{
// C++11 中，可在想要 “禁止使用” 的特殊成员函数声明后加 “= delete”，
//而需要保留的加 "= default" 或者不采取操作
class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected://当子类中的构造函数调用父类中的 public或protected构造函数时是对的,所以这个类不能被单独创建
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace muduo

#endif  // MUDUO_BASE_NONCOPYABLE_H
