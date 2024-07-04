#include <Channel.h>

#include <cstdlib>
#include <iostream>

#include <queue>

#include <Epoll.h>
#include <EventLoop.h>
#include <Util.h>

using namespace std;

Channel::Channel(EventLoop* loop) : loop_(loop), events_(0), lastEvents_(0), fd_(0) {}

Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), events_(0), lastEvents_(0) {}

Channel::~Channel() {}

int Channel::getFd() { return fd_; }
void Channel::setFd(int fd) { fd_ = fd; }

void Channel::setHolder(std::shared_ptr<HttpData> holder) { holder_ = holder; }
std::shared_ptr<HttpData> Channel::getHolder() 
{
    std::shared_ptr<HttpData> ret(holder_.lock());
    return ret;
}

void Channel::setReadHandler(CallBack&& readHandler) { readHandler_ = readHandler; }
void Channel::setWriteHandler(CallBack&& writeHandler) { writeHandler_ = writeHandler; }
void Channel::setErrorHandler(CallBack&& errorHandler) { errorHandler_ = errorHandler; }
void Channel::setConnHandler(CallBack&& connHandler) { connHandler_ = connHandler; }

void Channel::handleEvents()
{
    events_ = 0;
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        events_ = 0;
        return;
    }
    if (revents_ & EPOLLERR) {
        if (errorHandler_) errorHandler_();
        events_ = 0;
        return;
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        handleRead();
    }
    if (revents_ & EPOLLOUT) {
        handleWrite();
    }
    handleConn();
}
void Channel::handleRead() 
{
  if (this->readHandler_) 
  {
    this->readHandler_();
  }
}
void Channel::handleWrite() 
{
  if (this->writeHandler_)
  {
    this->writeHandler_();
  }
}
void Channel::handleConn() 
{
  if (this->connHandler_)
  {
    this->connHandler_();
  }
}

void Channel::setRevents(__uint32_t ev) { revents_ = ev; }
void Channel::setEvents(__uint32_t ev) { events_ = ev; }

__uint32_t& Channel::getEvents() { return events_; }

bool Channel::EqualAndUpdateLastEvents()
{
    bool ret = (lastEvents_ == events_);
    lastEvents_ = events_;
    return ret;
}

__uint32_t Channel::getLastEvents() { return lastEvents_; }
