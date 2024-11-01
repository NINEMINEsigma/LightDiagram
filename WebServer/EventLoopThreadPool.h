#ifndef __FILE_EVENTLOOPTHREADPOOL
#define __FILE_EVENTLOOPTHREADPOOL
#pragma once
#include <LightDiagram.h>
#include <memory>
#include <vector>
#include <EventLoopThread.h>
#include <base/Logging.h>

_LF_C_API(Class) EventLoopThreadPool final: public noncopyable
{
public:
	EventLoopThreadPool(EventLoop * baseLoop, int numThreads);
	~EventLoopThreadPool();
	void start();

	EventLoop* getNextLoop();

private:
	EventLoop* baseLoop_;
	bool started_;
	int numThreads_;
	int next_;
	std::vector<std::shared_ptr<EventLoopThread>> threads_;
	std::vector<EventLoop*> loops_;
};

#endif // !__FILE_EVENTLOOPTHREADPOOL
