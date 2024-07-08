#define __FILE_FILESYSTEM
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
		constexpr wchar_t separator2 = L'\\';

		size_t FindPathSepartor(const string& str)
		{
			size_t result = str.find(separator);
			return result == string::npos ? str.find(separator2) : result;
		}
		size_t rFindPathSepartor(const string& str)
		{
			size_t result = str.rfind(separator);
			return result == string::npos ? str.rfind(separator2) : result;
		}
		size_t FindPathSepartor(const wstring& str)
		{
			size_t result = str.find(separator);
			return result == string::npos ? str.find(separator2) : result;
		}
		size_t rFindPathSepartor(const wstring& str)
		{
			size_t result = str.rfind(separator);
			return result == string::npos ? str.rfind(separator2) : result;
		}

		struct any_info
		{
		public:
			wstring name, path;
			// Path's attribute
			virtual wstring GetFullPath() const abstract;
			virtual bool IsExist() const abstract;
		private:
			any_info(const wstring& fullpath, int sp, bool coren) :path(coren ? L"" : fullpath.substr(0, sp)), name(coren ? fullpath : fullpath.substr(sp + 1, fullpath.size() - sp - 1)) {}
			any_info(const wstring& fullpath, int sp) :any_info(fullpath,sp, sp == wstring::npos) {}
		public:
			any_info() :name(L""), path(L"") {}
			any_info(const wstring& fullpath) :any_info(fullpath, rFindPathSepartor(fullpath)) {}
		};

		wstring Combine(const wstring& path, const wstring& next)
		{
			return path + separator + next;
		}

		struct File final
		{
			struct Info :public any_info
			{
				Info():extension(L"") {}
				wstring extension;
			private:
				Info(const wstring& fullpath, int sp, bool coren) :any_info(fullpath.substr(0, sp)), extension(coren ? L"" : fullpath.substr(sp + 1, fullpath.size() - sp - 1)) {}
				Info(const wstring& fullpath, int sp) :Info(fullpath, sp, sp == wstring::npos) {}
			public:
				Info(const wstring& fullpath) :Info(fullpath, fullpath.rfind('.')) {}
				wstring GetFullPathWithoutExtension() const
				{
					return path + separator + name;
				}
				virtual wstring GetFullPath() const override
				{
					return GetFullPathWithoutExtension() + (extension.size() ? (L'.' + extension) : L"");
				}
				virtual bool IsExist() const override
				{
					return std::filesystem::exists(GetFullPath());
				}
			};
			Info fileinfo;
			operator Info& ()
			{
				return fileinfo;
			}
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

			File(const wstring& fullpath) :fileinfo(fullpath) {}
		};


		struct Directory final
		{
			struct Info :public any_info
			{
				Info(const wstring& fullpath) :any_info(fullpath) {}
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
			using subfiles_shared_type = std::shared_ptr<File>;
			using subfiles_container = std::vector<subfiles_shared_type>;
			using subdir_shared_type = std::shared_ptr<Directory>;
			using subdir_container = std::vector<subdir_shared_type>;
			subfiles_container files;
			subdir_container dirs;

			operator Info& ()
			{
				return dirinfo;
			}
			operator subfiles_container& ()
			{
				return files;
			}
			operator wstring() const
			{
				return this->dirinfo.GetFullPath();
			}
			operator bool() const
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
				dirs.clear();
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
				struct _finddata_t fileinfo;
				intptr_t handle = _findfirst(to_string(dirinfo.GetFullPath()).c_str(), &fileinfo);
				if (handle == -1) return;
				while (!_findnext(handle, &fileinfo))
				{
					files.push_back(std::make_shared<File>(new File(to_wstring(fileinfo.name))));
				}
				_findclose(handle);
#else
				int fileNum = 0;
				DIR* pDir;
				struct dirent* ptr;
				if (!(pDir = opendir(path.c_str())))return;
				while ((ptr = readdir(pDir)) != 0)
				{
					if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
						files.push_back(std::make_shared<File>(new File(to_wstring(ptr->d_name)));
				}
				closedir(pDir);
#endif
				if (this->dirinfo.IsExist())
				{
					for (auto& i : std::filesystem::directory_iterator(this->dirinfo.GetFullPath()))
					{
						if (std::filesystem::is_directory(i))
						{
							//files.push_back(std::make_shared<File>(new File(to_wstring(i.path().native()))));
						}
					}
				}
			}

			Directory(const wstring& fullpath) :dirinfo(fullpath) {}
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
