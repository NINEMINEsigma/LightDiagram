#ifdef _LINUX_ON_WINDOW_
# ifndef _CRT_SECURE_NO_WARNINGS
#     define _CRT_SECURE_NO_WARNINGS
# endif
 
# include <stdlib.h>
# include <stdio.h>
# include <tchar.h>
# include "uni_utility.h"

std::map<int, std::fstream> __uni_helper_fd_map;
std::set<int> __uni_helper_fd_index;

int open(const char* pathname, int flags, mode_t mode)
{
    std::ios::openmode mode_type = 0;
    if (flags & O_RDONLY)mode_type = mode_type | std::ios::in;
    if (flags & O_WRONLY)mode_type = mode_type | std::ios::out;
    if (flags & O_RDWR)mode_type = mode_type | std::ios::in | std::ios::out;
    if (flags & O_CREAT)mode_type = mode_type | std::ios::in;
    if (flags & O_APPEND)mode_type = mode_type | std::ios::ate;
    int result = __uni_helper_fd_map.size();
    for (auto& i : __uni_helper_fd_index)
    {
        result = i;
        __uni_helper_fd_index.erase(i);
        break;
    }
    __uni_helper_fd_map[result].open(pathname, mode_type);
    return result;
}

ssize_t write(int fd, const void* buf, size_t count)
{
    if (__uni_helper_fd_map.count(fd))
    {
        try
        {
            __uni_helper_fd_map[fd].write(static_cast<const char*>(buf), count).flush();
        }
        catch (const std::exception& e)
        {
            __uni_helper_fd_map[fd].clear();
            return -1;
        }
        return count;
    }
    return -1;
}

ssize_t read(int fd, void* buf, size_t count)
{
    if (__uni_helper_fd_map.count(fd))
    {
        try
        {
            __uni_helper_fd_map[fd].read(static_cast<char*>(buf), count);
        }
        catch (const std::exception& e)
        {
            __uni_helper_fd_map[fd].clear();
            return -1;
        }
        return count;
    }
    return -1;
}

int close(int fd)
{
    if (__uni_helper_fd_map.count(fd))
    {
        __uni_helper_fd_map[fd].close();
        __uni_helper_fd_map.erase(fd);
        __uni_helper_fd_index.insert(fd);
    }
    return fd;
}
 
int pthread_once(pthread_once_t *once_control, void (*init_routine) (void))
{
    std::lock_guard<std::mutex> lock(once_control->locker);
    if(once_control->stats==0)
    {
        once_control->stats++;
        init_routine();
    }
}

std::map<void*,int> __uni_helper_mmaparr;

void* mmap(void* start, size_t length, int prot, int flags, int fd, off_t offset)
{
    if (__uni_helper_fd_map.count(fd))
    {
        __uni_helper_fd_map[fd].seekg(offset, std::ios::beg);
        void* result = start;
        if (result == nullptr)
        {
            void* result = malloc(sizeof(char) * length);
        }
        __uni_helper_mmaparr[result] = fd;
        read(fd, result, length);
        return result;
    }
    return nullptr;
}

int munmap(void* start, size_t length)
{
    __uni_helper_mmaparr.erase(start);
    ::free(start);
    return length;
}

int msync(void* addr, size_t len, int flags)
{
    if (__uni_helper_mmaparr.count(addr) && __uni_helper_fd_map.count(__uni_helper_mmaparr[addr]))
    {
        write(__uni_helper_mmaparr[addr], addr, len);
        return len;
    }
    return 0;
}

#include <time.h>

