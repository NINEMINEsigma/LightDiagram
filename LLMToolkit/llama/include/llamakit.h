#ifndef __FILE_LLAMA_KIT
#define __FILE_LLAMA_KIT

#include"llama.h"
#include<Core/LF_RAII.h>

namespace ld
{
    template<>
    _LF_C_API(Class) instance<llama_sampler> : public instance<void>
    {
    public:
        using tag = llama_sampler;
    private:
        tag* instance_ptr;
        void destruct_and_free_instance_ptr()
        {
            if (instance_ptr == nullptr)
                return;
            llama_sampler_free(instance_ptr);
            instance_ptr = nullptr;
        }
        //build up instance by outside-ptr
        instance(tag* ptr) : instance_ptr(ptr), instance<void>() {}
    public:
        //build up instance
        instance() noexcept : instance(nullptr) {}
        //build up instance by copy left-value instance
        instance(instance& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(from) {}
        //build up instance by move right-value instance
        instance(instance&& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(std::move(from))
        {
            from.instance_ptr = nullptr;
        }
        //build up instance by copy left-value(const) instance
        instance(const instance& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(from) {}
        virtual ~instance()
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
        }
        //get real address
        constexpr tag* get_ptr() const noexcept
        {
            return instance_ptr;
        }
        //get instance reference, not check
        tag& get_ref() const
        {
            return *instance_ptr;
        }
        //to read address
        constexpr tag* operator->() const
        {
            return instance_ptr;
        }
        //swap instance-ptr and instance-counter
        void swap(instance<tag>& from)noexcept
        {
            instance<void>::swap(from);
            std::swap(this->instance_ptr, from.instance_ptr);
        }
        //swap instance-ptr and instance-counter
        void swap(instance<tag>&& from)noexcept
        {
            instance<void>::swap(std::move(from));
            std::swap(this->instance_ptr, from.instance_ptr);
        }
        //set up instance by left-value copy operator
        instance<tag>& operator=(instance<tag>& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(from);
            this->instance_ptr = from.instance_ptr;
            return *this;
        }
        //set up instance by right-value move operator
        instance<tag>& operator=(instance<tag>&& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(std::move(from));
            this->instance_ptr = from.instance_ptr;
            from.instance_ptr = nullptr;
            return *this;
        }
        //set up instance by left-value copy operator
        instance<tag>& operator=(const instance<tag>& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(from);
            this->instance_ptr = from.instance_ptr;
            return *this;
        }
        //is instance same one
        bool operator==(const instance<tag>& from) const noexcept
        {
            return instance<void>::operator==(from);
        }
        //is instance same one
        bool equals(const instance<tag>& from) const noexcept
        {
            return instance<void>::operator==(from);
        }
        //is instance empty
        bool equals(nullptr_t) const noexcept
        {
            return this->instance_ptr == nullptr;
        }
        //is instance real address same with target
        bool equals(tag* from) const noexcept
        {
            return this->instance_ptr == from;
        }

        operator tag& ()
        {
            return this->get_ref();
        }
        operator bool()
        {
            return !this->empty();
        }

        //is instance reference exist
        virtual bool empty() const override
        {
            return this->instance_ptr == nullptr;
        }

        virtual std::string SymbolName() const override
        {
            return "llama-instance";
        }
        virtual std::string ToString() const override
        {
            return "llama-instance";
        }

        void init_instance(llama_sampler_chain_params params)
        {
            instance_ptr = llama_sampler_chain_init(params);
            llama_sampler_chain_add(instance_ptr, llama_sampler_init_greedy());
        }

        void sampler_print() const
        {
            llama_perf_sampler_print(instance_ptr);
        }

        constexpr operator tag* ()
        {
            return instance_ptr;
        }
    };

    template<>
    _LF_C_API(Class) instance<llama_context> : public instance<void>
    {
    public:
        using tag = llama_context;
    private:
        tag* instance_ptr;
        void destruct_and_free_instance_ptr()
        {
            if (instance_ptr == nullptr)
                return;
            llama_free(instance_ptr);
            instance_ptr = nullptr;
        }
        //build up instance by outside-ptr
        instance(tag* ptr) : instance_ptr(ptr), instance<void>() {}
    public:
        //build up instance
        instance() noexcept : instance(nullptr) {}
        //build up instance by copy left-value instance
        instance(instance& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(from) {}
        //build up instance by move right-value instance
        instance(instance&& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(std::move(from))
        {
            from.instance_ptr = nullptr;
        }
        //build up instance by copy left-value(const) instance
        instance(const instance& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(from) {}
        virtual ~instance()
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
        }
        //get real address
        constexpr tag* get_ptr() const noexcept
        {
            return instance_ptr;
        }
        //get instance reference, not check
        tag& get_ref() const
        {
            return *instance_ptr;
        }
        //to read address
        constexpr tag* operator->() const
        {
            return instance_ptr;
        }
        //swap instance-ptr and instance-counter
        void swap(instance<tag>& from)noexcept
        {
            instance<void>::swap(from);
            std::swap(this->instance_ptr, from.instance_ptr);
        }
        //swap instance-ptr and instance-counter
        void swap(instance<tag>&& from)noexcept
        {
            instance<void>::swap(std::move(from));
            std::swap(this->instance_ptr, from.instance_ptr);
        }
        //set up instance by left-value copy operator
        instance<tag>& operator=(instance<tag>& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(from);
            this->instance_ptr = from.instance_ptr;
            return *this;
        }
        //set up instance by right-value move operator
        instance<tag>& operator=(instance<tag>&& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(std::move(from));
            this->instance_ptr = from.instance_ptr;
            from.instance_ptr = nullptr;
            return *this;
        }
        //set up instance by left-value copy operator
        instance<tag>& operator=(const instance<tag>& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(from);
            this->instance_ptr = from.instance_ptr;
            return *this;
        }
        //is instance same one
        bool operator==(const instance<tag>& from) const noexcept
        {
            return instance<void>::operator==(from);
        }
        //is instance same one
        bool equals(const instance<tag>& from) const noexcept
        {
            return instance<void>::operator==(from);
        }
        //is instance empty
        bool equals(nullptr_t) const noexcept
        {
            return this->instance_ptr == nullptr;
        }
        //is instance real address same with target
        bool equals(tag* from) const noexcept
        {
            return this->instance_ptr == from;
        }

        operator tag& ()
        {
            return this->get_ref();
        }
        operator bool()
        {
            return !this->empty();
        }

        //is instance reference exist
        virtual bool empty() const override
        {
            return this->instance_ptr == nullptr;
        }

        virtual std::string SymbolName() const override
        {
            return "llama-instance";
        }
        virtual std::string ToString() const override
        {
            return "llama-instance";
        }

        void init_instance(llama_model* model, llama_context_params params)
        {
            instance_ptr = llama_new_context_with_model(model, params);
            if (instance_ptr == nullptr)
            {
                throw LDException("error: failed to create the llama_context");
            }
        }
        void init_instance(llama_model* model)
        {
            init_instance(model, llama_context_default_params());
        }

        using llama_tokens_instance = instance<std::vector<llama_token>>;

        // build up prompt token and init instance with default params
        void init_instance_and_build_context(
            llama_model* model,
            llama_tokens_instance prompt_tokens,
            int n_predict)
        {
            llama_context_params ctx_params = llama_context_default_params();
            int n_prompt = prompt_tokens->size();
            // n_ctx is the context size
            ctx_params.n_ctx = n_prompt + n_predict - 1;
            // n_batch is the maximum number of tokens that can be processed in a single call to llama_decode
            ctx_params.n_batch = n_prompt;
            // enable performance counters
            ctx_params.no_perf = false;

            // init
            init_instance(model, ctx_params);
        }

        void context_print() const
        {
            llama_perf_context_print(instance_ptr);
        }

        constexpr operator tag* ()
        {
            return instance_ptr;
        }
    };

    template<>
    _LF_C_API(Class) instance<llama_model> : public instance<void>
    {
    public:
        using tag = llama_model;
    private:
        tag* instance_ptr;
        void destruct_and_free_instance_ptr()
        {
            if (instance_ptr == nullptr)
                return;
            llama_free_model(instance_ptr);
            instance_ptr = nullptr;
        }
        //build up instance by outside-ptr
        instance(tag* ptr) : instance_ptr(ptr), instance<void>() {}
    public:
        //build up instance
        instance() noexcept : instance(nullptr) {}
        //build up instance by copy left-value instance
        instance(instance& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(from) {}
        //build up instance by move right-value instance
        instance(instance&& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(std::move(from))
        {
            from.instance_ptr = nullptr;
        }
        //build up instance by copy left-value(const) instance
        instance(const instance& from) noexcept : instance_ptr(from.instance_ptr), instance<void>(from) {}
        virtual ~instance()
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
        }
        //get real address
        constexpr tag* get_ptr() const noexcept
        {
            return instance_ptr;
        }
        //get instance reference, not check
        tag& get_ref() const
        {
            return *instance_ptr;
        }
        //to read address
        constexpr tag* operator->() const
        {
            return instance_ptr;
        }
        //swap instance-ptr and instance-counter
        void swap(instance<tag>& from)noexcept
        {
            instance<void>::swap(from);
            std::swap(this->instance_ptr, from.instance_ptr);
        }
        //swap instance-ptr and instance-counter
        void swap(instance<tag>&& from)noexcept
        {
            instance<void>::swap(std::move(from));
            std::swap(this->instance_ptr, from.instance_ptr);
        }
        //set up instance by left-value copy operator
        instance<tag>& operator=(instance<tag>& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(from);
            this->instance_ptr = from.instance_ptr;
            return *this;
        }
        //set up instance by right-value move operator
        instance<tag>& operator=(instance<tag>&& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(std::move(from));
            this->instance_ptr = from.instance_ptr;
            from.instance_ptr = nullptr;
            return *this;
        }
        //set up instance by left-value copy operator
        instance<tag>& operator=(const instance<tag>& from) noexcept
        {
            if (this->get_count() <= 1)
            {
                destruct_and_free_instance_ptr();
            }
            instance<void>::operator=(from);
            this->instance_ptr = from.instance_ptr;
            return *this;
        }
        //is instance same one
        bool operator==(const instance<tag>& from) const noexcept
        {
            return instance<void>::operator==(from);
        }
        //is instance same one
        bool equals(const instance<tag>& from) const noexcept
        {
            return instance<void>::operator==(from);
        }
        //is instance empty
        bool equals(nullptr_t) const noexcept
        {
            return this->instance_ptr == nullptr;
        }
        //is instance real address same with target
        bool equals(tag* from) const noexcept
        {
            return this->instance_ptr == from;
        }

        operator tag& ()
        {
            return this->get_ref();
        }
        operator bool()
        {
            return !this->empty();
        }

        //is instance reference exist
        virtual bool empty() const override
        {
            return this->instance_ptr == nullptr;
        }

        virtual std::string SymbolName() const override
        {
            return "llama-instance";
        }
        virtual std::string ToString() const override
        {
            return "llama-instance";
        }

        //init env first
        void init_instance(const std::string& model_path, llama_model_params params)
        {
            instance_ptr = llama_load_model_from_file(model_path.c_str(), params);
            if (instance_ptr == nullptr)
            {
                throw LDException("error: unable to load model");
            }
        }
        //init env first (default params)
        void init_instance(const std::string& model_path)
        {
            init_instance(model_path, llama_model_default_params());
        }

        using llama_tokens_instance = instance<std::vector<llama_token>>;

        llama_tokens_instance build_prompt_tokens(const string& prompt)
        {
            // find the number of tokens in the prompt
            const int n_prompt = -llama_tokenize(
                instance_ptr,
                prompt.c_str(),
                prompt.size(),
                nullptr,
                0,
                true,
                true);

            // allocate space for the tokens and tokenize the prompt
            std::vector<llama_token> prompt_tokens(n_prompt);
            if (llama_tokenize(
                instance_ptr,
                prompt.c_str(),
                prompt.size(),
                prompt_tokens.data(),
                prompt_tokens.size(),
                true,
                true) < 0)
            {
                throw LDException("error: failed to tokenize the prompt");
            }
            return instance<std::vector<llama_token>>(std::move(prompt_tokens));
        }

        void print_prompt_token_by_token(
            llama_tokens_instance prompt_tokens,
            std::function<void(const std::string&)> call
        )
        {
            for (auto id : prompt_tokens.get_ref())
            {
                char buf[128];
                int n = llama_token_to_piece(instance_ptr, id, buf, sizeof(buf), 0, true);
                if (n < 0)
                {
                    throw LDException("error: failed to convert token to piece");
                }
                call(std::string(buf, n));
            }
        }

        llama_batch build_batch(llama_tokens_instance prompt_tokens)
        {
            return llama_batch_get_one(prompt_tokens->data(), prompt_tokens->size());
        }

        void main_loop(
            llama_tokens_instance prompt_tokens,
            instance<llama_context> ctx,
            instance<llama_sampler> smpl,
            llama_batch batch,
            int n_predict,
            std::function<void(const std::string&)> callback)
        {
            llama_token new_token_id;
            int n_prompt = prompt_tokens->size();

            for (int n_pos = 0; n_pos + batch.n_tokens < n_prompt + n_predict; )
            {
                // evaluate the current batch with the transformer model
                if (llama_decode(ctx.get_ptr(), batch))
                {
                    throw LDException("error: failed to eval");
                }

                n_pos += batch.n_tokens;

                // sample the next token
                {
                    new_token_id = llama_sampler_sample(smpl.get_ptr(), ctx.get_ptr(), -1);

                    // is it an end of generation?
                    if (llama_token_is_eog(this->get_ptr(), new_token_id))
                    {
                        break;
                    }

                    char buf[128];
                    int n = llama_token_to_piece(
                        this->get_ptr(),
                        new_token_id,
                        buf,
                        sizeof(buf),
                        0,
                        true);
                    if (n < 0)
                    {
                        throw LDException("error: failed to convert token to piece");
                    }
                    callback(std::string(buf, n));

                    // prepare the next batch with the sampled token
                    batch = llama_batch_get_one(&new_token_id, 1);
                }
            }
        }
        void operator()(
            llama_tokens_instance prompt_tokens,
            instance<llama_context> ctx,
            instance<llama_sampler> smpl,
            llama_batch batch,
            int n_predict,
            std::function<void(const std::string&)> callback)
        {
            main_loop(prompt_tokens, ctx, smpl, batch, n_predict, callback);
        }

        constexpr operator tag* ()
        {
            return instance_ptr;
        }
    };

}

#endif // !__FILE_LLAMA_KIT
