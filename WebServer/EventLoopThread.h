#pragma once
#ifndef __FILE_EVENTLOOPTHREAD
#define __FILE_EVENTLOOPTHREAD
#include <LightDiagram.h>
#include <EventLoop.h>
#include <base/Condition.h>
#include <base/MutexLock.h>
#include <base/Thread.h>


_LF_C_API(Class) EventLoopThread final: public noncopyable
{
public:
  EventLoopThread();
  ~EventLoopThread();
  EventLoop* startLoop();

private:
  void threadFunc();
  EventLoop* loop_;
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_;
};

#endif // !__FILE_EVENTLOOPTHREAD
