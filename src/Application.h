﻿#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <regex>
#include <curl/curl.h>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

#include <dpp/dpp.h>
#include <twobot.hh>

class config {
public:
	config() = default;

	config(std::string& path);

	config& reset(std::string& path);

	nlohmann::json& GetConifg();
private:
	std::unique_ptr<nlohmann::json> m_config;
};

//TODO
class make_hash {
public:
	make_hash() = default;

	make_hash& reset();

	void push(uint64_t obj);

	void set_link(uint64_t message_id);

	void set_name_id(std::tuple<std::string, std::string> obj);

	std::unordered_map<uint64_t, uint64_t>& get_hash_map();

	std::unordered_map<std::string, std::string>& get_name_hash();
private:

	uint64_t tmp_link;

	std::unordered_map<uint64_t, uint64_t> hash_map;

	std::unordered_map<std::string, std::string> name_hash;
private:
	std::unique_ptr<make_hash> m_make_hash;
};

class markdown {
public:
	markdown() = default;

	std::string MarkdownRemove(std::string str);

	std::string MarkdownAttachedQQ(std::string&& str);
private:
	std::vector<std::string> Flag;
};

class utility {
public:
	static void get_http(nlohmann::json& jsonDate, std::string url);
};

class qq {
public:
	qq() = default;

	qq& reset(nlohmann::json& config);

	qq& set_callback(void(*fn)(nlohmann::json));

	qq& start();

public:
	twobot::BotInstance& GetInstance();

	static void accept(nlohmann::json input);
private:
	qq& main();

	std::string get_image_url(std::string file_id);
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

	dpp::cluster& get_cluster();
public:
	void set_send_flag();

	static void accept(nlohmann::json input);
private:
	discord& main();

	nlohmann::json emoji(std::string& obj);

	bool isImageFile(const std::string& filename);
private:

	bool send_flag = 0;

	std::function<void(nlohmann::json)> callback;
	std::unique_ptr<dpp::cluster> m_cluster;
	nlohmann::json config;
};

class Realm : public config, public qq, public discord, public make_hash {
public:
	Realm() = default;

	Realm(std::string& config);

	Realm& reset(std::string& config);

	Realm& start();

public:
	static std::unique_ptr<Realm> m_instance;
};