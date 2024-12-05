#include "Config.h"

using namespace ld;
using namespace std;

namespace ls
{
	namespace config
	{
#define log_message(key, value)\
		do\
		{\
			stringstream ss;\
			ss << "config key: " << key;\
			if (value.empty())\
				ss << endl;\
			else\
				ss << ", and its value is \"" << value << "\"\n";\
			console.LogMessage(next_line(ss));\
		} while (false)

#pragma region Memory

		namespace memory
		{
			char* memory_buffer = nullptr;
			size_t memory_black = 0;
		}
		void init_memory_size(const string& value)
		{
			::free(memory::memory_buffer);
			memory::memory_buffer = (char*)malloc(sizeof(char) * atoi(value.c_str()));
			memory::memory_black = 0;
			log_message("memory_size", value);
		}

#pragma endregion

		map<string, function<void(const string&)>> key_words =
		{
			make_pair("memory_size",init_memory_size)
		};

		config::config(int argc, char** argv)
		{
			config_instance reader(argc, argv);
			if (reader->empty())
			{
				empty_config_log();
			}
			else
			{
				for (auto& [key,value] : reader)
				{
					if (key_words.count(key))
					{
						key_words[key](value);
					}
					else
						read_any_config_info(key, value);
				}
				for (auto& [key, value] : key_words)
				{
					if (reader.contains(key) == false)
					{
						value(default_values[key]);
					}
				}
			}
		}
		void config::read_any_config_info(const string& key, const string& value) const noexcept
		{
			if (key == config_instance::local_path_key)return;
			static stringstream ss;
			ss << "unknow config key: " << key;
			if (value.empty())
				ss << endl;
			else
				ss << ", and its value is \"" << value << "\"\n";
			console.LogWarning(next_line(ss));
		}
		void config::empty_config_log() const noexcept
		{
			console.LogWarning("no config is been define");
		}
#undef log_message
	}
}
