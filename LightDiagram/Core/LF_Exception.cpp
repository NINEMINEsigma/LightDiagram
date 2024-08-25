#include<Core/LF_Exception.h>

namespace ld
{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
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

#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
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
	std::ostream& operator<< (std::ostream& os, const ConsoleColor& data)
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetColorCode(data));
#else 
		std::cout << to_string(GetColorCode(data));
#endif

		return os;
	}

	// Operator overloading for console background color
	std::ostream& operator<< (std::ostream& os, const ConsoleBackgroundColor& data)
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetBackgroundColorCode(data));
#else 
		std::cout << to_string(GetBackgroundColorCode(data));
#endif

		return os;
	}

	// Operator overloading for console text color
	std::wostream& operator<< (std::wostream& os, const ConsoleColor& data)
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetColorCode(data));
#else 
		std::wcout << GetColorCode(data);
#endif

		return os;
	}

	// Operator overloading for console background color
	std::wostream& operator<< (std::wostream& os, const ConsoleBackgroundColor& data)
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, GetBackgroundColorCode(data));
#else 
		std::wcout << GetBackgroundColorCode(data);
#endif

		return os;
	}

	class clog_init_helper
	{
	public:
		clog_init_helper()
		{
			ld::clog->imbue(std::locale(ld::clog->getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
		}
	};

	std::ostream* clog = new std::ofstream("./line exception.txt");
	static clog_init_helper __clog_init_helper;

	bool is_log_message_to_cout = true;

	LDException::LDException(const time_t& ts, const std::string& msg) :
		message(msg),
		counter(new int(1)),
		is_release(new bool(false)) {}
	LDException::LDException() :LDException("unknown") {}
	LDException::LDException(const string& msg) :LDException(time(nullptr), msg) {}
	LDException::LDException(const std::wstring& msg) :LDException(time(nullptr), to_string(msg)) {}
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
#ifdef _DEBUG
			if (is_log_message_to_cout)
			{
				std::cout
					<< ConsoleColor::Red
					<< message
					<< ConsoleColor::None << std::endl;
			}
#endif // _DEBUG
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
			(*clog) << "<catch>" << message << "L<!exception is catch>" << std::endl;
#ifdef _DEBUG
			if (is_log_message_to_cout)
			{
				std::cout
					<< ConsoleColor::Yellow
					<< message
					<< ConsoleColor::None << std::endl;
			}
#endif // _DEBUG
		}
	}

	//  Ease Progress Bar
	void    _LF_C_API(DLL)  EaseProgressBar(double t, int length, ConsoleBackgroundColor color)
	{
		std::cout << color;
		for (int i = 0, e = static_cast<int>(t * length); i < e; i++)
		{
			std::cout << " ";
		}
		std::cout << ConsoleBackgroundColor::None;
		for (int i = static_cast<int>(t * length); i <= length; i++)
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

	ConsolePro::ConsolePro()
		: Message(0), Warning(1), Error(2), FC(ConsoleColor::None), BC(ConsoleBackgroundColor::None) {}
	ConsolePro::ConsolePro(const ConsolePro& from)
		: Message(from.Message), Warning(from.Warning), Error(from.Error), FC(from.FC), BC(from.BC) {}
	ConsolePro::~ConsolePro() {}

	const ConsolePro& ConsolePro::Log(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail, const ConsolePro::symbol_t& type) const
	{
		if (is_log_message_to_cout)
		{
			if (type == this->Warning)
				std::cout << ConsoleColor::Yellow << message << std::endl << this->FC;
			else if (type == this->Error)
				std::cout << ConsoleColor::Red << message << std::endl << this->FC;
			else if (type == this->Message)
				std::cout << ConsoleColor::Blue << message << std::endl << this->FC;
			else
				std::cout << message << std::endl;
		}
		(*clog) << "<" << (label) << ">" << (message) << "<!" << (tail) << ">" << std::endl;
		return *this;
	}
	const ConsolePro& ConsolePro::LogMessage(const ConsolePro::string& message ) const
	{
		static ConsolePro::string label("message");
		return Log(message, label, label, this->Message);
	}
	const ConsolePro& ConsolePro::LogWarning(const ConsolePro::string& message) const
	{
		static ConsolePro::string label("warning");
		return Log(message, label, label, this->Warning);
	}
	const ConsolePro& ConsolePro::LogError(const ConsolePro::string& message) const
	{
		static ConsolePro::string label("error");
		return Log(message, label, label, this->Error);
	}
	const ConsolePro& ConsolePro::CoutMessage(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		std::cout << ConsoleColor::Blue << "<" << label << ">" << message << "<!" << tail << ">" << this->FC << std::endl;
		return *this;
	}
	const ConsolePro& ConsolePro::CoutWarning(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		std::cout << ConsoleColor::Yellow << "<" << label << ">" << message << "<!" << tail << ">" << this->FC << std::endl;
		return *this;
	}
	const ConsolePro& ConsolePro::CoutError(const ConsolePro::string& message, const ConsolePro::string& label, const ConsolePro::string& tail) const
	{
		std::cout << ConsoleColor::Red << "<" << label << ">" << message << "<!" << tail << ">" << this->FC << std::endl;
		return *this;
	}

	const ConsolePro& ConsolePro::CoutMessage(const ConsolePro::string& message) const
	{
		static ConsolePro::string label("message");
		return CoutMessage(message, label, label);
	}
	const ConsolePro& ConsolePro::CoutWarning(const ConsolePro::string& message) const
	{
		static ConsolePro::string label("warning");
		return CoutWarning(message, label, label);
	}
	const ConsolePro& ConsolePro::CoutError(const ConsolePro::string& message) const
	{
		static ConsolePro::string label("error");
		return CoutError(message, label, label);
	}

	const ConsolePro& ConsolePro::Log(const ConsolePro::wstring& message, const ConsolePro::wstring& label, const ConsolePro::wstring& tail, const ConsolePro::symbol_t& type) const
	{
		if (is_log_message_to_cout)
		{
			if (type == this->Warning)
				std::wcout << ConsoleColor::Yellow << message << std::endl << this->FC;
			else if (type == this->Error)
				std::wcout << ConsoleColor::Red << message << std::endl << this->FC;
			else if (type == this->Message)
				std::wcout << ConsoleColor::Blue << message << std::endl << this->FC;
			else
				std::wcout << message << std::endl;
		}
		(*clog) << "<" << to_string(label) << ">" << to_string(message) << "<!" << to_string(tail) << ">" << std::endl;
		return *this;
	}

	const ConsolePro& ConsolePro::LogMessage(const ConsolePro::wstring& message) const
	{
		static ConsolePro::wstring label(L"message");
		return Log(message, label, label, this->Message);
	}
	const ConsolePro& ConsolePro::LogWarning(const ConsolePro::wstring& message) const
	{
		static ConsolePro::wstring label(L"warning");
		return Log(message, label, label, this->Warning);
	}
	const ConsolePro& ConsolePro::LogError(const ConsolePro::wstring& message) const
	{
		static ConsolePro::wstring label(L"error");
		return Log(message, label, label, this->Error);
	}
	const ConsolePro& ConsolePro::WcoutMessage(const ConsolePro::wstring& message, const ConsolePro::wstring& label, const ConsolePro::wstring& tail) const
	{
		std::wcout << ConsoleColor::Blue << L"<" << label << L">" << message << L"<!" << tail << L">" << this->FC << std::endl;
		return *this;
	}
	const ConsolePro& ConsolePro::WcoutWarning(const ConsolePro::wstring& message, const ConsolePro::wstring& label, const ConsolePro::wstring& tail) const
	{
		std::wcout << ConsoleColor::Yellow << L"<" << label << L">" << message << L"<!" << tail << L">" << this->FC << std::endl;
		return *this;
	}
	const ConsolePro& ConsolePro::WcoutError(const ConsolePro::wstring& message, const ConsolePro::wstring& label, const ConsolePro::wstring& tail) const
	{
		std::wcout << ConsoleColor::Red << L"<" << label << L">" << message << L"<!" << tail << L">" << this->FC << std::endl;
		return *this;
	}
								  
	const ConsolePro& ConsolePro::WcoutMessage(const ConsolePro::wstring& message) const
	{
		static ConsolePro::wstring label(L"message");
		return WcoutMessage(message, label, label);
	}
	const ConsolePro& ConsolePro::WcoutWarning(const ConsolePro::wstring& message) const
	{
		static ConsolePro::wstring label(L"warning");
		return WcoutWarning(message, label, label);
	}
	const ConsolePro& ConsolePro::WcoutError(const ConsolePro::wstring& message) const
	{
		static ConsolePro::wstring label(L"error");
		return WcoutError(message, label, label);
	}
}

ld::ConsolePro console;


