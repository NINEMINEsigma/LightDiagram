#include <LightDiagram.h>
#include <EventLoop.h>
#include <Server.h>
#include <base/Logging.h>

int main(int argc, char* argv[])
{
    int threadNum = 4;
    int port = 80;
    std::string logPath = "./WebServer.log";
    ld::ConsolePro consolepro;
    // parse args
    int opt;
    // thread(100) logPath(./WebServer.log) port(80) begin("index.html")
    const char* str = "t:l:p:i:";
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 't':
        {
            threadNum = atoi(optarg);
        }
        break;
        case 'l':
        {
            logPath = optarg;
            if (logPath.size() < 2 || optarg[0] != '/')
            {
                printf("logPath should start with \"/\"\n");
                abort();
            }
        }
        break;
        case 'p':
        {
            port = atoi(optarg);
        }
        break;
        case 'i':
        {
            if (FILE* file = fopen(optarg, "r"))
            {
                fclose(file);
                html_start_file_path = optarg;
                return true;
            }
            else
            {
                printf("file:%s is not find", optarg);
                abort();
            }
        }
        break;
        default:
            break;
        }
    }
    consolepro.LogMessage("opt is read over");
    Logger::setLogFileName(logPath);
    consolepro.LogMessage("log path is setup");
    // STL库在多线程上应用
#ifndef _PTHREADS
    LOG << "_PTHREADS is not defined !";
#endif
    EventLoop mainLoop;
    consolepro.LogMessage("main loop is ready");
    consolepro.LogMessage("HTTP Server is try create");
    Server myHTTPServer(&mainLoop, threadNum, port);
    consolepro.LogMessage("HTTP Server is ready");
    myHTTPServer.start();
    consolepro.LogMessage("HTTP Server is start");
    consolepro.LogMessage("main loop is begin");
    mainLoop.loop();
    return 0;
}
