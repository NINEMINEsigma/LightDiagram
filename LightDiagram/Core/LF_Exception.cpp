#include<Core/Header/LF_Exception.h>

namespace ld
{
#ifdef _WINDOW_
	// Get the Windows color code for a given ConsoleColor
	WORD GetColorCode(ConsoleColor color)
	{
		switch (color)
		{
		case ConsoleColor::Green: return FOREGROUND_GREEN;
		case ConsoleColor::Black: return 0;
		case ConsoleColor::Blue: return FOREGROUND_BLUE;
		case ConsoleColor::Gray: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		case ConsoleColor::Purple: return FOREGROUND_BLUE | FOREGROUND_RED;
		case ConsoleColor::Red: return FOREGROUND_RED;
		case ConsoleColor::White: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		case ConsoleColor::Cyan: return FOREGROUND_BLUE | FOREGROUND_GREEN;
		case ConsoleColor::Yellow: return FOREGROUND_RED | FOREGROUND_GREEN;
		case ConsoleColor::None: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		case ConsoleColor::GreenIntensity: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		case ConsoleColor::BlackIntensity: return 0;
		case ConsoleColor::BlueIntensity: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		case ConsoleColor::GrayIntensity: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		case ConsoleColor::PurpleIntensity: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		case ConsoleColor::RedIntensity: return FOREGROUND_RED | FOREGROUND_INTENSITY;
		case ConsoleColor::WhiteIntensity: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		case ConsoleColor::YellowIntensity: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		case ConsoleColor::CyanIntensity: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		default: return 0;
		}
	}
#else
	// Get the ANSI escape code for a given ConsoleColor
	std::wstring GetColorCode(ConsoleColor color)
	{
		switch (color)
		{
		case ConsoleColor::Green: return L"\033[32m";
		case ConsoleColor::Black: return L"\033[30m";
		case ConsoleColor::Blue: return L"\033[34m";
		case ConsoleColor::Gray: return L"\033[37m";
		case ConsoleColor::Purple: return L"\033[35m";
		case ConsoleColor::Red: return L"\033[31m";
		case ConsoleColor::White: return L"\033[37m";
		case ConsoleColor::Cyan: return L"\033[36m";
		case ConsoleColor::Yellow: return L"\033[33m";
		case ConsoleColor::None: return L"\033[0m";
		case ConsoleColor::GreenIntensity: return L"\033[32m;1m";
		case ConsoleColor::BlackIntensity: return L"\033[30m;1m";
		case ConsoleColor::BlueIntensity: return L"\033[34m;1m";
		case ConsoleColor::GrayIntensity: return L"\033[37m;1m";
		case ConsoleColor::PurpleIntensity: return L"\033[35m;1m";
		case ConsoleColor::RedIntensity: return L"\033[31m;1m";
		case ConsoleColor::WhiteIntensity: return L"\033[37m;1m";
		case ConsoleColor::YellowIntensity: return L"\033[33m;1m";
		case ConsoleColor::CyanIntensity: return L"\033[36m;1m";
		default: return 0;
		}
	}
#endif

#ifdef _WINDOW_
	// Get the Windows color code for a given ConsoleBackgroundColor
	WORD GetBackgroundColorCode(ConsoleBackgroundColor color)
	{
		switch (color)
		{
		case ConsoleBackgroundColor::Green: return BACKGROUND_GREEN;
		case ConsoleBackgroundColor::Black: return 0;
		case ConsoleBackgroundColor::Blue: return BACKGROUND_BLUE;
		case ConsoleBackgroundColor::Gray: return 0;
		case ConsoleBackgroundColor::Purple: return BACKGROUND_RED | BACKGROUND_BLUE;
		case ConsoleBackgroundColor::Red: return BACKGROUND_RED;
		case ConsoleBackgroundColor::White: return BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
		case ConsoleBackgroundColor::Cyan: return BACKGROUND_BLUE | BACKGROUND_GREEN;
		case ConsoleBackgroundColor::Yellow: return BACKGROUND_RED | BACKGROUND_GREEN;
		case ConsoleBackgroundColor::None: return 0;
		default: return 0;
		}
	}
#else
	// Get the ANSI escape code for a given ConsoleBackgroundColor
	std::wstring GetBackgroundColorCode(ConsoleBackgroundColor color)
	{
		switch (color)
		{
		case ConsoleBackgroundColor::Green: return L"\033[42m";
		case ConsoleBackgroundColor::Black: return L"\033[40m";
		case ConsoleBackgroundColor::Blue: return L"\033[44m";
		case ConsoleBackgroundColor::Gray: return L"\033[40m";
		case ConsoleBackgroundColor::Purple: return L"\033[45m";
		case ConsoleBackgroundColor::Red: return L"\033[41m";
		case ConsoleBackgroundColor::White: return L"\033[47m";
		case ConsoleBackgroundColor::Cyan: return L"\033[46m";
		case ConsoleBackgroundColor::Yellow: return L"\033[43m";
		case ConsoleBackgroundColor::None: return L"\033[40m";
		default: return 0;
		}
	}
#endif

