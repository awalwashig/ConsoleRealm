﻿#include "Application.h"

std::unique_ptr<Realm> Realm::m_instance;

int main() {
	std::string path{ "/home/woomy/projects/ConsoleApplication/data/config.json" };

	Realm::m_instance.reset(new Realm);
	Realm::m_instance->
		reset(path)
		.start();
}

config::config(std::string& path) {
	reset(path);
}

config& config::reset(std::string& path) {
	std::ifstream File(path);

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

nlohmann::json& config::GetConifg() {
	return *m_config;
}

make_hash& make_hash::reset() {
	m_make_hash.reset(new make_hash);
	return *this;
}

void make_hash::push(uint64_t obj) {
	tmp_link = obj;
}

void make_hash::set_link(uint64_t message_id) {
	//debug
	std::cout << "LINK!" << std::endl;

	//link
	hash_map[tmp_link] = message_id;
	hash_map[message_id] = tmp_link;
}

void make_hash::set_name_id(std::tuple<std::string, std::string> obj) {
	auto& [name, id] = obj;

	//双映射
	name_hash[name] = id;
	name_hash[id] = name;
}

std::unordered_map<uint64_t, uint64_t>& make_hash::get_hash_map() {
	return this->hash_map;
}

std::unordered_map<std::string, std::string>& make_hash::get_name_hash() {
	return this->name_hash;
}


std::string markdown::MarkdownRemove(std::string str) {
	std::vector<std::tuple<std::string, std::string, std::string>> regexReplacements = {
			{ R"(\*\*([^*]+)\*\*)", "$1","(**)"},      // Markdown 加粗，如 **加粗** → 保留内部内容
			{ R"(\*([^*]+)\*)", "$1","(*)" },          // Markdown 斜体，如 *斜体* → 保留内部内容
			{ R"(__([^_]+)__)", "$1","(__)" },          // Markdown 下划线，如 __下划线__ → 保留内部内容
			{ R"(~~([^~]+)~~)", "$1","(~~)" },          // Markdown 删除线，如 ~~删除线~~ → 保留内部内容
			{ R"(\|\|([^|]+)\|\|)", "$1","(||)" },       // 剧透文本，如 ||剧透内容|| → 保留内部内容
			{ R"(<@!?(\d+)>)", "","" },         // 用户提及，如 <@123456789> 或 <@!987654321> → 保留数字 ID
			{ R"(<@&(\d+)>)", "","" },           // 角色提及，如 <@&111222333> → 保留数字 ID
			{ R"(<#(\d+)>)", "","" },            // 频道提及，如 <#444555666> → 保留数字 ID
	};

	std::string tmp;
	for (const auto& Obj : regexReplacements) {
		auto [regex, rp, flag] = Obj;

		tmp = str;
		std::regex pattern(regex);
		str = std::regex_replace(str, pattern, rp);
		if (tmp.size() != str.size()) {
			Flag.push_back(flag);
		}
	}
	return str;
}

std::string markdown::MarkdownAttachedQQ(std::string&& str) {
	for (const auto& Obj : Flag) {
		str = str + Obj;
		std::cout << str << std::endl;
	}
	return str;
}


void utility::get_http(nlohmann::json& jsonDate, std::string url) {
	std::string jsonStr = jsonDate.dump();

	// 初始化 libcurl
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL* curl = curl_easy_init();
	if (curl) {
		// 设置请求头为 JSON 格式
		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");

		// 设置请求 URL 和 POST 数据
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

		// 执行请求
		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "请求失败: " << curl_easy_strerror(res) << std::endl;
		}
		else {

		}

		// 清理资源
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}
	else {
		std::cerr << "初始化 libcurl 失败" << std::endl;
	}
	curl_global_cleanup();
}

qq& qq::reset(nlohmann::json& config) {
	this->config = config["qq"];

	m_qq = twobot::BotInstance::createInstance(
		twobot::Config{
			this->config["ip"],
			this->config["http"],
			this->config["ws"],
			this->config["token"]
		}
	);

	main();

	return *this;
}

qq& qq::set_callback(void(*fn)(nlohmann::json)) {
	callback = fn;
	return *this;
}

qq& qq::start() {
	std::thread([&]() {
		m_qq->start();
		}).detach();
	return *this;
}

twobot::BotInstance& qq::GetInstance() {
	return *m_qq;
}

void qq::accept(nlohmann::json input) {
	static const std::string url = Realm::m_instance->GetConifg()["qq"]["useip"].get<std::string>() + "/send_group_msg";
	std::cout << "QQ: accept" << std::endl;
	utility::get_http(input, url);
}

