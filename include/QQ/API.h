#pragma once
#include <iostream>
#include <QQ/Web.h>

namespace QQ {

class API {
public:
	API() noexcept = default;

	API(std::string ip);

	~API();

public:
	API* on_message();
private:
	std::string token;
	std::string ip;
	
};

}