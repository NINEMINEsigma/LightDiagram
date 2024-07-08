#ifndef __FILE_SPACK
#define __FILE_SPACK
#include <LightDiagram.h>
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
#include <Windows/Spark/3.5/v1.1/include/sparkchain.h>
#include <Windows/Spark/3.5/v1.1/include/sc_llm.h>
#else
#include <Linux/Spark/3.5/v1.1/include/sparkchain.h>
#include <Linux/Spark/3.5/v1.1/include/sc_llm.h>
#endif

namespace llm
{
	namespace Spark
	{
		using namespace SparkChain;

		_LF_C_API(Class)
			Callback :
		public LLMCallbacks Symbol_Link
			_LF_Inherited(any_class)
		{
		public:
			Callback();
			Callback(Callback & right) noexcept;
			Callback(Callback && right) noexcept;
			virtual ~Callback();
			virtual void onLLMResult(LLMResult * result, void* usrContext) override;
			virtual void onLLMEvent(LLMEvent * event, void* usrContext) override;
			virtual void onLLMError(LLMError * error, void* usrContext) override;
			using OnEndCallbackAction = std::function<void(const char*, LLMResult*)>;
			using OnProcessCallbackAction = std::function<void(const char*, LLMEvent*)>;
			using OnErrorCallbackAction = std::function<void(const char*, LLMError*)>;
			OnEndCallbackAction OnEnd;
			OnProcessCallbackAction OnProcess;
			OnErrorCallbackAction OnError;
		private:
			std::string all_result;
		};
	}
}

#endif // !__FILE_SPACK
