#pragma once
#include <dpp/dpp.h>
#include "../RealmDC/LinkQQ.h"

namespace Realm::QQ {
	class LinkDC {
	public:
		static void InitLink();

		static void InputMsg(nlohmann::json obj);
		static void OutputMsg(void(*Send)(nlohmann::json obj));

		static void InputRecall(nlohmann::json obj);
		static void OutRecall(void(*Send)(nlohmann::json obj));
	private:

		//static Link* s_Instance;
	};
}