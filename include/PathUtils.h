#pragma once

#include "filesystem_def.h"

namespace Framework
{
	namespace PathUtils
	{
		fs::path GetAppResourcesPath();
		fs::path GetRoamingDataPath();
		fs::path GetPersonalDataPath();
		fs::path GetCachePath();
		
#ifdef _WIN32
		fs::path GetPathFromCsidl(int);
#endif	//WIN32
		void SetFilesDirPath(const char*);
		void SetCacheDirPath(const char*);

		void EnsurePathExists(const fs::path&);

		std::string GetNativeStringFromPath(const fs::path&);
		fs::path    GetPathFromNativeString(const std::string&);
	};
};
