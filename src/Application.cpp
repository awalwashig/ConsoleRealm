#include "Application.h"

int main() {
	Realm bot;

}

config::config(std::string_view& path) {
	reset(path);
}

config& config::reset(std::string_view& path) {
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

nlohmann::json& config::GetConifg() {
	return *m_config;
}

std::string markdown::MarkdownRemove(std::string str){
	std::vector<std::tuple<std::string, std::string, std::string>> regexReplacements = {
			{ R"(\*\*([^*]+)\*\*)", "$1","**"},      // Markdown �Ӵ֣��� **�Ӵ�** �� �����ڲ�����
			{ R"(\*([^*]+)\*)", "$1","*" },          // Markdown б�壬�� *б��* �� �����ڲ�����
			{ R"(__([^_]+)__)", "$1","__" },          // Markdown �»��ߣ��� __�»���__ �� �����ڲ�����
			{ R"(~~([^~]+)~~)", "$1","~~" },          // Markdown ɾ���ߣ��� ~~ɾ����~~ �� �����ڲ�����
			{ R"(\|\|([^|]+)\|\|)", "$1","||" },       // ��͸�ı����� ||��͸����|| �� �����ڲ�����
			{ R"(<@!?(\d+)>)", "","" },         // �û��ἰ���� <@123456789> �� <@!987654321> �� �������� ID
			{ R"(<@&(\d+)>)", "","" },           // ��ɫ�ἰ���� <@&111222333> �� �������� ID
			{ R"(<#(\d+)>)", "","" },            // Ƶ���ἰ���� <#444555666> �� �������� ID
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

qq::qq() {

}

qq& qq::reset(nlohmann::json& config) {
	this->config = config["qq"];

	m_qq = twobot::BotInstance::createInstance(
		twobot::Config{
			config["ip"],
			config["http"],
			config["ws"],
			config["token"]
		}
	);

	return *this;
}

qq& qq::set_callback(void(*fn)(nlohmann::json)){
	return *this;
}

qq& qq::start(){
	return *this;
}

qq& qq::main(){



	return *this;
}

discord::discord(nlohmann::json& config) {
	reset(config);
}

discord& discord::reset(nlohmann::json& config) {
	this->config = config["discord"];
	m_cluster.reset(new dpp::cluster(this->config["discord"]["token"]));

	main();

	return *this;
}

discord& discord::set_callback(void(*fn)(nlohmann::json)){
	callback = fn;

	return *this;
}

discord& discord::start(dpp::start_type start) {
	m_cluster->start(start);
	return *this;
}

discord& discord::main(){
	m_cluster->on_message_create([&](const dpp::message_create_t& event) {
		static std::string Obj = "";

		if (event.msg.author.is_bot() || event.msg.channel_id != config["channel"].get<dpp::snowflake>()) {
			return;
		}

		nlohmann::json message;

		markdown MK;

		std::string content = MK.MarkdownRemove(event.msg.content);

		if (Obj == event.msg.author.global_name && send_flag) {
			message["msg"] = content;
		}
		else {
			message["msg"] = event.msg.author.global_name + ":" + content;
			Obj = event.msg.author.global_name;
		}

		callback(message);
		});

	return *this;
}

Realm::Realm(std::string_view& config) {
	reset(config);
}

Realm& Realm::reset(std::string_view& config) {
	config::reset(config);

	discord::reset(config::GetConifg());
	qq::reset(config::GetConifg());

	return *this;
}

Realm& Realm::start() {


	return *this;
}
