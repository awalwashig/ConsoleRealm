#include "LinkDC.h"
#include "RealmQQ.h"

#include "RealmHashQQ.h"
#include <iostream>
#include <sstream>
#include <string>

namespace Realm::QQ {
	void LinkDC::InitLink() {
		DC::LinkQQ Obj;
		Obj.OutputMsg(InputMsg);
	}
	void LinkDC::InputMsg(nlohmann::json obj) {
		std::cout << "QQ函数回调" << std::endl;

		std::string str = std::string(obj["channel_id"]);
		std::stringstream ss(str);
		dpp::snowflake tmp;
		ss >> tmp;

		RealmQQ::GetRealmBot()->getApiSet().
			sendGroupMsg(RealmHashQQ::GetGroup(tmp), ((std::string)obj["usernamecustom"] + ":" + (std::string)obj["content"]));
	}

	void LinkDC::OutputMsg(void(*Send)(nlohmann::json obj)) {
		RealmQQ::GetRealmBot()->onEvent<twobot::Event::GroupMsg>([Send](const twobot::Event::GroupMsg& msg) {
			//debug
			std::cout << msg.raw_msg << std::endl;

			uint64_t Group_id = msg.raw_msg["group_id"];
			for (nlohmann::json tmp : msg.raw_msg["message"]) {
				if (tmp["type"] == "image")
					RealmQQ::GetRealmBot()->getApiSet().getImage(Group_id, tmp["data"]["file"]);
			}

			(*Send)(msg.raw_msg);
			});

	}
	void LinkDC::InputRecall(nlohmann::json obj) {

	}
	void LinkDC::OutRecall(void(*Send)(nlohmann::json obj)) {

	}
}
