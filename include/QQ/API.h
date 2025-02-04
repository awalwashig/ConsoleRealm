#pragma once
#include <iostream>
#include <QQ/Link.h>

namespace QQ {

class API {
public:
	API() noexcept = default;

	API(std::string& ip);

	API* set_token();

	API* on_message();
	
	~API();
private:
	std::string token;
	
	
};

}