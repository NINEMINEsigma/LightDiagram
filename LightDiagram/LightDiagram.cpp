#include "LightDiagram.h"

ld_test::ld_test()
{
	std::cout << "ld test awake successful\n";
}

namespace ld
{
#ifndef _CUSTOM_CLOG
	std::ofstream clog;
#endif // !_CUSTOM_CLOG

	LDException::LDException(const time_t& ts, const string& msg)
		:message(string(ctime(&ts)) + ":\t" + message), counter(new int(1)) {}
	LDException::LDException() :LDException("unknown") {}
	LDException::LDException(const string& msg) :LDException(time(nullptr), msg) {}
	LDException::LDException(LDException& ex) noexcept :counter(ex.counter) { (*counter)++; }
	LDException::LDException(LDException&& ex) noexcept :counter(ex.counter) { ex.counter = nullptr; }
	LDException::~LDException()
	{
		if (counter == nullptr)return;
		if (*counter > 0)
		{
			(*counter)--;
			clog << "[lose ]" << message << "\n";
			std::cerr << message + "exception is not catch";
		}
		else
		{
			clog << "[catch]" << message << "\n";
			delete counter;
		}
	}
	void LDException::release() const noexcept
	{
		(*counter)--;
	}
}
