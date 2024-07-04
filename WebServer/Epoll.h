#ifndef __FILE_EPOLL
#define __FILE_EPOLL
#pragma once
#include <LightDiagram.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include <Channel.h>
#include <HttpData.h>
#include <Timer.h>

_LF_C_API(Class) Epoll final:public any_class
{
public:
  Epoll();
  ~Epoll();
  void epoll_add(SP_Channel request, int timeout);
  void epoll_mod(SP_Channel request, int timeout);
  void epoll_del(SP_Channel request);
  std::vector<std::shared_ptr<Channel>> poll();
  std::vector<std::shared_ptr<Channel>> getEventsRequest(int events_num);
  void add_timer(std::shared_ptr<Channel> request_data, int timeout);
  int getEpollFd() { return epollFd_; }
  void handleExpired();
private:
	constexpr static int MAXFDS = 1 << 16;
	int epollFd_;
	std::vector<epoll_event> events_;
	std::shared_ptr<Channel> fd2chan_[MAXFDS];
	std::shared_ptr<HttpData> fd2http_[MAXFDS];
	TimerManager timerManager_;
};
#endif // !__FILE_EPOLL

