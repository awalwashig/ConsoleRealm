#include "LinkQQ.h"

#include "RealmDC.h"
#include "RealmHashDC.h"
#include "../RealmQQ/RealmHashQQ.h"
#include <stdlib.h>

namespace Realm::DC {
	void LinkQQ::InitLink() {
		QQ::LinkDC Obj;
		Obj.OutputMsg(InputMsg);
	}
	//输入进DC消息
	void LinkQQ::InputMsg(nlohmann::json obj) {
		//add QQ message
		dpp::embed EmbedQQ;

		std::string avatar = std::string("https://q.qlogo.cn/headimg_dl?dst_uin=") + std::string(std::to_string((int)obj["user_id"])) + std::string("&spec=2&img_type=jpg");


		EmbedQQ.set_author(dpp::embed_author(obj["sender"]["card"] == "" ? obj["sender"]["nickname"] : obj["sender"]["card"], "", avatar));
		for (nlohmann::json tmp : obj["message"])
			EmbedQQ
			.add_field(std::string(tmp["type"] == "text" ? tmp["data"]["text"] : tmp["data"]["url"]), "");

		EmbedQQ.set_color(dpp::colors::purple_dragon);

		RealmDC::GetRealmBot()->message_create(dpp::message(RealmHashDC::GetChannel(obj["group_id"]), EmbedQQ), [](const dpp::confirmation_callback_t& callback)->dpp::command_completion_event_t {
			return dpp::utility::log_error();
			});

		RealmDC::GetRealmBot()->message_create(dpp::message(GetImageURL(obj)).set_channel_id(RealmHashDC::GetChannel(obj["group_id"])), [](const dpp::confirmation_callback_t& callback)->dpp::command_completion_event_t {
			return dpp::utility::log_error();
			});
	}

	//输出QQ
	void LinkQQ::OutputMsg(void(*Send)(nlohmann::json obj)) {
		RealmDC::GetRealmBot()->on_message_create([Send](const dpp::message_create_t& event) {
			if (RealmHashQQ::GetGroup(event.msg.channel_id) == NULL)
				return;

			if (event.msg.author.id == RealmDC::GetRealmBot()->me.id)
				return;

			nlohmann::json JsonObj = (nlohmann::json)event.msg.to_json();

			JsonObj["usernamecustom"] = event.msg.author.global_name != "" ? event.msg.author.global_name : (std::string)JsonObj["username"];

			//debug
			std::cout << JsonObj << std::endl;

			(*Send)(JsonObj);
			});
	}
	void LinkQQ::InputRecall(nlohmann::json& obj) {

	}
	void LinkQQ::OutRecall(void(*Send)(nlohmann::json obj)) {

	}
	std::string LinkQQ::GetImageURL(nlohmann::json& Obj) {
		std::vector<std::string> image;
		std::vector<std::string> msgs;
		for (nlohmann::json tmp : Obj["message"])
			if (tmp["type"] != "image")
				msgs.push_back(tmp["type"] == "text" ? tmp["data"]["text"] : tmp["data"]["url"]);
			else if (tmp["file"] != "marketface")
				image.push_back(tmp["data"]["file_unique"]);

		//RealmQQ::GetRealmBot()->getApiSet().getImage(tmp["data"]["file"]);

		std::time_t now = std::time(nullptr);
		std::tm* timeinfo = std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(timeinfo, "%Y-%m");

		std::string ImageURL = "https://fumoserpi.awalwashig.uno/";

		std::string ReturnStr;

		//std::cout << nlohmann::json(Obj).is_string() << std::endl;

		for (auto temp : image) {
			std::transform(temp.begin(), temp.end(), temp.begin(),
				[](unsigned char c) { return std::tolower(c); });

			system(std::string("sudo find /root/.config/QQ/nt_qq_354df08726cc8340e983dd9b686f4450/nt_data/ -name \"*" + temp + "*\" | xargs -I {} sudo cp {} ./server/images/" + temp + ".jpg").c_str());

			ReturnStr += ImageURL + temp + ".jpg\n";
		}

		return ReturnStr;
	}
}