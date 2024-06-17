#ifndef __FILE_LF_EXCEPTION

#define __FILE_LF_EXCEPTION

#include<Core/Header/LF_Config.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/static_indicator.h>

namespace ld
{
	// Enum class for console text color
	enum _LF_C_API(Class) ConsoleColor
	{
		Green, Red, Blue, White, Black, Yellow, Purple, Gray, Cyan, None,
		GreenIntensity, RedIntensity, BlueIntensity, WhiteIntensity, BlackIntensity, YellowIntensity, PurpleIntensity, GrayIntensity, CyanIntensity
	};

	// Enum class for console background color
	enum _LF_C_API(Class) ConsoleBackgroundColor
	{
		Green, Red, Blue, White, Black, Yellow, Purple, Gray, Cyan, None
	};

#ifdef _WINDOW_
	// Get the Windows color code for a given ConsoleColor
    WORD GetColorCode(ConsoleColor color);
#else
	// Get the ANSI escape code for a given ConsoleColor
	std::wstring GetColorCode(ConsoleColor color);
#endif

#ifdef _WINDOW_
	// Get the Windows color code for a given ConsoleBackgroundColor
	WORD GetBackgroundColorCode(ConsoleBackgroundColor color);
#else
	// Get the ANSI escape code for a given ConsoleBackgroundColor
	std::wstring GetBackgroundColorCode(ConsoleBackgroundColor color);
#endif


    std::ostream& operator<< (std::ostream& os, ConsoleColor data);
    std::ostream& operator<< (std::ostream& os, ConsoleBackgroundColor data);
    std::wostream& operator<< (std::wostream& os, ConsoleColor data);
    std::wostream& operator<< (std::wostream& os, ConsoleBackgroundColor data);

    using string = string_indicator::tag;

    extern std::ostream* clog;

    extern bool is_log_message_to_cout;

    // Commonly used exception
    _LF_C_API(Class)    LDException:    _LF_Inherited(any_class)
    {
        LDException(const time_t & ts, const string & msg);
        bool* is_release;
    public:
        LDException();
        LDException(const string & msg);
        LDException(LDException & ex) noexcept;
        LDException(LDException && ex) noexcept;
        virtual ~LDException();
        void release() const noexcept;
        int* counter;
        string message;
    };

    //  Ease Progress Bar
    void    _LF_C_API(DLL)  EaseProgressBar(double t, int length, ConsoleBackgroundColor color);
    //  Ease Progress Bar
    void    _LF_C_API(DLL)  EaseProgressBar(int a, int b, int length, ConsoleBackgroundColor color);

    _LF_C_API(Class)    ConsolePro:
    _LF_Inherited(anyclass)
    {
    public:
        ConsolePro();
        virtual ~ConsolePro();

        using symbol_t = short;
        using string = string_indicator::tag;

        symbol_t Message, Warning, Error;
        ConsoleColor FC;
        ConsoleBackgroundColor BC;

        ConsolePro& Log(const string & message, const string & label, const string & tail, const symbol_t & type) const;
        ConsolePro& LogMessage(const string & message, const string & label, const string & tail) const;
        ConsolePro& LogWarning(const string & message, const string & label, const string & tail) const;
        ConsolePro& LogError(const string & message, const string & label, const string & tail) const;
        ConsolePro& CoutMessage(const string & message, const string & label, const string & tail) const;
        ConsolePro& CoutWarning(const string & message, const string & label, const string & tail) const;
        ConsolePro& CoutError(const string & message, const string & label, const string & tail) const;
    };
}

#endif // !__FILE_LF_EXCEPTION
