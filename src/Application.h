#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <regex>
#include <curl/curl.h>

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

class markdown {
public:
	markdown() = default;

	std::string MarkdownRemove(std::string str);

	std::string MarkdownAttached(std::string&& str);
private:
	std::vector<std::string> Flag;
};

class qq {
public:
	qq();

	qq& reset(nlohmann::json& config);

	qq& set_callback(void(*fn)(nlohmann::json));

	qq& start();

public:


	static void send(nlohmann::json input);
private:
	qq& main();


private:
	std::function<void(nlohmann::json)> callback;

	std::unique_ptr<twobot::BotInstance> m_qq;
	nlohmann::json config;
};

class discord {
public:
	discord() = default;

	discord(nlohmann::json& config);

	discord& reset(nlohmann::json& config);

	discord& set_callback(void(*fn)(nlohmann::json));

	discord& start(dpp::start_type start);
public:


	static void send(nlohmann::json input);

	static void UseWebhook(nlohmann::json& jsonDate, std::string url);
private:
	discord& main();

private:

	bool send_flag = 0;

	std::function<void(nlohmann::json)> callback;
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