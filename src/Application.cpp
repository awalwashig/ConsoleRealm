#include "Application.h"

std::unique_ptr<Realm> Realm::m_instance;

int main() {
	std::string path{"/home/woomy/projects/ConsoleApplication/data/config.json"};

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

std::string markdown::MarkdownRemove(std::string str){
	std::vector<std::tuple<std::string, std::string, std::string>> regexReplacements = {
			{ R"(\*\*([^*]+)\*\*)", "$1","**"},      // Markdown 加粗，如 **加粗** → 保留内部内容
			{ R"(\*([^*]+)\*)", "$1","*" },          // Markdown 斜体，如 *斜体* → 保留内部内容
			{ R"(__([^_]+)__)", "$1","__" },          // Markdown 下划线，如 __下划线__ → 保留内部内容
			{ R"(~~([^~]+)~~)", "$1","~~" },          // Markdown 删除线，如 ~~删除线~~ → 保留内部内容
			{ R"(\|\|([^|]+)\|\|)", "$1","||" },       // 剧透文本，如 ||剧透内容|| → 保留内部内容
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

std::string markdown::MarkdownAttached(std::string&& str){
	for (const auto& Obj : Flag) {
		str = Obj + str + Obj;
		std::cout << str << std::endl;
	}
	return str;
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

	//if (!m_qq->getApiSet().testConnection()) {
	//	std::cerr << "测试连接失败，请启动onebot服务器，并配置HTTP端口！" << std::endl;
	//}

	return *this;
}

qq& qq::set_callback(void(*fn)(nlohmann::json)){
	return *this;
}

qq& qq::start(){
	std::thread([&]() {
		m_qq->start();
		}).detach();
	return *this;
}

twobot::BotInstance& qq::GetInstance(){
	return *m_qq;
}

void qq::accept(nlohmann::json input){
	std::cout << "QQ: accept" << std::endl;

	Realm::m_instance->
	GetInstance().
		getApiSet().
		sendGroupMsg(input["group"], input["msg"]);
}

qq& qq::main(){
	using twobot::Config;
	using twobot::BotInstance;
	using twobot::ApiSet;
	using namespace twobot::Event;

	m_qq->onEvent<GroupMsg>([&](const GroupMsg& msg) {
		//if (msg.raw_message == "你好")
		//	m_qq->getApiSet().sendGroupMsg(msg.group_id, "你好，我是twobot！");
		//else if (msg.raw_message.find("AT我") != std::string::npos) {
		//	std::string at = "[CQ:at,qq=" + std::to_string(msg.user_id) + "]";
		//	m_qq->getApiSet().sendGroupMsg(msg.group_id, at + "要我at你干啥？");
		//}

		std::cout << msg.raw_msg << std::endl;

		if (msg.group_id != config["group"]) {
			return;
		}
		nlohmann::json input;

		input["content"] = msg.raw_message;
		input["username"] = msg.group_name;
		input["avatar_url"];


		callback(input);
		});
	return *this;
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

discord& discord::set_callback(void(*fn)(nlohmann::json)){
	callback = fn;

	return *this;
}

discord& discord::start(dpp::start_type start) {
	//debug
	m_cluster->on_log(dpp::utility::cout_logger());

	m_cluster->start(start);
	return *this;
}

void discord::set_send_flag(){
	send_flag = 1;
}

void discord::accept(nlohmann::json input){
	nlohmann::json jsonData;


	UseWebhook(jsonData, input["webhook"]);
}

void discord::UseWebhook(nlohmann::json& jsonDate, std::string url){
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

discord& discord::main(){
	m_cluster->on_message_create([&](const dpp::message_create_t& event) {
		static std::string Obj = "";

		if (event.msg.author.is_bot() || event.msg.channel_id != config["channel"].get<dpp::snowflake>()) {
			return;
		}

		nlohmann::json input;
		input["group"] = Realm::m_instance->GetConifg()["qq"]["group"];

		markdown MK;

		std::string content = MK.MarkdownRemove(event.msg.content);

		std::cout << Obj << ":" << content << std::endl;

		if (Obj == event.msg.author.global_name && !send_flag) {
			input["msg"] = content;
		}
		else {
			input["msg"] = event.msg.author.global_name + ":" + content;
			Obj = event.msg.author.global_name;
			send_flag = 0;
		}

		callback(input);
		});

	return *this;
}

Realm::Realm(std::string& config) {
	reset(config);
}

Realm& Realm::reset(std::string& config) {
	config::reset(config);

	discord::reset(config::GetConifg())
		.set_callback(qq::accept);
	qq::reset(config::GetConifg());

	return *this;
}

Realm& Realm::start() {

	qq::start();
	discord::start(dpp::st_wait);
	return *this;
}
