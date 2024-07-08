#include <Spack.h>

using namespace SparkChain;
using namespace std;
using namespace llm::Spark;

#pragma comment(lib, "F:/source/2024/LightDiagram/LLMToolkit/Windows/Spark/3.5/v1.1/libs/x64/SparkChain.lib") 

Callback::Callback() {}
Callback::~Callback() {}
void Callback::onLLMResult(LLMResult* result, void* usrContext)
{
	this->all_result += result->getContent();
	this->OnEnd(all_result.c_str(), result);
}
void Callback::onLLMEvent(LLMEvent* event, void* usrContext)
{
	this->OnProcess(event->getEventMsg(), event);
}
void Callback::onLLMError(LLMError* error, void* usrContext)
{
	this->OnError(error->getErrMsg(), error);
}

void LLMSystem::Init() {}
LLMSystem::LLMSystem() :maxCache(5), domain("generalv3.5"), url("ws(s)://spark-api.xf-yun.com/v3.5/chat") {}
void LLMSystem::InitSDK(const char* appID, const char* apiKey, const char* apiSecret)
{
	this->config = SparkChainConfig::builder();
	config->appID(appID)->apiKey(apiKey)->apiSecret(apiSecret);
	this->init_result = SparkChain::init(config);
}
void LLMSystem::UnInitSDK()
{
	SparkChain::unInit();
}
LLMSystem::LLMSystem(const char* appID, const char* apiKey, const char* apiSecret) :LLMSystem()
{
	this->InitSDK(appID, apiKey, apiSecret);
}
LLMSystem::~LLMSystem()
{
	this->UnInitSDK();
}
LLMSystem::operator bool() const
{
	return this->init_result == 0;
}
void LLMSystem::SetupModel(const string& _domain, const string& _url, const int _maxCache)
{
	this->domain = _domain;
	this->url = _url;
	this->maxCache = _maxCache;
}

void LLMSystem::SyncSend(const string& message)
{
	LLMConfig* llmConfig = LLMConfig::builder();
	llmConfig->domain(this->domain.c_str())->url(this->url.c_str());

	Memory* window_memory = Memory::WindowMemory(this->maxCache);
	LLM* syncllm = LLM::create(llmConfig, window_memory);
	// Memory* token_memory = Memory::TokenMemory(500);
	// LLM *syncllm = LLM::create(llmConfig,token_memory);
	LLMSyncOutput* result = syncllm->run(message.c_str());
	if (result->getErrCode() != 0)
	{
		this->callback.OnError.OnInvoke(result->getErrMsg(), dynamic_cast<LLMError*>(result));
	}
	else
	{
		this->callback.OnEnd.OnInvoke(result->getContent(), dynamic_cast<LLMResult*>(result));
	}
	if (syncllm != nullptr)
		SparkChain::LLM::destroy(syncllm);
}

void LLMSystem::AsyncSend(const string& message, int user, int wait_clock_time, int wait_max_time)
{
	LLMConfig* llmConfig = LLMConfig::builder();
	llmConfig->domain(this->domain.c_str())->url(this->url.c_str());

	Memory* window_memory = Memory::WindowMemory(this->maxCache);
	LLM* asyncllm = LLM::create(llmConfig, window_memory);
	// Memory* token_memory = Memory::TokenMemory(500);
	// LLM *asyncllm = LLM::create(llmConfig,token_memory);
	if (asyncllm == nullptr)
	{
		this->callback.OnEnd.OnInvoke("fail, please setLLMConfig before", nullptr);
		return;
	}
	asyncllm->registerLLMCallbacks(&this->callback);
	this->async_finish = false;
	int ret = asyncllm->arun(message.c_str(), &user);
	do
	{
		if (ret != 0)
		{
			this->callback.OnError.OnInvoke((string("AsyncSend failed: ") + to_string(ret)).c_str(), nullptr);
			continue;
		}
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		while (duration.count() < wait_max_time)
		{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
			Sleep(wait_clock_time);
#else 
			sleep(wait_clock_time);
#endif
			if (this->async_finish)break;
			end = std::chrono::steady_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		}
	} while (false);
	if (asyncllm != nullptr)
		LLM::destroy(asyncllm);
}
