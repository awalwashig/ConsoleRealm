#include "Application.h"

int main() {
	Realm bot;

}

config::config(std::string_view& path){
	reset(path);
}

config& config::reset(std::string_view& path){
	std::ifstream File((const std::string&)path);

	if (!File.is_open()) {
		std::cerr << "[ERROR]:Cennt open file" << std::endl;
	}
	else {
		nlohmann::json root;
		File >> root;
		m_config.reset(new nlohmann::json(std::move(root)));
	}

	return *this;
}

nlohmann::json& config::GetConifg(){
	return *m_config;
}


qq::qq(){

}

qq& qq::reset(nlohmann::json& config){


	return *this;
}

discord::discord(nlohmann::json& config){
	reset(config);
}

discord& discord::reset(nlohmann::json& config){
	this->config = config["discord"];
	m_cluster.reset(new dpp::cluster(this->config["discord"]["token"]));
	return *this;
}

discord& discord::start(dpp::start_type start){
	m_cluster->start(start);
	return *this;
}

Realm::Realm(std::string_view& config){
	reset(config);
}

Realm& Realm::reset(std::string_view& config){
	config::reset(config);
	discord::reset(config::GetConifg());
	qq::reset(config::GetConifg());

	return *this;
}

Realm& Realm::start(){


	return *this;
}