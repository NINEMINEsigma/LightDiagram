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

static void print_str(const char* str)
{
    cout << ConsoleColor::Blue << str;
}

int main(int argc, char** argv)
{
    // path to the model gguf file
    std::string model_path = "D:/LLM/MODELs/llama3-8B/Meta-Llama-3-8B-Instruct/Meta-Llama-3-8B-Instruct-Q4_0.gguf";
    // prompt to generate text from
    std::string prompt = "Who is you?";
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
        if (__config__.detect_and_set("-n", n_predict))
            console.LogWarning(Combine<string>("[n predict]\t", n_predict));
        if (__config__.detect_and_set("-ngl", ngl))
            console.LogWarning(Combine<string>("[n gpu layers]\t", ngl));
        if (__config__.detect_and_set("-p", prompt))
            console.LogWarning(Combine<string>("[prompt]\t", prompt));
    }
    catch (exception ex)
    {
        console.LogError("error is happen:");
        console.LogError(ex.what());
        print_usage(argc, argv);
        return 0;
    }
    llama_ld_call(model_path.c_str(),prompt.c_str(),n_predict, print_str);
}