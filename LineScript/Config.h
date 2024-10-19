#ifndef __FILE_CONFIG
#define __FILE_CONFIG

#include<LightDiagram.h>

namespace ls
{
	namespace config
	{
		class config final
		{
		public:
			config(int argc, char** argv);
			std::map<std::string, std::string> default_values =
			{
				std::make_pair("memory_size","1073741824")
			};
		private:
			void read_any_config_info(const std::string& key, const std::string& value) const noexcept;
			void empty_config_log() const noexcept;
		};
	}
}

#endif // !__FILE_CONFIG
