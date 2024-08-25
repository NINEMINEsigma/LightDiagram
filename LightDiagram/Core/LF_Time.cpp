#include <Core/LF_Time.h>

using namespace std;

namespace ld
{
    Clock::Clock() : m_StartTimepoint(std::chrono::high_resolution_clock::now()), m_LastTimepoint(std::chrono::high_resolution_clock::now())
    {

    }

    void Clock::Count(TimeDuration* ns, TimeDoubleDuration* ms)
    {
        if (ns != nullptr)
        {
            *ns = CountNanosecond();
            if (ms != nullptr)
                *ms = *ns * 1e-6;
        }
        else if (ms != nullptr)
        {
            *ms = CountMillisecond();
        }
    }

    TimeDuration Clock::CountNanosecond()
    {
        m_LastTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_LastTimepoint).time_since_epoch().count();

        return end - start;
    }

    TimeDoubleDuration Clock::CountMillisecond()
    {
        return CountNanosecond() * 1e-6;
    }

    TimeDuration Clock::operator-(const Clock& _Right) const
    {
        return
            std::chrono::time_point_cast<std::chrono::nanoseconds>(this->m_StartTimepoint).time_since_epoch().count() -
            std::chrono::time_point_cast<std::chrono::nanoseconds>(_Right.m_StartTimepoint).time_since_epoch().count();
    }

    TimeTick::TimeTick() : m_StartTimepoint(std::chrono::high_resolution_clock::now())
    {

    }

    void TimeTick::operator=(const TimeTick& _Right)
    {
        this->m_StartTimepoint = _Right.m_StartTimepoint;
    }

    TimeDuration TimeTick::Duration() const
    {
        auto m_LastTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_LastTimepoint).time_since_epoch().count();

        return end - start;
    }

    TimeDuration TimeTick::operator-(const TimeTick& _Right) const
    {
        return
            std::chrono::time_point_cast<std::chrono::nanoseconds>(this->m_StartTimepoint).time_since_epoch().count() -
            std::chrono::time_point_cast<std::chrono::nanoseconds>(_Right.m_StartTimepoint).time_since_epoch().count();
    }

}

