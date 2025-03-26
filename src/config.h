#pragma once
#include <dpp/dpp.h>

namespace Realm {
class RealmConfig {
public:
	RealmConfig(std::string_view& path);
	~RealmConfig() = default;

	nlohmann::json ReadConfig(std::string_view& path);

private:
	nlohmann::json config;
};
}//End Realm