qq& qq::main() {
	using twobot::Config;
	using twobot::BotInstance;
	using twobot::ApiSet;
	using namespace twobot::Event;

	m_qq->onEvent<OtherEvent>([&](const OtherEvent& event) {
		//{"status":"ok","retcode":0,"data":{"message_id":1716356328},"message":"","wording":"","echo":null}

		if (event.raw_msg["user_id"] != config["bot_qq_id"]) {
			return;
		}
		Realm::m_instance->set_link(event.raw_msg["message_id"].get<uint64_t>());

		});

	m_qq->onEvent<GroupMsg>([&](const GroupMsg& msg) {
		//史
		std::cout << msg.raw_msg << std::endl;

		if (msg.group_id != config["group"]) {
			return;
		}

		Realm::m_instance->set_link(msg.raw_msg["message_id"].get<uint64_t>());

		std::string tmp_message = "";
		for (auto& data : msg.raw_msg["message"]) {
			if (data["type"] == "text") {
				tmp_message += data["data"]["text"].get<std::string>() + "\n";

				continue;
			}

			if (data["type"] == "image") {
				tmp_message += get_image_url(data["data"]["file"].get<std::string>()) + "\n";

				continue;
			}

			if (data["type"] == "at") {
				tmp_message += Realm::m_instance->get_name_hash()[data["data"]["qq"].get<std::string>()];

				continue;
			}

			if (data["type"] == "reply") {
				Realm::m_instance->get_cluster().message_create(
					dpp::message("reply")
					.set_channel_id(Realm::m_instance->GetConifg()["discord"]["channel"])
					.set_reference(Realm::m_instance->get_hash_map()[std::stoull(data["data"]["id"].get<std::string>())])
				);

				continue;
			}
		}

		nlohmann::json input;

		input["content"] = std::move(tmp_message);
		input["avatar_url"] = std::string("https://q.qlogo.cn/headimg_dl?dst_uin=") + std::string(std::to_string((int)msg.user_id)) + std::string("&spec=640&img_type=jpg");

		if (msg.raw_msg["sender"]["card"] != "") {
			input["username"] = msg.raw_msg["sender"]["card"];
		}
		else {
			input["username"] = msg.raw_msg["sender"]["nickname"];
		}

		Realm::m_instance->push(msg.raw_msg["message_id"]);

		callback(input);
		});
	return *this;
}

//看网址托管情况为定
std::string qq::get_image_url(std::string file_id) {
	static const std::string prefix = "/root/.config/QQ";

	if (!m_qq->getApiSet().getImage(file_id).second["data"]["file"].is_null()) {
		std::string message = m_qq->getApiSet().getImage(file_id).second["data"]["file"].get<std::string>();

		//史
		std::string cmd = "sudo mv -f " + message + " " + message + ".gif";
		system(cmd.c_str());
		//End

		message.erase(0, prefix.length());
		message = config["domain_name"].get<std::string>() + message + ".gif"; //gif为史

		return message;
	}
	return std::string();
}

discord::discord(nlohmann::json& config) {
	reset(config);
}

discord& discord::reset(nlohmann::json& config) {
	this->config = config["discord"];
	m_cluster.reset(new dpp::cluster(this->config["token"], dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_messages));

	main();

	return *this;
}

discord& discord::set_callback(void(*fn)(nlohmann::json)) {
	callback = fn;

	return *this;
}

discord& discord::start(dpp::start_type start) {
	//debug
	m_cluster->on_log(dpp::utility::cout_logger());

	m_cluster->start(start);
	return *this;
}

dpp::cluster& discord::get_cluster() {
	return *m_cluster;
}

void discord::set_send_flag() {
	send_flag = 1;
}

void discord::accept(nlohmann::json input) {
	std::cout << "discord: accept" << std::endl;

	Realm::m_instance->set_send_flag();

	utility::get_http(input, Realm::m_instance->GetConifg()["discord"]["webhook"]);
}

