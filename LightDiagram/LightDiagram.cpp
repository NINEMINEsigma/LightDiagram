#include "LightDiagram.h"

ld_test::ld_test()
{
	std::cout << "ld test awake successful\n";
}

namespace ld
{
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
			throw message + "exception is not catch";
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

	IBase::IBase() {}
	IBase::IBase(const IBase&) {}
	IBase::~IBase() {}
	IBase& IBase::operator=(const IBase&) {}

	IBaseS::IBaseS(const type_info& type_id) :hash_bind_id(type_id) {}
	IBaseS::IBaseS(const IBaseS& right) :hash_bind_id(right.hash_bind_id) {}
	IBaseS::~IBaseS() {}
	IBaseS& IBaseS::operator=(const IBaseS& right)
	{
		if (hash_bind_id != right.hash_bind_id)
		{
			throw LDException("type is not match");
		}
		else
		{
			static_cast<IBase*>(this)->operator=(right);
		}
	}
	void IBaseS::ToMap(_Out_ IBaseMap* BM)
	{
		if (hash_bind_id != typeid(BM))
		{
			throw LDException("type is not match");
		}
		else
		{
			ToMapS(BM);
		}
	}
	bool IBaseS::FromMap(_In_ IBaseMap* from)
	{
		if (hash_bind_id != from->hash_bind_id)
		{
			throw LDException("type is not match");
		}
		else
		{
			return FromMapS(BM);
		}
	}
}
