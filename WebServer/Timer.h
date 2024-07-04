#ifndef __FILE_TIMER

#pragma once
#include <LightDiagram.h>
#include <deque>
#include <memory>
#include <queue>
#include <HttpData.h>
#include <base/MutexLock.h>
#include <base/noncopyable.h>

class HttpData;

_LF_C_API(Class) TimerNode
{
public:
    TimerNode(std::shared_ptr<HttpData> requestData, int timeout);
    ~TimerNode();
    TimerNode(TimerNode & tn);
    void update(int timeout);
    bool isValid();
    void clearReq();
    void setDeleted();
    bool isDeleted()const;
    size_t getExpTime()const;
private:
    bool deleted_;
    size_t expiredTime_;
    std::shared_ptr<HttpData> SPHttpData;
};

struct TimerCmp
{
    bool operator()(std::shared_ptr<TimerNode>& a, std::shared_ptr<TimerNode>& b) const;
};

class TimerManager
{
public:
    using SPTimerNode = std::shared_ptr<TimerNode>;
    TimerManager();
    ~TimerManager();
    void addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout);
    void handleExpiredEvent();

private:
    std::priority_queue<SPTimerNode, std::deque<SPTimerNode>, TimerCmp> timerNodeQueue;
    // MutexLock lock;
};

#define __FILE_TIMER
#endif // !__FILE_TIMER
