#include "LLM/Spark.h"

using namespace SparkChain;
using namespace std;
using namespace llm::Spark;

//#pragma comment(lib, "F:/source/2024/LightDiagram/LLMToolkit/Windows/Spark/3.5/v1.1/libs/x64/SparkChain.lib") 

LLMArchitecture::~LLMArchitecture() {}

Callback::Callback() {}
Callback::~Callback() {}
void Callback::onLLMResult(LLMResult* result, void* usrContext)
{
	this->all_result += result->getContent();
	this->OnEnd(result->getContent(), result);
}
void Callback::onLLMEvent(LLMEvent* event, void* usrContext)
{
	this->OnEvent(event->getEventMsg(), event);
}
void Callback::onLLMError(LLMError* error, void* usrContext)
{
	this->OnError(error->getErrMsg(), error);
}

static LLMSystem* initer_ptr = nullptr;

void LLMSystem::Init()
{
	auto* llmarch = this->Architecture()->AsDynamicPtr<LLMArchitecture>();
	if (llmarch != nullptr)
		this->InitSDK(llmarch->appID.c_str(), llmarch->apiKey.c_str(), llmarch->apiSecret.c_str());
}
LLMSystem::LLMSystem() :async_finish(true), init_result(-1), maxCache(5), domain("generalv3.5"), url("ws(s)://spark-api.xf-yun.com/v3.5/chat")
{

}
bool LLMSystem::InitSDK(const char* appID, const char* apiKey, const char* apiSecret)
{
	if (initer_ptr == this)
	{
		this->UnInitSDK();
	}
	if (initer_ptr == nullptr)
	{
		auto* config = SparkChainConfig::builder();
		config->appID(appID)->apiKey(apiKey)->apiSecret(apiSecret);
		this->init_result = SparkChain::init(config);
		initer_ptr = this;
		return this->init_result == 0;
	}
	else return false;
}
void LLMSystem::UnInitSDK()
{
	SparkChain::unInit();
	initer_ptr = nullptr;
	this->init_result = -1;
}
LLMSystem::LLMSystem(const char* appID, const char* apiKey, const char* apiSecret) :LLMSystem()
{
	this->InitSDK(appID, apiKey, apiSecret);
}
LLMSystem::~LLMSystem() {}
static void __DeleteLLMSystem(ld::IAnyArchitecture* r)
{
	r->AsDynamicPtr<LLMSystem>()->UnInitSDK();
};
ld::IAnyArchitecture::DestroyAction LLMSystem::WithDestroy() const
{
	return __DeleteLLMSystem;
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

LLMSystem::AsyncEndCallback LLMSystem::AsyncSend(const string& message, int user)
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
		return AsyncEndCallback([](LLM* llmptr) {}, std::move(asyncllm));
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
	} while (false);
	return AsyncEndCallback([](LLM* llmptr)
		{
			if (llmptr != nullptr)
				LLM::destroy(llmptr);
		}, std::move(asyncllm));
}
