#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

namespace QQ {

using json = nlohmann::json;


class request_queue {
public:

	typedef std::variant<websocketpp::client<websocketpp::config::asio_client>&, json&> message;
	std::variant<websocketpp::client<websocketpp::config::asio_client>> client;	
};



}