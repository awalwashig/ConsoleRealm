﻿#include "RealmHashDC.h"
#include "RealmDC.h"
#include "../base/Config.h"

namespace Realm {
	void RealmHashDC::InitHash() {
		FuntionHash.reset(new std::unordered_map<std::string, void(*) (dpp::slashcommand_t*)>());

		channelHash.reset(new std::unordered_map<dpp::snowflake, dpp::snowflake>());

		ImageHash.reset(new std::unordered_map<dpp::snowflake, std::string>());

		for (int i = 0; i < (*Base::RealmConfig::GetJsonConfig())["RealmDC"]["Link"].size(); ++i) {
			dpp::snowflake QQtmp = (*Base::RealmConfig::GetJsonConfig())["RealmQQ"]["Link"][i];
			dpp::snowflake DCtmp = (*Base::RealmConfig::GetJsonConfig())["RealmDC"]["Link"][i];
			std::cout << QQtmp << ":" << DCtmp << std::endl;
			(*RealmHashDC::channelHash)[QQtmp] = DCtmp;
		}

	}
	void RealmHashDC::AddFuntionHash(std::string Command, void(*Funtion)(dpp::slashcommand_t*)) {
		(*FuntionHash)[Command] = Funtion;
	}

	//static
	std::unique_ptr<std::unordered_map<std::string, void(*) (dpp::slashcommand_t*)>> RealmHashDC::FuntionHash = nullptr;

	std::unique_ptr<std::unordered_map<dpp::snowflake, dpp::snowflake>> RealmHashDC::channelHash = nullptr;

	std::unique_ptr<std::unordered_map<dpp::snowflake, std::string>> RealmHashDC::ImageHash = nullptr;
}
