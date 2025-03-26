#pragma once
#include <iostream>
#include <memory>

#include <dpp/dpp.h>
#include <twobot.hh>

class config {
public:
	config() = default;

	config(std::string_view& path);

	config& reset(std::string_view& path);

	nlohmann::json& GetConifg();
private:
	std::unique_ptr<nlohmann::json> m_config;
};

class qq {
public:
	qq();

	qq& reset(nlohmann::json& config);
private:
	std::unique_ptr<twobot::BotInstance> m_qq;
	nlohmann::json config;
};

class discord {
public:
	discord() = default;

	discord(nlohmann::json& config);

	discord& reset(nlohmann::json& config);

private:
	discord& start(dpp::start_type start);

	std::unique_ptr<dpp::cluster> m_cluster;
	nlohmann::json config;
};

class Realm : public config, public qq, public discord {
public:
	Realm() = default;

	Realm(std::string_view& config);

	Realm& reset(std::string_view& config);

	Realm& start();
};