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

    instance<llama_sampler> sampler;
    auto sparams = llama_sampler_chain_default_params();
    sparams.no_perf = false;
    sampler.init_instance(sparams);

    //model.print_prompt_token_by_token(tokens, str_callback);
    auto batch = model.build_batch(tokens);

    model.main_loop(tokens, context, sampler, batch, n_predict, str_callback);
    return 0;
}