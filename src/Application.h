#pragma once
#include <iostream>
#include <memory>

#include <dpp/dpp.h>
#include <twobot.hh>

class qq {
public:
	qq();

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

class Realm {
public:
	Realm();

	Realm& start();
};