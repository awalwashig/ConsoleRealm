#pragma once
#include "discord.h"
#include "qq.h"
#include "config.h"

namespace Realm {
class ConsoleRelam {
public:
	ConsoleRelam();
	~ConsoleRelam() = default;


	void Config(std::string_view path);
private:
	
	discord dcbot;
	qq qqbot;

};

}