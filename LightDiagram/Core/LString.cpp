#include<Core/LString.h>

using namespace std;

namespace ld
{
	using string_index = size_t;
	using string_char = size_t;
	class LStringImpl
	{
	public:
		string_index forward_index = 0;
		string_char char_data = 0;
		size_t str_length = 0;
		size_t char_length = sizeof(char);
	};

	static map<string_index, LStringImpl> LStringImplMapper;
	static map<string_char, set<string_index>> R_LStringImplMapper;
	static atomic<size_t> ImplCounter = 0;
	static mutex ImplMutex;

	//build string from lstring
	void LStringImpl2LStringVec(string_index head, stack<string_char>& result)
	{
		if (LStringImplMapper.count(head))
		{
			auto& current = LStringImplMapper[head];
			result.push(current.char_data);
			LStringImpl2LStringVec(current.forward_index, result);
		}
		else if (head == 0)
		{
			return;
		}
		else
		{
			throw LDException("string has been release or never exist");
		}
	}
	//build string from lstring
	stack<string_char> LStringImpl2LStringVec(string_index head)
	{
		stack<string_char> result;
		LStringImpl2LStringVec(head, result);
		return result;
	}
	//build string from lstring
	template<typename _StrChar>
	auto LString2String(string_index head)
	{
		lock_guard lgx(ImplMutex);
		using result_string = std::basic_string<_StrChar>;
		auto str_vec = LStringImpl2LStringVec(head);
		result_string result(str_vec.size(), '\0');
		for (size_t i = 0, e = str_vec.size(); i < e; i++)
		{
			result[i] = static_cast<_StrChar>(str_vec.top());
			str_vec.pop();
		}
		return result;
	}
	//build lstring from string
	void LStringVec2LStringImpl(string_index& current, stack<string_char>& vec)
	{
		if (vec.size() == 0)
		{
			return;
		}
		else if (current == 0)
		{
			string_char topch = vec.top();

		}
		else
		{
			return;
		}
	}
	//build lstring from string
	string_index LStringVec2LStringImpl(stack<string_char>& vec)
	{
		string_index result = 0;
		LStringVec2LStringImpl(result, vec);
		return result;
	}
	//build lstring from string
	template<typename _StrChar>
	string_index String2LString(const std::basic_string<_StrChar>& str)
	{
		lock_guard lgx(ImplMutex);
		stack<string_char> vec;
		for (auto i = str.rbegin(), e = str.rend(); i != e; i++)
		{
			vec.push(static_cast<string_char>(*i));
		}
		return LStringVec2LStringImpl(vec);
	}

	LString::LString(const std::string& str) :u_index(String2LString(str)) {}
	LString::LString(const std::wstring& wstr) :u_index(String2LString(wstr)) {}
	LString::LString(const LString& from) noexcept : u_index(from.u_index) {}
	LString& LString::operator=(const LString& from) noexcept
	{
		this->u_index = from.u_index;
		return *this;
	}
	LString::~LString()
	{

	}

	LString::operator std::string() const
	{
		return ToString();
	}


	bool LString::operator==(const LString& from) noexcept
	{
#ifdef _DEBUG
		auto mstr = LString2String<string_char>(u_index);
		auto tstr = LString2String<string_char>(from.u_index);
		if ((mstr == tstr) && (this->u_index != from.u_index))
			throw LDException(go_string(__func__, ": error: u_index is bad equals"));
#endif // _DEBUG
		return this->u_index == from.u_index;
	}

	string LString::ToString() const
	{
		return LString2String<char>(u_index);
	}
	wstring LString::ToWString() const
	{
		return LString2String<wchar_t>(u_index);
	}

	void LString::ReSetMemory()
	{
		LStringImplMapper.clear();
		R_LStringImplMapper.clear();
	}
}

namespace std
{
	std::string to_string(const ld::LString& str)
	{
		return str.ToString();
	}
}