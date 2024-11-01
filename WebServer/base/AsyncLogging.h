#ifndef __FILE_ASYNCLOGGING
#define __FILE_ASYNCLOGGING
#pragma once
#include <LightDiagram.h>
#include <functional>
#include <string>
#include <vector>
#include <CountDownLatch.h>
#include <LogStream.h>
#include <MutexLock.h>
#include <Thread.h>

_LF_C_API(Class) AsyncLogging : public noncopyable
{
public:
    AsyncLogging(const std::string basename, int flushInterval = 2);
    ~AsyncLogging();
    void append(const char* logline, int len);

    void start();
    void stop();

private:
    void threadFunc();
    typedef FixedBuffer<kLargeBuffer> Buffer;
    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
    typedef std::shared_ptr<Buffer> BufferPtr;
    const int flushInterval_;
    bool running_;
    std::string basename_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;
    BufferVector buffers_;
    CountDownLatch latch_;
};

#endif // !__FILE_ASYNCLOGGING
