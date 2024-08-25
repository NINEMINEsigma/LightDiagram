#ifndef __FILE_LF_TIME
#define __FILE_LF_TIME

#include <Core/LF_Config.h>

namespace ld
{
    using TimeDuration = long long;
    using TimeDoubleDuration = double;

    class Clock
    {
    public:
        Clock();
        void Count(_Out_opt_ TimeDuration* ns, _Out_opt_ TimeDoubleDuration* ms);
        TimeDuration CountNanosecond();
        TimeDoubleDuration CountMillisecond();
        TimeDuration operator-(const Clock& _Right) const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTimepoint;
    };
    class TimeTick
    {
    public:
        TimeTick();
        void operator=(const TimeTick& _Right);
        TimeDuration Duration() const;
        TimeDuration operator-(const TimeTick& _Right) const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    };
}

#endif // !__FILE_LF_TIME
