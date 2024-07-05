﻿#include "LinkDC.h"
#include "RealmQQ.h"

#include <iostream>

namespace Realm::QQ {
	void LinkDC::InitLink(){

	}
	void LinkDC::Input(nlohmann::json obj){

		std::cout << "QQ函数回调" << std::endl;

	}

	void LinkDC::output(void(*Send)(nlohmann::json obj)){
		RealmQQ::GetRealmBot()->onEvent<twobot::Event::GroupMsg>([Send](const twobot::Event::GroupMsg& msg) {

			//debug
			std::cout << msg.sender << std::endl;

			(*Send)(msg.sender);
			});

	}
}