#include "RealmQQ.h"
#include "../base/Config.h"
#include <thread>

#include "RealmHashQQ.h"

namespace Realm {
	RealmQQ::RealmQQ() :ConfigQQ((*Base::RealmConfig::GetJsonConfig())["RealmQQ"]) {
		using twobot::Config;
		using twobot::BotInstance;
		using twobot::ApiSet;
		using namespace twobot::Event;

		// 解决UTF8编码，中文乱码问题，不需要可以不加
		// system("chcp 65001 && cls");

		RealmBot = BotInstance::createInstance(Config{
			"192.168.1.24",
			3001,
			5752,
			std::nullopt
			});
	}
	//加载
	void RealmQQ::QQInit() {

		std::thread([&]() {
			RealmBot->start();
			}).detach();

		RealmHashQQ::InitHash();
	}
	void RealmQQ::QQRun() {

	}
	//?
	void RealmQQ::QQQuit() {

	}
	void RealmQQ::SetInstance(RealmQQ* Instance) {
		s_Instance = Instance;
	}
	RealmQQ* RealmQQ::GetInstance() {
		return s_Instance;
	}
	twobot::BotInstance* RealmQQ::GetRealmBot() {
		return &*s_Instance->RealmBot;
	}
	RealmQQ* RealmQQ::s_Instance = nullptr;

	void InitRealmQQ() {
		RealmQQ::SetInstance(new RealmQQ);
	}
}