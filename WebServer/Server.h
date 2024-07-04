#ifndef __FILE_SERVER
#define __FILE_SERVER

#pragma once
#include <LightDiagram.h>
#include <memory>
#include <Channel.h>
#include <EventLoop.h>
#include <EventLoopThreadPool.h>

_LF_C_API(Class) Server final:public any_class
{
public:
	Server(EventLoop * loop, int threadNum, int port);
	~Server() {}
	EventLoop* getLoop() const;
	void start();
	void handNewConn();
	void handThisConn();

private:
	EventLoop* loop_;
	int threadNum_;
	std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
	bool started_;
	std::shared_ptr<Channel> acceptChannel_;
	int port_;
	int listenFd_;
	static const int MAXFDS = 100000;
};

#endif // !__FILE_SERVER

