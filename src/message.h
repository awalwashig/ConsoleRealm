#pragma once
#include <string>
#include <string_view>
#include <variant>

#include <dpp/dpp.h>

namespace Realm {

class MessageQueue {
public:
	std::variant<dpp::message_create_t, nlohmann::json> input;
public:

	MessageQueue() = default;

	~MessageQueue() = default;

	void push();

private:

};

}//End Realm