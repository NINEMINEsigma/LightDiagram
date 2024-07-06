#ifndef __FILE_FILESYSTEM
#define __FILE_FILESYSTEM

#include <Core/Header/LF_Config.h>
#include <filesystem>

namespace ld
{
	namespace FileSystem
	{
		using string = std::string;
		using wstring = std::wstring;

		constexpr wchar_t separator = L'/';

		struct any_info
		{
			// Path's attribute
			wstring name, path;
			virtual wstring GetFullPath() const abstract;
			virtual bool IsExist() const abstract;
		};

		wstring Combine(const wstring& path, const wstring& next)
		{
			return path + separator + next;
		}

		struct File final
		{
			struct Info :public any_info
			{
				wstring extension;
				wstring GetFullPathWithoutExtension() const
				{
					return path + separator + name;
				}
				virtual wstring GetFullPath() const override
				{
					return GetFullPathWithoutExtension() + L'.' + extension;
				}
				virtual bool IsExist() const override
				{
					return std::filesystem::exists(GetFullPath());
				}
			};
			Info fileinfo;

			operator wstring() const
			{
				return this->fileinfo.GetFullPath();
			}
			operator bool() const
			{
				return fileinfo.IsExist();
			}
			operator int() const
			{
				if (static_cast<bool>(*this))
				{
					return std::filesystem::file_size(static_cast<wstring>(*this));
				}
				else return -1;
			}

		};


		struct Directory final
		{
			struct Info :public any_info
			{
				virtual wstring GetFullPath() const override
				{
					return path + separator + name;
				}
				virtual bool IsExist() const override
				{
					wstring temp = GetFullPath();
					return std::filesystem::exists(temp) && std::filesystem::is_directory(temp);
				}
			};
			Info dirinfo;
			std::vector<File> files;

			operator wstring()
			{
				return this->dirinfo.GetFullPath();
			}
			operator bool()
			{
				return dirinfo.IsExist();
			}
			operator int() const
			{
				if (static_cast<bool>(*this))
				{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
					struct _finddata_t fileinfo;
					intptr_t handle = _findfirst(to_string(dirinfo.GetFullPath()).c_str(), &fileinfo);
					int fileNum = 0;
					if (handle == -1) return 0;
					while (!_findnext(handle, &fileinfo)) fileNum++;
					_findclose(handle);
					return fileNum;
#else
					int fileNum = 0;
					DIR* pDir;
					struct dirent* ptr;
					if (!(pDir = opendir(path.c_str())))
						return fileNum;
					while ((ptr = readdir(pDir)) != 0)
					{
						if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
							fileNum++;
					}
					closedir(pDir);
					return fileNum;
#endif
				}
				else return -1;
			}

			void RefreshFileList()
			{
				files.clear();
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
				struct _finddata_t fileinfo;
				intptr_t handle = _findfirst(to_string(dirinfo.GetFullPath()).c_str(), &fileinfo);
				if (handle == -1) return;
				while (!_findnext(handle, &fileinfo))
				{
					//files.push_back(File())
				}
				_findclose(handle);
#else
				int fileNum = 0;
				DIR* pDir;
				struct dirent* ptr;
				if (!(pDir = opendir(path.c_str())))
					return fileNum;
				while ((ptr = readdir(pDir)) != 0)
				{
					if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
						fileNum++;
				}
				closedir(pDir);
#endif
			}
		};
	};
}

std::wstring to_wstring(const ld::FileSystem::File& file)
{
	return static_cast<std::wstring>(file);
}
std::string to_string(const ld::FileSystem::File& file)
{
	return to_string(static_cast<std::wstring>(file));
}
std::wstring to_wstring(const ld::FileSystem::Directory& dir)
{
	return static_cast<std::wstring>(dir);
}
std::string to_string(const ld::FileSystem::Directory& dir)
{
	return to_string(static_cast<std::wstring>(dir));
}

#endif // !__FILE_FILESYSTEM