discord& discord::main() {
	m_cluster->on_message_create([&](const dpp::message_create_t& event) {
		static std::string Obj = "";

		if (event.msg.channel_id != config["channel"].get<dpp::snowflake>() || event.msg.author.id == m_cluster->me.id) {
			return;
		}

		Realm::m_instance->set_link(event.msg.id);

		if (event.msg.author.is_bot()) {
			return;
		}

		nlohmann::json input;
		input["group_id"] = Realm::m_instance->GetConifg()["qq"]["group"];

		markdown MK;

		std::string content = MK.MarkdownRemove(event.msg.content);
		if (Obj != event.msg.author.global_name || send_flag) {
			content = event.msg.author.global_name + ":" + MK.MarkdownAttachedQQ(std::move(content));

			Obj = event.msg.author.global_name;
			send_flag = 0;
		}
		else {
			content = MK.MarkdownAttachedQQ(std::move(content));
		}

		input["message"] = emoji(content);

		//回复
		if (!event.msg.message_reference.message_id.empty()) {
			nlohmann::json res = {
			{"data", {
				{"id", ""},
			}},
			{"type", "reply"}
			};
			res["data"]["id"] = std::to_string(Realm::m_instance->get_hash_map()[event.msg.message_reference.message_id]);
			input["message"].push_back(std::move(res));
		}

		//附件
		for (auto& obj : event.msg.attachments) {
			if (!isImageFile(obj.filename)) {
				continue;
			}

			nlohmann::json res = {
			{"data", {
				{"file", ""},
				{"sub_type", 1},
				{"summary", "[动画表情]"},
				{"url", ""}
			}},
			{"type", "image"}
			};

			system(std::string("curl -L -o " + obj.filename + " \"" + obj.url + "\"").c_str());
			system(std::string("sudo mv " + obj.filename + " /root/.config/QQ/NapCat/temp/").c_str());

			res["data"]["file"] = obj.filename;
			res["data"]["url"] = "file:///root/.config/QQ/NapCat/temp/" + obj.filename;

			input["message"].push_back(std::move(res));
		}

		std::cout << content << std::endl;

		if (content != "") {
			nlohmann::json obj;
			obj["data"]["text"] = content;
			obj["type"] = "text";
			input["message"].push_back(std::move(obj));
		}

		std::cout << input.dump() << std::endl;

		Realm::m_instance->push(event.msg.id);
		callback(input);
		});

	return *this;
}

nlohmann::json discord::emoji(std::string& obj) {
	static std::unordered_map<std::string, bool> cache;
	nlohmann::json res;
	std::smatch match;
	std::string cmd = "wget ";
	std::regex emojiPattern("<:[^:]+:(\\d+)>");

	int index = 0;
	std::string s = obj;
	while (std::regex_search(s, match, emojiPattern)) {
		res[index] = {
			{"data", {
				{"file", ""},
				{"sub_type", 1},
				{"summary", "[动画表情]"},
				{"url", ""}
			}},
			{"type", "image"}
		};

		//史
		if (cache[match[1].str()] == bool()) {
			cmd = cmd + "https://cdn.discordapp.com/emojis/" + match[1].str() + ".webp";
			system(std::string("mkdir -p " + config["cache"].get<std::string>()).c_str());
			system(cmd.c_str());
			system(std::string("mv -f " + match[1].str() + ".webp " + config["cache"].get<std::string>()).c_str());

			cache[match[1].str()] = true;
		}

		res[index]["data"]["file"] = match[1].str() + ".webp";
		res[index]["data"]["url"] = "file://" + config["cache"].get<std::string>() + "/" + match[1].str() + ".webp";

		s = match.suffix().str();
		index++;
	}
	obj = std::regex_replace(obj, emojiPattern, "");

	return res;
}

bool discord::isImageFile(const std::string& filename) {
	// 查找最后一个点的位置
	size_t pos = filename.find_last_of(".");
	if (pos == std::string::npos) {
		return false;  // 没有扩展名
	}
	// 获取扩展名
	std::string ext = filename.substr(pos + 1);
	// 将扩展名转换为小写
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	// 定义常见的图片格式集合
	static const std::set<std::string> imageExtensions = {
		"jpg", "jpeg", "png", "gif", "bmp", "tiff", "tif", "webp"
	};

	// 判断扩展名是否在图片格式集合中
	return { imageExtensions.find(ext) != imageExtensions.end() };
}

Realm::Realm(std::string& config) {
	reset(config);
}

Realm& Realm::reset(std::string& config) {
	config::reset(config);
	make_hash::reset();

	discord::reset(config::GetConifg())
		.set_callback(qq::accept);
	qq::reset(config::GetConifg())
		.set_callback(discord::accept);

	std::thread([&]() {
		make_hash::reset();
		std::this_thread::sleep_for(std::chrono::days(1));
		}).detach();

	return *this;
}

Realm& Realm::start() {

	qq::start();
	discord::start(dpp::st_wait);
	return *this;
}

/*
* 通用：消息队列，建立好hash表对双方映射;
*
* discord：处理正则表达（表情符号）并保存挂在服务上面;
*
* qq处理一堆破事分类好qq喂过来的史;
*/