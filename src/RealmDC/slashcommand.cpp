#include "slashcommand.h"
#include "RealmDC.h"
#include "RealmHashDC.h"

namespace Realm {
	Slashcommand::Slashcommand() :RealmBot(RealmDC::GetRealmBot()) {

	}

	void Slashcommand::InitSlashcommand() {
		s_Instance = new Slashcommand();

		s_Instance->LoadSlashcommand();
		s_Instance->LoadSlashcommandFuntion();

		RunDeleteSlashcommand();
	}
	Slashcommand* Slashcommand::GetInstance() {
		return s_Instance;
	}
	void Slashcommand::RunDeleteSlashcommand() {
		delete s_Instance;
		s_Instance = nullptr;
	}

	void Slashcommand::LoadSlashcommand() {
		//写入命令
		RealmBot->on_ready([this](const dpp::ready_t event) {

			RealmBot->global_command_create(dpp::slashcommand("Ping", "Test slashcommand", RealmBot->me.id));
			RealmBot->global_command_create(dpp::slashcommand("Test", "Test slashcommand", RealmBot->me.id));
			RealmBot->global_command_create(dpp::slashcommand("kick", "这个命令会踢出服务器全部人！！！", RealmBot->me.id));
			RealmBot->global_command_create(dpp::slashcommand("ping", "ping?", RealmBot->me.id));

			});
	}

	//实现
	void Slashcommand::LoadSlashcommandFuntion() {
		//main
		RealmBot->on_slashcommand([](dpp::slashcommand_t event) {
			try {
				if ((*RealmHashDC::FuntionHash)[event.command.get_command_name()] == nullptr) {
					event.reply("~~没有这个命令的实现~~");
					throw "调用了空函数";
				}
				(*RealmHashDC::FuntionHash)[event.command.get_command_name()](&event);
			}
			catch (const char* msg) {
				std::cerr << msg << std::endl;
			}
			});

		//Funtion
		RealmHashDC::AddFuntionHash("Ping", [](dpp::slashcommand_t* event)->void {
			event->reply("Pong~");
			});
		RealmHashDC::AddFuntionHash("kick", [](dpp::slashcommand_t* event)->void {
			event->reply("https://images-ext-1.discordapp.net/external/vT3sHp6CIF4D7JMwNv8NEpmuGxibgAbTTwjqHezfhVw/https/media.tenor.com/giffyl_96U4AAAPo/rickroll-meme.mp4");
			});		
		RealmHashDC::AddFuntionHash("ping", [](dpp::slashcommand_t* event)->void {

			});
	}

	Slashcommand* Slashcommand::s_Instance = nullptr;
}