	// Operator overloading for console text color
	std::ostream& operator<< (std::ostream& os, ConsoleColor data)
	{
#ifdef _WINDOW_
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetColorCode(data));
#else 
		std::cout << GetColorCode(data);
#endif

		return os;
	}

	// Operator overloading for console background color
	std::ostream& operator<< (std::ostream& os, ConsoleBackgroundColor data)
	{
#ifdef _WINDOW_
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetBackgroundColorCode(data));
#else 
		std::cout << GetBackgroundColorCode(data);
#endif

		return os;
	}

	// Operator overloading for console text color
	std::wostream& operator<< (std::wostream& os, ConsoleColor data)
	{
#ifdef _WINDOW_
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetColorCode(data));
#else 
		std::wcout << GetColorCode(data);
#endif

		return os;
	}

	// Operator overloading for console background color
	std::wostream& operator<< (std::wostream& os, ConsoleBackgroundColor data)
	{
#ifdef _WINDOW_
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetBackgroundColorCode(data));
#else 
		std::wcout << GetBackgroundColorCode(data);
#endif

		return os;
	}


	std::ostream* clog = new std::ofstream("./line exception.txt");

	bool is_log_message_to_cout = true;

	LDException::LDException(const time_t& ts, const string& msg)
		:message(msg),
		counter(new int(1)),
		is_release(new bool(false)) {}
	LDException::LDException() :LDException("unknown") {}
	LDException::LDException(const string& msg) :LDException(time(nullptr), msg) {}
	LDException::LDException(LDException& ex) noexcept
		:counter(ex.counter),
		is_release(ex.is_release),
		message(ex.message)
	{
		(*counter)++;
	}
	LDException::LDException(LDException&& ex) noexcept
		:counter(ex.counter),
		is_release(ex.is_release),
		message(ex.message)
	{
		ex.counter = nullptr;
		ex.is_release = nullptr;
		ex.message.clear();
	}
	LDException::~LDException()
	{
		if (counter == nullptr)return;
		(*counter)--;
		if (*counter)
		{
			if (*is_release)return;
			(*clog) << "<break>" << message << "<!exception is not catch>" << std::endl;
			if (is_log_message_to_cout)
			{
				std::cout
					<< ConsoleColor::Red
					<< message
					<< ConsoleColor::None << std::endl;
			}
		}
		else
		{
			delete is_release;
			delete counter;
		}
	}
	void LDException::release() const noexcept
	{
		if (!*is_release)
		{
			*is_release = true;
			(*clog) << "<catch>" << message << "<!exception is catch>" << std::endl;
			if (is_log_message_to_cout)
			{
				std::cout
					<< ConsoleColor::Yellow
					<< message
					<< ConsoleColor::None << std::endl;
			}
		}
	}

	//  Ease Progress Bar
	void    _LF_C_API(DLL)  EaseProgressBar(double t, int length, ConsoleBackgroundColor color)
	{
		std::cout << color;
		for (int i = 0, e = t * length; i < e; i++)
		{
			std::cout << " ";
		}
		std::cout << ConsoleBackgroundColor::None;
		for (int i = t * length; i <= length; i++)
		{
			std::cout << " ";
		}
		std::cout << ConsoleColor::Blue << ((int)(t * 10000) * 0.01) << "%" << ConsoleColor::Black;
		std::cout << "                                         \r";
	}
	//  Ease Progress Bar
	void    _LF_C_API(DLL)  EaseProgressBar(int a, int b, int length, ConsoleBackgroundColor color)
	{
		std::cout << color;
		for (int i = 0, e = (double)a / (double)b * length; i < e; i++)
		{
			std::cout << " ";
		}
		std::cout << ConsoleBackgroundColor::None;
		for (int i = (double)a / (double)b * length; i <= length; i++)
		{
			std::cout << " ";
		}
		std::cout << ConsoleColor::Blue << a << "/" << b << ConsoleColor::Black;
		std::cout << "                                         \r";
	}


	ConsolePro& ConsolePro::Log(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail, const ConsolePro::symbol_t& type) const
	{
		if (type == this->Warning)
		{

		}
		else if (type == this->Error)
		{

		}
		else
		{

		}
		(*clog) << "<" << label << ">" << message << "<!" << tail << ">" << std::endl;
	}

	ConsolePro& ConsolePro::LogMessage(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		// TODO: 在此处插入 return 语句
	}

	ConsolePro& ConsolePro::LogWarning(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		// TODO: 在此处插入 return 语句
	}

	ConsolePro& ConsolePro::LogError(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		// TODO: 在此处插入 return 语句
	}

	ConsolePro& ConsolePro::CoutMessage(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		// TODO: 在此处插入 return 语句
	}

	ConsolePro& ConsolePro::CoutWarning(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		// TODO: 在此处插入 return 语句
	}

	ConsolePro& ConsolePro::CoutError(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		// TODO: 在此处插入 return 语句
	}
}

