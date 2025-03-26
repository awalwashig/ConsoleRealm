#include "config.h"

namespace Realm {

RealmConfig::RealmConfig(std::string_view& path) 
	:config(std::move(ReadConfig(path))){
	//debug
	std::cout << config.dump() << std::endl;
}

nlohmann::json RealmConfig::ReadConfig(std::string_view& path){
	std::ifstream File((const std::string&)path);

	if (!File.is_open()) {
		std::cerr << "[ERROR]:Cennt open file";
	}
	else {
		nlohmann::json root;
		File >> root;
		return root;
	}

	return nlohmann::json();
}

}