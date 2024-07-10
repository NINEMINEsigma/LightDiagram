#ifndef __FILE_SPACK
#define __FILE_SPACK
#include <LightDiagram.h>
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
#include <../LLMToolkit/Windows/Spark/3.5/v1.1/include/sparkchain.h>
#include <../LLMToolkit/Windows/Spark/3.5/v1.1/include/sc_llm.h>
#else
#include <../LLMToolkit/Linux/Spark/3.5/v1.1/include/sparkchain.h>
#include <../LLMToolkit/Linux/Spark/3.5/v1.1/include/sc_llm.h>
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
			Callback(Callback & right) = delete;
			Callback(Callback && right) = delete;
			virtual ~Callback();
			virtual void onLLMResult(LLMResult * result, void* usrContext) override;
			virtual void onLLMEvent(LLMEvent * event, void* usrContext) override;
			virtual void onLLMError(LLMError * error, void* usrContext) override;
			using OnEndCallbackAction = ld::LDEvent<void(const char*, LLMResult*)>;
			using OnProcessCallbackAction = ld::LDEvent<void(const char*, LLMEvent*)>;
			using OnErrorCallbackAction = ld::LDEvent<void(const char*, LLMError*)>;
			OnEndCallbackAction OnEnd;
			OnProcessCallbackAction OnEvent;
			OnErrorCallbackAction OnError;
			std::string all_result;
		private:
		};

		_LF_C_API(Class)
			LLMSystem : _LF_Inherited(ld::ISystem)
		{
		public:
			bool InitSDK(const char* appID, const char* apiKey, const char* apiSecret);
			void UnInitSDK();
			using string = std::string;
			LLMSystem();
			LLMSystem(const char* appID, const char* apiKey, const char* apiSecret);
			virtual ~LLMSystem();
			LLMSystem(LLMSystem&) = delete;
			LLMSystem(LLMSystem&&) = delete;
			virtual void Init() override;
			int init_result;
			string domain, url;
			void SetupModel(const string & _domain, const string & _url,const int _maxCache);
			operator bool() const;
			Callback callback;
			void SyncSend(const string & message);
			using AsyncEndCallback = closures<void(SparkChain::LLM*), SparkChain::LLM*>;
			AsyncEndCallback AsyncSend(const string & message,int user);
			int maxCache;
			bool async_finish;
			IAnyArchitecture::DestroyAction WithDestroy() const override;
		};

		_LF_C_API(Class)
			LLMArchitecture : _LF_Inherited(ld::IArchitecture)
		{
		public:
			virtual ~LLMArchitecture();
			std::string appID;
			std::string apiKey;
			std::string apiSecret;
		};

		/*
		
	llmConfig->domain("generalv3.5");
	llmConfig->url("ws(s)://spark-api.xf-yun.com/v3.5/chat");
		
	config->appID("1555396e")        // ÄãµÄappid
		->apiKey("5ed9018f67a8c1a2ee5cede10cc405d5")        // ÄãµÄapikey
		->apiSecret("ODUyNDBlNjllNTE4OTQzNzQ1YzVhNWY0"); // ÄãµÄapisecret
		
		*/
	}
}

#endif // !__FILE_SPACK
