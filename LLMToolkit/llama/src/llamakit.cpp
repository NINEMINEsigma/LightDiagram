#include"llamakit.h"

using namespace std;
using namespace ld;

int llama_ld_call(
    const char* model_path_cstr,
    const char* prompt_cstr,
    int n_predict_number,
    void (*callback)(const char*)
)
{
    std::function<void(const string&)> str_callback = [callback](const string& str)
        {
            callback(str.c_str());
        };

    // path to the model gguf file
    std::string model_path = model_path_cstr;
    // prompt to generate text from
    std::string prompt = prompt_cstr;
    // number of layers to offload to the GPU
    int ngl = 99;
    // number of tokens to predict
    int n_predict = n_predict_number;

    llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = ngl;
    instance<llama_model> model;
    model.init_instance(model_path, model_params);

    instance<llama_context> context;
    instance<llama_model>::llama_tokens_instance tokens = model.build_prompt_tokens(prompt);
    context.init_instance_and_build_context(model, tokens, n_predict);

    instance<llama_sampler> sampler{};
    sampler.init_default();

    //model.print_prompt_token_by_token(tokens, str_callback);
    auto batch = model.build_batch(tokens);

    model.main_loop(tokens, context, sampler, batch, n_predict, str_callback);
    return 0;
}

static map<map_index_t, instance<llama_model>> model_maper;
static map<map_index_t, instance<llama_sampler>> sampler_maper;

map_index_t LoadModel(
    const char* model_path, 
    struct llama_model_params params
)
{
    map_index_t index = model_maper.size();
    while (model_maper.count(index))
        index++;
    model_maper[index];
    model_maper[index].init_instance(model_path, params);
    return index;
}

map_index_t CreateSampler()
{
    map_index_t index = sampler_maper.size();
    while (sampler_maper.count(index))
        index++;
    sampler_maper[index];
    return index;
}

int LlamaPredict(
    map_index_t model_index,
    map_index_t sampler_index,
    const char* prompt_cstr,
    int n_predict_number,
    void (*callback)(const char*)
)
{
    std::function<void(const string&)> str_callback = [callback](const string& str)
        {
            callback(str.c_str());
        };

    // number of tokens to predict
    int n_predict = n_predict_number;

    if (model_maper.count(model_index) == 0)
        return -1;
    instance<llama_model> model = model_maper[model_index];

    instance<llama_context> context;
    instance<llama_model>::llama_tokens_instance tokens = model.build_prompt_tokens(prompt_cstr);
    context.init_instance_and_build_context(model, tokens, n_predict);

    map_index_t current_sampler_index = sampler_index;
    map_index_t sampler = CreateSampler();
    if (sampler_index >= 0 && sampler_maper.count(sampler_index))
    {
        sampler_maper[sampler_index].push(sampler_maper[sampler]);
        sampler = sampler_index;
    }
    else
    {
        sampler_maper[sampler].init_default();
    }

    auto batch = model.build_batch(tokens);

    model.main_loop(tokens, context, sampler_maper[sampler], batch, n_predict, str_callback);
    return sampler;
}