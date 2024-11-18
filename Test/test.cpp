#define _CRT_SECURE_NO_WARNINGS

#include<LightDiagram.h>
#include<llamakit.h>

using namespace ld;
//using namespace ld::resources;
using namespace std;

//sync_with_stdio_false(__auto__);

static void print_usage(int argc, char** argv) 
{
    printf("\nexample usage:\n");
    printf("\n    %s [-m=model.gguf] [-n=n_predict] [-ngl=n_gpu_layers] [-p=prompt]\n", argv[0]);
    printf("\n");
}

int llama_call(
    const char* model_path,
    int model_path_length,
    const char* prompt,
    int prompt_length,
    int ngl, 
    int n_predict)
{
#pragma region initialize the model

        
    llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = ngl;

    llama_model* model = llama_load_model_from_file(model_path, model_params);

    if (model == NULL) 
    {
        fprintf(stderr, "%s: error: unable to load model\n", __func__);
        return 1;
    }

#pragma endregion

#pragma region prompt


    // find the number of tokens in the prompt
    const int n_prompt = -llama_tokenize(model, prompt, prompt_length, NULL, 0, true, true);

    // allocate space for the tokens and tokenize the prompt
    std::vector<llama_token> prompt_tokens(n_prompt);
    if (llama_tokenize(
        model,
        prompt,
        prompt_length,
        prompt_tokens.data(),
        prompt_tokens.size(),
        true, 
        true) < 0) 
    {
        fprintf(stderr, "%s: error: failed to tokenize the prompt\n", __func__);
        return 1;
    }

#pragma endregion

#pragma region initialize the context
    
    llama_context_params ctx_params = llama_context_default_params();
    // n_ctx is the context size
    ctx_params.n_ctx = n_prompt + n_predict - 1;
    // n_batch is the maximum number of tokens that can be processed in a single call to llama_decode
    ctx_params.n_batch = n_prompt;
    // enable performance counters
    ctx_params.no_perf = false;

    llama_context* ctx = llama_new_context_with_model(model, ctx_params);

    if (ctx == NULL) {
        fprintf(stderr, "%s: error: failed to create the llama_context\n", __func__);
        return 1;
    }

#pragma endregion

#pragma region initialize the sampler

    auto sparams = llama_sampler_chain_default_params();
    sparams.no_perf = false;
    llama_sampler* smpl = llama_sampler_chain_init(sparams);

    llama_sampler_chain_add(smpl, llama_sampler_init_greedy());

#pragma endregion

#pragma region print the prompt token-by-token

    for (auto id : prompt_tokens) 
    {
        char buf[128];
        int n = llama_token_to_piece(model, id, buf, sizeof(buf), 0, true);
        if (n < 0) 
        {
            fprintf(stderr, "%s: error: failed to convert token to piece\n", __func__);
            return 1;
        }
        std::string s(buf, n);
        printf("%s", s.c_str());
    }

#pragma endregion

#pragma region prepare a batch for the prompt

    llama_batch batch = llama_batch_get_one(prompt_tokens.data(), prompt_tokens.size());

#pragma endregion

#pragma region main loop

    const auto t_main_start = ggml_time_us();
    int n_decode = 0;
    llama_token new_token_id;

    for (int n_pos = 0; n_pos + batch.n_tokens < n_prompt + n_predict; ) {
        // evaluate the current batch with the transformer model
        if (llama_decode(ctx, batch)) {
            fprintf(stderr, "%s : failed to eval, return code %d\n", __func__, 1);
            return 1;
        }

        n_pos += batch.n_tokens;

        // sample the next token
        {
            new_token_id = llama_sampler_sample(smpl, ctx, -1);

            // is it an end of generation?
            if (llama_token_is_eog(model, new_token_id)) {
                break;
            }

            char buf[128];
            int n = llama_token_to_piece(model, new_token_id, buf, sizeof(buf), 0, true);
            if (n < 0) {
                fprintf(stderr, "%s: error: failed to convert token to piece\n", __func__);
                return 1;
            }
            std::string s(buf, n);
            printf("%s", s.c_str());
            fflush(stdout);

            // prepare the next batch with the sampled token
            batch = llama_batch_get_one(&new_token_id, 1);

            n_decode += 1;
        }
    }

#pragma endregion

#pragma region end

    printf("\n");

    const auto t_main_end = ggml_time_us();

    fprintf(stderr, "%s: decoded %d tokens in %.2f s, speed: %.2f t/s\n",
        __func__, n_decode, (t_main_end - t_main_start) / 1000000.0f, n_decode / ((t_main_end - t_main_start) / 1000000.0f));

    fprintf(stderr, "\n");
    llama_perf_sampler_print(smpl);
    llama_perf_context_print(ctx);
    fprintf(stderr, "\n");

    llama_sampler_free(smpl);
    llama_free(ctx);
    llama_free_model(model);

    return 0;

#pragma endregion
}

int llama_ld_call(int argc, char** argv)
{
    // path to the model gguf file
    std::string model_path = "D:/LLM/MODELs/llama3-8B/Meta-Llama-3-8B-Instruct/Meta-Llama-3-8B-Instruct-Q4_0.gguf";
    // prompt to generate text from
    std::string prompt = "Hello my name is";
    // number of layers to offload to the GPU
    int ngl = 99;
    // number of tokens to predict
    int n_predict = 32;
    // parse command line arguments
    config_instance __config__(argc, argv);
    try
    {
        if (__config__.contains("-h") || __config__.contains("--help"))
        {
            print_usage(argc, argv);
            return 0;
        }
        if (__config__.detect_and_set("-m", model_path))
            console.LogWarning(Combine<string>("[model path]\t", model_path));
        if(__config__.detect_and_set("-n", ngl))
            console.LogWarning(Combine<string>("[n predict]\t", ngl));
        if(__config__.detect_and_set("-ngl", n_predict))
            console.LogWarning(Combine<string>("[n gpu layers]\t", n_predict));
        if(__config__.detect_and_set("-p", prompt))
            console.LogWarning(Combine<string>("[prompt]\t", prompt));
    }
    catch (exception ex)
    {
        console.LogError("error is happen:");
        console.LogError(ex.what());
        print_usage(argc, argv);
        return 0;
    }

    return llama_call(
        model_path.c_str(),
        model_path.size(),
        prompt.c_str(),
        prompt.size(),
        ngl, n_predict);

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

    model.print_prompt_token_by_token(tokens, [](const std::string& str) {cout << str; });
    auto batch = model.build_batch(tokens);

    model.main_loop(tokens, context, sampler, batch, n_predict, [](const std::string& str)
        {
            cout << str;
        });
    return 0;
}

int main(int argc, char** argv)
{
    llama_ld_call(argc, argv);
}