#ifndef __FILE_UNI_UTITIY

#define __FILE_UNI_UTITIY

// on window(with linux)
#if defined(_WINDOW_)

#include <Core/Header/LF_Config.h>

#include <mutex>

#ifdef _WIN64
typedef int64_t ssize_t;
#else
typedef int32_t ssize_t;
#endif
typedef unsigned int mode_t;
typedef uint32_t __uint32_t;
typedef uint64_t __uint64_t;
typedef int pid_t;
struct pthread_once_t
{
    std::mutex locker;
    int stats = 0;
};
#ifndef PTHREAD_ONCE_INIT
#define PTHREAD_ONCE_INIT pthread_once_t()
#endif
#ifndef __thread
#define __thread thread_local 
#endif
typedef union epoll_data 
{
    void* ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;
struct epoll_event 
{
    uint32_t events;    // epoll 事件类型，包括可读，可写等
    epoll_data_t data;  // 用户数据，可以是一个指针或文件描述符等
};
#pragma region events
#ifndef EPOLLIN
#define EPOLLIN         0
#endif
#ifndef EPOLLOUT
#define EPOLLOUT        1
#endif
#ifndef EPOLLRDHUP
#define EPOLLRDHUP      2
#endif
#ifndef EPOLLPRI
#define EPOLLPRI        4
#endif
#ifndef EPOLLERR
#define EPOLLERR        8
#endif
#ifndef EPOLLHUP
#define EPOLLHUP        16
#endif
#ifndef EPOLLET
#define EPOLLET         32
#endif
#ifndef EPOLLONESHOT
#define EPOLLONESHOT    64
#endif
#pragma endregion


#include <fstream>
#include <map>
#include <set>

extern int open(const char *pathname, int flags, mode_t mode);
extern ssize_t write(int fd, const void *buf, size_t count);
extern ssize_t read(int fd, void *buf, size_t count);
extern int pthread_once(pthread_once_t* once_control, void (*init_routine) (void));

std::map<int,std::fstream> __uni_helper_fd_map;
std::set<int> __uni_helper_fd_index;

#pragma region open -> int flags
#ifndef O_RDONLY
#define O_RDONLY    1
#endif
#ifndef O_WRONLY
#define O_WRONLY    2
#endif
#ifndef O_RDWR
#define O_RDWR      3
#endif 
#ifndef O_CREAT
#define O_CREAT     4
#endif
#ifndef O_APPEND
#define O_APPEND    5
#endif
#ifndef O_TRUNC
#define O_TRUNC     6
#endif
#pragma endregion
#pragma region open -> mode_t mode
#ifndef S_ISUID
#define S_ISUID     04000  
#endif
#ifndef S_ISGID
#define S_ISGID     02000  
#endif
#ifndef S_ISVTX
#define S_ISVTX     01000  
#endif
#ifndef S_IRUSR
#define S_IRUSR     00400
#endif  
#ifndef S_IWUSR
#define S_IWUSR     00200   
#endif
#ifndef S_IXUSR
#define S_IXUSR     00100  
#endif
#ifndef S_IRGRP
#define S_IRGRP     00040  
#endif
#ifndef S_IWGRP
#define S_IWGRP     00020  
#endif
#ifndef S_IXGRP
#define S_IXGRP     00010  
#endif
#ifndef S_IROTH
#define S_IROTH     00004  
#endif
#ifndef S_IWOTH
#define S_IWOTH     00002  
#endif
#ifndef S_IXOTH
#define S_IXOTH     00001  
#endif 
#pragma endregion

# ifndef __GETOPT_H_
# define __GETOPT_H_
 
# ifdef _GETOPT_API
#     undef _GETOPT_API
# endif
//------------------------------------------------------------------------------
# if defined(EXPORTS_GETOPT) && defined(STATIC_GETOPT)
#     error "The preprocessor definitions of EXPORTS_GETOPT and STATIC_GETOPT \
can only be used individually"
# elif defined(STATIC_GETOPT)
#     pragma message("Warning static builds of getopt violate the Lesser GNU \
Public License")
#     define _GETOPT_API
# else
#     define _GETOPT_API _LF_C_API(DLL)
# endif
 
# include <tchar.h>
// Standard GNU options
# define null_argument           0 /*Argument Null*/
# define no_argument             0 /*Argument Switch Only*/
# define required_argument       1 /*Argument Required*/
# define optional_argument       2 /*Argument Optional*/
// Shorter Versions of options
# define ARG_NULL 0 /*Argument Null*/
# define ARG_NONE 0 /*Argument Switch Only*/
# define ARG_REQ  1 /*Argument Required*/
# define ARG_OPT  2 /*Argument Optional*/
// Change behavior for C\C++
# ifdef __cplusplus
#     define _BEGIN_EXTERN_C extern "C" {
#     define _END_EXTERN_C }
#     define _GETOPT_THROW throw()
# else
#     define _BEGIN_EXTERN_C
#     define _END_EXTERN_C
#     define _GETOPT_THROW
# endif
_BEGIN_EXTERN_C
extern _GETOPT_API TCHAR *optarg;
extern _GETOPT_API int    optind;
extern _GETOPT_API int    opterr;
extern _GETOPT_API int    optopt;
struct option
{
/* The predefined macro variable __STDC__ is defined for C++, and it has the in-
   teger value 0 when it is used in an #if statement, indicating that the C++ l-
   anguage is not a proper superset of C, and that the compiler does not confor-
   m to C. In C, __STDC__ has the integer value 1. */
# if defined (__STDC__) && __STDC__
    const TCHAR* name;
# else
    TCHAR* name;
# endif
    int has_arg;
    int *flag;
    TCHAR val;
};
extern _GETOPT_API int getopt( int argc, TCHAR *const *argv
                             , const TCHAR *optstring ) _GETOPT_THROW;
extern _GETOPT_API int getopt_long
                             ( int ___argc, TCHAR *const *___argv
                             , const TCHAR *__shortopts
                             , const struct option *__longopts
                             , int *__longind ) _GETOPT_THROW;
extern _GETOPT_API int getopt_long_only
                             ( int ___argc, TCHAR *const *___argv
                             , const TCHAR *__shortopts
                             , const struct option *__longopts
                             , int *__longind ) _GETOPT_THROW;
// harly.he add for reentrant 12.09/2013
extern _GETOPT_API void getopt_reset() _GETOPT_THROW;
_END_EXTERN_C
// Undefine so the macros are not included
# undef _BEGIN_EXTERN_C
# undef _END_EXTERN_C
# undef _GETOPT_THROW
# undef _GETOPT_API
# endif  // __GETOPT_H_

#endif

#endif
