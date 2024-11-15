﻿#pragma once

#include <unordered_map>
#include <dpp/dpp.h>

namespace Realm {
	class RealmHashDC {
	public:
		static void InitHash();

		static void AddFuntionHash(std::string Command, void(*Funtion)(dpp::slashcommand_t*));

		static dpp::snowflake GetChannel(int _id);

		static std::unique_ptr<std::unordered_map<std::string, void(*) (dpp::slashcommand_t*)>> FuntionHash;

		static std::unique_ptr<std::unordered_map<int, dpp::snowflake>> channelHash;

		static std::unique_ptr<std::unordered_map<int, dpp::snowflake>> messageHash;

		static std::unique_ptr<std::unordered_map<dpp::snowflake, std::string>>ImageHash;
	};
}