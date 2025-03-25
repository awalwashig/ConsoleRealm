#pragma once
#include <dpp/dpp.h>

namespace Base {
	class RealmConfig {
	public:
		RealmConfig(std::string Path_);

		static nlohmann::json Read(std::string Path);
		static RealmConfig* SetInstance(RealmConfig* Instance);
		static RealmConfig* GetInstance();
		static nlohmann::json* GetJsonConfig();
	private:
		nlohmann::json JsonConfig;
		std::string Path;
		static RealmConfig* s_Instance;
	};
	void InitConfig(std::string Path);
}