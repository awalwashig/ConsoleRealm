#pragma once
#include <nlohmann/json.hpp>
#include "../RealmQQ/LinkDC.h"

#include "RealmHashDC.h"


namespace Realm::DC {
	class LinkQQ {
	public:
		static void InitLink();

		static void InputMsg(nlohmann::json obj);
		static void OutputMsg(void(*Send)(nlohmann::json obj));

		static void InputRecall(nlohmann::json& obj);
		static void OutRecall(void(*Send)(nlohmann::json obj));

	private:
		static std::string GetImageURL(nlohmann::json& Obj);
	};
}