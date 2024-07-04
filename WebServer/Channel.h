#ifndef __FILE_CHANNEL
#define __FILE_CHANNEL

#pragma once

#include <LightDiagram.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <Timer.h>

class EventLoop;
class HttpData;

using ChannelCallBack = std::function<void()>;

_LF_C_API(Class) Channel final:public any_class
{
public:
    using CallBack = ChannelCallBack;
private:
    EventLoop* loop_;
    int fd_;
    __uint32_t events_;
    __uint32_t revents_;
    __uint32_t lastEvents_;

    // 方便找到上层持有该Channel的对象
    std::weak_ptr<HttpData> holder_;

private:
    int parse_URI();
    int parse_Headers();
    int analysisRequest();

    CallBack readHandler_;
    CallBack writeHandler_;
    CallBack errorHandler_;
    CallBack connHandler_;

public:
    Channel(EventLoop* loop);
    Channel(EventLoop* loop, int fd);
    ~Channel();
    int getFd();
    void setFd(int fd);

    void setHolder(std::shared_ptr<HttpData> holder);
    std::shared_ptr<HttpData> getHolder();

    void setReadHandler(CallBack&& readHandler);
    void setWriteHandler(CallBack&& writeHandler);
    void setErrorHandler(CallBack&& errorHandler);
    void setConnHandler(CallBack&& connHandler);

    void handleEvents();
    void handleRead();
    void handleWrite();
    void handleError(int fd, int err_num, std::string short_msg);
    void handleConn();

    void setRevents(__uint32_t ev);
    void setEvents(__uint32_t ev);

    __uint32_t& getEvents();

    bool EqualAndUpdateLastEvents();

    __uint32_t getLastEvents();
};

using SP_Channel = std::shared_ptr<Channel>;

#endif // !__FILE_CHANNEL
