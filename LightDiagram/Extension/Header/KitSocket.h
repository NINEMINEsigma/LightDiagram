#ifndef __FILE_KITSOCKET

#define __FILE_KITSOCKET

#include<Core/Header/LF_Config.h>

#ifdef _WINDOW_
typedef SOCKET HSocket;
#pragma comment(lib, "ws2_32.lib")
#elif defined(_LINUX_)
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
typedef int HSocket;
#define SOCKET_ERROR  (-1)
#define INVALID_SOCKET  0
#endif

_LF_C_API(Struct) socketoption_t
{
    int block;
    int sendbuffersize;
    int recvbuffersize;
    int lingertimeout;
    int recvtimeout;
    int sendtimeout;
};

_LF_C_API(Struct) transresult_t
{
    int nbytes;
    int nresult;
};

namespace ld
{
    namespace socketkit
    {
        int _LF_C_API(Func) InitializeSocketEnvironment();
        void _LF_C_API(Func) FreeSocketEnvironment();
        void _LF_C_API(Func) GetAddressFrom(SOCKADDR_IN* addr, const char* ip, int port);
        void _LF_C_API(Func) GetIpAddress(char* ip, SOCKADDR_IN* addr);
        bool _LF_C_API(Func) IsValidSocketHandle(HSocket handle);
        int  _LF_C_API(Func)  GetLastSocketError();

        HSocket _LF_C_API(Func)  SocketOpen(int tcpudp);
        void _LF_C_API(Func)  SocketClose(HSocket& handle);

        int _LF_C_API(Func) SocketBlock(HSocket hs, bool bblock);
        int _LF_C_API(Func) SocketTimeOut(HSocket hs, int recvtimeout, int sendtimeout, int lingertimeout);

        int  _LF_C_API(Func) SocketBind(HSocket hs, SOCKADDR_IN* addr);
        HSocket _LF_C_API(Func)  SocketAccept(HSocket hs, SOCKADDR_IN* addr);
        int _LF_C_API(Func)  SocketListen(HSocket hs, int maxconn);

        void _LF_C_API(Func) SocketSend(HSocket hs, const char* ptr, int nbytes, transresult_t& rt);
        void _LF_C_API(Func) SocketRecv(HSocket hs, char* ptr, int nbytes, transresult_t& rt);
        void _LF_C_API(Func) SocketTryRecv(HSocket hs, char* ptr, int nbytes, int milliseconds, transresult_t& rt);
        void _LF_C_API(Func) SocketTrySend(HSocket hs, const char* ptr, int nbytes, int milliseconds, transresult_t& rt);

        void  _LF_C_API(Func)  SocketClearRecvBuffer(HSocket hs);

        _LF_C_API(Class) CSockWrap
        {
        public:
            CSockWrap(int tcpudp);
            ~CSockWrap();
            void SetAddress(const char* ip, int port);
            void SetAddress(SOCKADDR_IN* addr);
            int SetTimeOut(int recvtimeout, int sendtimeout, int lingertimeout);
            int SetBufferSize(int recvbuffersize, int sendbuffersize);
            int SetBlock(bool bblock);

            HSocket  GetHandle() { return m_hSocket; }
            void Reopen(bool bForceClose);
            void Close();
            transresult_t Send(void* ptr, int nbytes);
            transresult_t Recv(void* ptr, int nbytes);
            transresult_t TrySend(void* ptr, int nbytes, int milliseconds);
            transresult_t TryRecv(void* ptr, int nbytes, int  milliseconds);
            void ClearRecvBuffer();

        protected:
            HSocket  m_hSocket;
            SOCKADDR_IN m_stAddr;
            int m_tcpudp;
        };

        using kit = CSockWrap;
    }
}

#endif //!__FILE_KITSOCKET