int gettimeofday(struct timeval* tp, void* tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

#pragma region getopt.h

# ifdef __cplusplus
#     define _GETOPT_THROW throw()
# else
#     define _GETOPT_THROW
# endif
 
enum ENUM_ORDERING
{
    REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
};
 
struct _getopt_data
{
    int     optind;
    int     opterr;
    int     optopt;
    TCHAR*  optarg;
    int     __initialized;
    TCHAR*  __nextchar;
    int     __ordering;
    int     __posixly_correct;
    int     __first_nonopt;
    int     __last_nonopt;
};
static struct _getopt_data  getopt_data = { 0, 0, 0, NULL, 0, NULL, 0, 0, 0, 0 };
 
TCHAR*  optarg  = NULL;
int     optind  = 1;
int     opterr  = 1;
int     optopt  = _T( '?' );
 
static void exchange( TCHAR** argv, struct _getopt_data* d )
{
    int     bottom  = d->__first_nonopt;
    int     middle  = d->__last_nonopt;
    int     top     = d->optind;
    TCHAR*  tem;
    while ( top > middle && middle > bottom )
    {
        if ( top - middle > middle - bottom )
        {
            int len = middle - bottom;
            register int i;
            for ( i = 0; i < len; i++ )
            {
                tem = argv[bottom + i];
                argv[bottom + i] = argv[top - ( middle - bottom ) + i];
                argv[top - ( middle - bottom ) + i] = tem;
            }
            top -= len;
        }
        else
        {
            int len = top - middle;
            register int i;
            for ( i = 0; i < len; i++ )
            {
                tem = argv[bottom + i];
                argv[bottom + i] = argv[middle + i];
                argv[middle + i] = tem;
            }
            bottom += len;
        }
    }
    d->__first_nonopt += ( d->optind - d->__last_nonopt );
    d->__last_nonopt = d->optind;
}
 
static const TCHAR* _getopt_initialize( const TCHAR* optstring
                                      , struct _getopt_data* d
                                      , int posixly_correct )
{
    d->__first_nonopt = d->__last_nonopt = d->optind;
    d->__nextchar = NULL;
    d->__posixly_correct = posixly_correct
                         | !!_tgetenv( _T( "POSIXLY_CORRECT" ) );
    if ( optstring[0] == _T( '-' ) )
    {
        d->__ordering = RETURN_IN_ORDER;
        ++optstring;
    }
    else if ( optstring[0] == _T( '+' ) )
    {
        d->__ordering = REQUIRE_ORDER;
        ++optstring;
    }
    else if ( d->__posixly_correct )
    {
        d->__ordering = REQUIRE_ORDER;
    }
    else
    {
        d->__ordering = PERMUTE;
    }
    return optstring;
}
 
int _getopt_internal_r( int argc
                      , TCHAR *const * argv
                      , const TCHAR* optstring
                      , const struct option* longopts
                      , int* longind
                      , int long_only
                      , struct _getopt_data* d
                      , int posixly_correct )
{
    int print_errors    = d->opterr;
    if ( argc < 1 )
    {
        return -1;
    }
    d->optarg = NULL;
    if ( d->optind == 0 || !d->__initialized )
    {
        if ( d->optind == 0 )
        {
            d->optind = 1;
        }
        optstring = _getopt_initialize( optstring, d, posixly_correct );
        d->__initialized = 1;
    }
    else if ( optstring[0] == _T( '-' ) || optstring[0] == _T( '+' ) )
    {
        optstring++;
    }
    if ( optstring[0] == _T( ':' ) )
    {
        print_errors = 0;
    }
    if ( d->__nextchar == NULL || *d->__nextchar == _T( '\0' ) )
    {
        if ( d->__last_nonopt > d->optind )
        {
            d->__last_nonopt = d->optind;
        }
        if ( d->__first_nonopt > d->optind )
        {
            d->__first_nonopt = d->optind;
        }
        if ( d->__ordering == PERMUTE )
        {
            if ( d->__first_nonopt != d->__last_nonopt
              && d->__last_nonopt != d->optind )
            {
                exchange( ( TCHAR * * ) argv, d );
            }
            else if ( d->__last_nonopt != d->optind )
            {
                d->__first_nonopt = d->optind;
            }
            while ( d->optind
                  < argc
                 && ( argv[d->optind][0] != _T( '-' )
                   || argv[d->optind][1] == _T( '\0' ) ) )
            {
                d->optind++;
            }
            d->__last_nonopt = d->optind;
        }
        if ( d->optind != argc && !_tcscmp( argv[d->optind], _T( "--" ) ) )
        {
            d->optind++;
            if ( d->__first_nonopt != d->__last_nonopt
              && d->__last_nonopt != d->optind )
            {
                exchange( ( TCHAR * * ) argv, d );
            }
            else if ( d->__first_nonopt == d->__last_nonopt )
            {
                d->__first_nonopt = d->optind;
            }
            d->__last_nonopt = argc;
            d->optind = argc;
        }
        if ( d->optind == argc )
        {
            if ( d->__first_nonopt != d->__last_nonopt )
            {
                d->optind = d->__first_nonopt;
            }
            return -1;
        }
        if ( ( argv[d->optind][0] != _T( '-' )
            || argv[d->optind][1] == _T( '\0' ) ) )
        {
            if ( d->__ordering == REQUIRE_ORDER )
            {
                return -1;
            }
            d->optarg = argv[d->optind++];
            return 1;
        }
        d->__nextchar = ( argv[d->optind]
                        + 1 + ( longopts != NULL
                             && argv[d->optind][1] == _T( '-' ) ) );
    }
    if ( longopts != NULL
        && ( argv[d->optind][1] == _T( '-' )
            || ( long_only && ( argv[d->optind][2]
                                || !_tcschr( optstring, argv[d->optind][1] ) )
               )
           )
        )
    {
        TCHAR*                  nameend;
        const struct option*    p;
        const struct option*    pfound      = NULL;
        int                     exact       = 0;
        int                     ambig       = 0;
        int                     indfound    = -1;
        int                     option_index;
        for ( nameend = d->__nextchar;
              *nameend && *nameend != _T( '=' );
              nameend++ )
            ;
        for ( p = longopts, option_index = 0; p->name; p++, option_index++ )
        {
            if ( !_tcsncmp( p->name, d->__nextchar, nameend - d->__nextchar ) )
            {
                if ( ( unsigned int ) ( nameend - d->__nextchar )
                  == ( unsigned int ) _tcslen( p->name ) )
                {
                    pfound = p;
                    indfound = option_index;
                    exact = 1;
                    break;
                }
                else if ( pfound == NULL )
                {
                    pfound = p;
                    indfound = option_index;
                }
                else if ( long_only
                       || pfound->has_arg != p->has_arg
                       || pfound->flag != p->flag
                       || pfound->val != p->val )
                {
                         ambig = 1;
                }
            }
        }
        if ( ambig && !exact )
        {
            if ( print_errors )
            {
                _ftprintf( stderr
                         , _T( "%s: option '%s' is ambiguous\n" )
                         , argv[0]
                         , argv[d->optind] );
            }
            d->__nextchar += _tcslen( d->__nextchar );
            d->optind++;
            d->optopt = 0;
            return _T( '?' );
        }
        if ( pfound != NULL )
        {
            option_index = indfound;
            d->optind++;
            if ( *nameend )
            {
                if ( pfound->has_arg )
                {
                    d->optarg = nameend + 1;
                }
                else
                {
                    if ( print_errors )
                    {
                        if ( argv[d->optind - 1][1] == _T( '-' ) )
                        {
                            _ftprintf( stderr
                                     , _T( "%s: option '--%s' doesn't allow " )
                                       _T( "an argument\n" )
                                     , argv[0]
                                     , pfound->name );
                        }
                        else
                        {
                            _ftprintf( stderr
                                     , _T( "%s: option '%c%s' doesn't allow " )
                                       _T( "an argument\n" )
                                     , argv[0]
                                     , argv[d->optind - 1][0]
                                     , pfound->name );
                        }
                    }
                    d->__nextchar += _tcslen( d->__nextchar );
                    d->optopt = pfound->val;
                    return _T( '?' );
                }
            }
            else if ( pfound->has_arg == 1 )
            {
                if ( d->optind < argc )
                {
                    d->optarg = argv[d->optind++];
                }
                else
                {
                    if ( print_errors )
                    {
                        _ftprintf( stderr
                                 , _T( "%s: option '--%s' requires an " )
                                   _T( "argument\n" )
                                 , argv[0]
                                 , pfound->name );
                    }
                    d->__nextchar += _tcslen( d->__nextchar );
                    d->optopt = pfound->val;
                    return optstring[0] == _T( ':' ) ? _T( ':' ) : _T( '?' );
                }
            }
            d->__nextchar += _tcslen( d->__nextchar );
            if ( longind != NULL )
            {
                *longind = option_index;
            }
            if ( pfound->flag )
            {
                *( pfound->flag ) = pfound->val;
                return 0;
            }
            return pfound->val;
        }
        if ( !long_only
          || argv[d->optind][1]
          == _T( '-' )
          || _tcschr( optstring
                    , *d->__nextchar )
          == NULL )
        {
            if ( print_errors )
            {
                if ( argv[d->optind][1] == _T( '-' ) )
                {
                    /* --option */
                    _ftprintf( stderr
                             , _T( "%s: unrecognized option '--%s'\n" )
                             , argv[0]
                             , d->__nextchar );
                }
                else
                {
                    /* +option or -option */
                    _ftprintf( stderr
                             , _T( "%s: unrecognized option '%c%s'\n" )
                             , argv[0]
                             , argv[d->optind][0]
                             , d->__nextchar );
                }
            }
            d->__nextchar = ( TCHAR * ) _T( "" );
            d->optind++;
            d->optopt = 0;
            return _T( '?' );
        }
    }
    {
        TCHAR   c       = *d->__nextchar++;
        TCHAR*  temp    = ( TCHAR* ) _tcschr( optstring, c );
        if ( *d->__nextchar == _T( '\0' ) )
        {
            ++d->optind;
        }
        if ( temp == NULL || c == _T( ':' ) || c == _T( ';' ) )
        {
            if ( print_errors )
            {
                _ftprintf( stderr
                         , _T( "%s: invalid option -- '%c'\n" )
                         , argv[0]
                         , c );
            }
            d->optopt = c;
            return _T( '?' );
        }
        if ( temp[0] == _T( 'W' ) && temp[1] == _T( ';' ) )
        {
            TCHAR*                  nameend;
            const struct option*    p;
            const struct option*    pfound      = NULL;
            int                     exact       = 0;
            int                     ambig       = 0;
            int                     indfound    = 0;
            int                     option_index;
            if ( *d->__nextchar != _T( '\0' ) )
            {
                d->optarg = d->__nextchar;
                d->optind++;
            }
            else if ( d->optind == argc )
            {
                if ( print_errors )
                {
                    _ftprintf( stderr
                             , _T( "%s: option requires an argument -- '%c'\n" )
                             , argv[0]
                             , c );
                }
                d->optopt = c;
                if ( optstring[0] == _T( ':' ) )
                {
                    c = _T( ':' );
                }
                else
                {
                    c = _T( '?' );
                }
                return c;
            }
            else
            {
                d->optarg = argv[d->optind++];
            }
            for ( d->__nextchar = nameend = d->optarg;
                  *nameend && *nameend != _T( '=' );
                  nameend++ )
                ;
            for ( p = longopts, option_index = 0;
                  p->name;
                  p++, option_index++ )
            {
                if ( !_tcsncmp( p->name
                              , d->__nextchar
                              , nameend - d->__nextchar ) )
                {
                    if ( ( unsigned int ) ( nameend - d->__nextchar )
                      == _tcslen( p->name ) )
                    {
                        pfound = p;
                        indfound = option_index;
                        exact = 1;
                        break;
                    }
                    else if ( pfound == NULL )
                    {
                        pfound = p;
                        indfound = option_index;
                    }
                    else if ( long_only
                           || pfound->has_arg != p->has_arg
                           || pfound->flag != p->flag
                           || pfound->val != p->val )
                    {
                             ambig = 1;
                    }
                }
            }
            if ( ambig && !exact )
            {
                if ( print_errors )
                {
                    _ftprintf( stderr
                             , _T( "%s: option '-W %s' is ambiguous\n" )
                             , argv[0]
                             , d->optarg );
                }
                d->__nextchar += _tcslen( d->__nextchar );
                d->optind++;
                return _T( '?' );
            }
            if ( pfound != NULL )
            {
                option_index = indfound;
                if ( *nameend )
                {
                    if ( pfound->has_arg )
                    {
                        d->optarg = nameend + 1;
                    }
                    else
                    {
                        if ( print_errors )
                        {
                            _ftprintf( stderr
                                     , _T( "%s: option '-W %s' doesn't allow " )
                                       _T( "an argument\n" )
                                     , argv[0]
                                     , pfound->name );
                        }
                        d->__nextchar += _tcslen( d->__nextchar );
                        return _T( '?' );
                    }
                }
                else if ( pfound->has_arg == 1 )
                {
                    if ( d->optind < argc )
                    {
                        d->optarg = argv[d->optind++];
                    }
                    else
                    {
                        if ( print_errors )
                        {
                            _ftprintf( stderr
                                     , _T( "%s: option '-W %s' requires an " )
                                       _T( "argument\n" )
                                     , argv[0]
                                     , pfound->name );
                        }
                        d->__nextchar += _tcslen( d->__nextchar );
                        return optstring[0] == _T(':') ? _T(':') : _T('?');
                    }
                }
                else
                {
                    d->optarg = NULL;
                }
                d->__nextchar += _tcslen( d->__nextchar );
                if ( longind != NULL )
                {
                    *longind = option_index;
                }
                if ( pfound->flag )
                {
                    *( pfound->flag ) = pfound->val;
                    return 0;
                }
                return pfound->val;
            }
            d->__nextchar = NULL;
            return _T( 'W' );
        }
        if ( temp[1] == _T( ':' ) )
        {
            if ( temp[2] == _T( ':' ) )
            {
                if ( *d->__nextchar != _T( '\0' ) )
                {
                    d->optarg = d->__nextchar;
                    d->optind++;
                }
                else
                {
                    d->optarg = NULL;
                }
                d->__nextchar = NULL;
            }
            else
            {
                if ( *d->__nextchar != _T( '\0' ) )
                {
                    d->optarg = d->__nextchar;
                    d->optind++;
                }
                else if ( d->optind == argc )
                {
                    if ( print_errors )
                    {
                        _ftprintf( stderr
                                 , _T( "%s: option requires an " )
                                   _T( "argument -- '%c'\n" )
                                 , argv[0]
                                 , c );
                    }
                    d->optopt = c;
                    if ( optstring[0] == _T( ':' ) )
                    {
                        c = _T( ':' );
                    }
                    else
                    {
                        c = _T( '?' );
                    }
                }
                else
                {
                    d->optarg = argv[d->optind++];
                }
                d->__nextchar = NULL;
            }
        }
        return c;
    }
}
 
int _getopt_internal( int argc
                    , TCHAR *const * argv
                    , const TCHAR* optstring
                    , const struct option* longopts
                    , int* longind
                    , int long_only
                    , int posixly_correct )
{
    int result;
    getopt_data.optind = optind;
    getopt_data.opterr = opterr;
    result = _getopt_internal_r( argc
                               , argv
                               , optstring
                               , longopts
                               , longind
                               , long_only
                               , &getopt_data
                               , posixly_correct );
    optind = getopt_data.optind;
    optarg = getopt_data.optarg;
    optopt = getopt_data.optopt;
    return result;
}
 
int getopt( int argc, TCHAR *const * argv, const TCHAR* optstring) _GETOPT_THROW
{
    return _getopt_internal( argc
                           , argv
                           , optstring
                           , ( const struct option * ) 0
                           , ( int * ) 0
                           , 0
                           , 0 );
}
 
int getopt_long( int argc
               , TCHAR *const * argv
               , const TCHAR* options
               , const struct option* long_options
               , int* opt_index ) _GETOPT_THROW
{
    return _getopt_internal( argc
                           , argv
                           , options
                           , long_options
                           , opt_index
                           , 0
                           , 0 );
}
 
int _getopt_long_r( int argc
                  , TCHAR *const * argv
                  , const TCHAR* options
                  , const struct option* long_options
                  , int* opt_index
                  , struct _getopt_data* d )
{
    return _getopt_internal_r( argc
                             , argv
                             , options
                             , long_options
                             , opt_index
                             , 0
                             , d
                             , 0 );
}
 
int getopt_long_only( int argc
                    , TCHAR *const * argv
                    , const TCHAR* options
                    , const struct option* long_options
                    , int* opt_index ) _GETOPT_THROW
{
    return _getopt_internal( argc
                           , argv
                           , options
                           , long_options
                           , opt_index
                           , 1
                           , 0 );
}
 
int _getopt_long_only_r( int argc
                       , TCHAR *const * argv
                       , const TCHAR* options
                       , const struct option* long_options
                       , int* opt_index
                       , struct _getopt_data* d )
{
    return _getopt_internal_r( argc
                             , argv
                             , options
                             , long_options
                             , opt_index
                             , 1
                             , d
                             , 0 );
}
 
void getopt_reset()
{
    optarg  = NULL;
    optind  = 1;
    opterr  = 1;
    optopt  = _T( '?' );
    //
    getopt_data.optind            = 0;
    getopt_data.opterr            = 0;
    getopt_data.optopt            = 0;
    getopt_data.optarg            = NULL;
    getopt_data.__initialized     = 0;
    getopt_data.__nextchar        = NULL;
    getopt_data.__ordering        = 0;
    getopt_data.__posixly_correct = 0;
    getopt_data.__first_nonopt    = 0;
    getopt_data.__last_nonopt     = 0;
}

#pragma endregion

#endif
