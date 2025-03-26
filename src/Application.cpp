#include "Application.h"

int main() {
	Realm bot;

	bot.start();
}

qq::qq(){

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

Realm::Realm(){

}

Realm& Realm::start(){

	return *this;
}