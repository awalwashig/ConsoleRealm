#pragma once
#include <iostream>
#include <QQ/Web.h>

namespace QQ {

class API {
public:
	API() noexcept = default;

	API(std::string& ip);

	API* set_token(std::string& param);

	API* on_message();
	
	~API();
private:
	std::string token;
	
	
};

}