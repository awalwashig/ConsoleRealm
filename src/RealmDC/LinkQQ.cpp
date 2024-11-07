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
		std::vector<std::string> image;
		std::vector<std::string> imageEmoji;

		std::string avatar = std::string("https://q.qlogo.cn/headimg_dl?dst_uin=") + std::string(std::to_string((int)obj["user_id"])) + std::string("&spec=2&img_type=jpg");


		EmbedQQ.set_author(dpp::embed_author(obj["sender"]["card"] == "" ? obj["sender"]["nickname"] : obj["sender"]["card"], "", avatar));

		std::vector<std::string> msgs;
		for (nlohmann::json tmp : obj["message"]) {

			if (tmp["type"] == "image") {
				if (tmp["file"] != "marketface")
					image.push_back(tmp["data"]["file_unique"]);
				else
					imageEmoji.push_back(tmp["data"]["file_unique"]);
				continue;
			}
			//RealmQQ::GetRealmBot()->getApiSet().getImage(tmp["data"]["file"]);

			msgs.push_back(tmp["type"] == "text" ? tmp["data"]["text"] : tmp["data"]["url"]);
		}

		for (std::string msg : msgs) {
			//TODO:add message funtion()
			//like:std::string message(msg);
			EmbedQQ
				.add_field(msg, "");
		}

		EmbedQQ.set_color(dpp::colors::purple_dragon);

		RealmDC::GetRealmBot()->message_create(dpp::message(RealmHashDC::GetChannel(obj["group_id"]), EmbedQQ), [](const dpp::confirmation_callback_t& callback)->dpp::command_completion_event_t {
			return dpp::utility::log_error();
			});

		std::time_t now = std::time(nullptr);
		std::tm* timeinfo = std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(timeinfo, "%Y-%m");

		std::string ImageURL = "https://fumoserpi.awalwashig.uno/";

		for (auto temp : imageEmoji) {
			std::transform(temp.begin(), temp.end(), temp.begin(),
				[](unsigned char c) { return std::tolower(c); });

			RealmDC::GetRealmBot()->message_create(dpp::message(ImageURL + "Emoji/emoji-recv/" + oss.str() + "/Ori/" + temp).set_channel_id(RealmHashDC::GetChannel(obj["group_id"])), [](const dpp::confirmation_callback_t& callback)->dpp::command_completion_event_t {
				return dpp::utility::log_error();
				});
		}

		for (auto temp : image) {
			std::transform(temp.begin(), temp.end(), temp.begin(),
				[](unsigned char c) { return std::tolower(c); });

			RealmDC::GetRealmBot()->message_create(dpp::message(ImageURL + "Pic/" + oss.str() + "/Ori/" + temp).set_channel_id(RealmHashDC::GetChannel(obj["group_id"])), [](const dpp::confirmation_callback_t& callback)->dpp::command_completion_event_t {
				return dpp::utility::log_error();
				});
		}
	}

	//输出QQ
	void LinkQQ::OutputMsg(void(*Send)(nlohmann::json obj)) {
		RealmDC::GetRealmBot()->on_message_create([Send](const dpp::message_create_t& event) {
			if (RealmHashQQ::GetGroup(event.msg.channel_id) != NULL)
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
	void LinkQQ::InputRecall(nlohmann::json obj) {

	}
	void LinkQQ::OutRecall(void(*Send)(nlohmann::json obj)) {

	}
}