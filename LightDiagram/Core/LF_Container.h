#ifndef __FILE_LF_CONTAINER
#define __FILE_LF_CONTAINER

#include<Core/LF_Config.h>
#include<Core/anyclass.h>
#include<Core/LF_RAII.h>

namespace ld
{
	namespace container
	{
		_LFramework_Indicator_Def(orderly, void, true);
		_LFramework_Indicator_Def(unordered, void, true);

		namespace orderly
		{
			template<typename _Ty,size_t _dimension>
			_LF_C_API(TClass) __orderly_container
			{
			public:
				using tag = typename choose_type<_dimension == 0, _Ty, __orderly_container<_Ty, (_dimension - 1)>>::tag;
				using indicators = type_list<container_indicator, orderly_indicator>;

			private:
				void* p_head;
				void* p_front;
				void* p_back;
				void* p_tail;
			public:

			};

		}

		namespace unordered
		{

		}
	}
}

#endif // !__FILE_LF_CONTAINER
