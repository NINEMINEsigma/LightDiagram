#ifndef __FILE_EVENTLOOP
#define __FILE_EVENTLOOP

#pragma once
#include <LightDiagram.h>
#include <functional>
#include <memory>
#include <vector>
#include <Channel.h>
#include <Epoll.h>
#include <Util.h>
#include <base/CurrentThread.h>
#include <base/Logging.h>
#include <base/Thread.h>


#include <iostream>
using namespace std;

using Functor = std::function<void()>;

_LF_C_API(Class) EventLoop final: public any_class
{
 public:
  EventLoop();
  ~EventLoop();
  void loop();
  void quit();
  void runInLoop(Functor&& cb);
  void queueInLoop(Functor&& cb);
  bool isInLoopThread() const;
  void assertInLoopThread();
  void shutdown(shared_ptr<Channel> channel);
  void removeFromPoller(shared_ptr<Channel> channel);
  void updatePoller(shared_ptr<Channel> channel, int timeout = 0);
  void addToPoller(shared_ptr<Channel> channel, int timeout = 0);

 private:
  // 声明顺序 wakeupFd_ > pwakeupChannel_
  bool looping_;
  shared_ptr<Epoll> poller_;
  int wakeupFd_;
  bool quit_;
  bool eventHandling_;
  mutable MutexLock mutex_;
  std::vector<Functor> pendingFunctors_;
  bool callingPendingFunctors_;
  const pid_t threadId_;
  shared_ptr<Channel> pwakeupChannel_;

  void wakeup();
  void handleRead();
  void doPendingFunctors();
  void handleConn();
};

#endif // !__FILE_EVENTLOOP
