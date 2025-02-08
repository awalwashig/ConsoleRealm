#pragma once

#include <functional>
#include <iostream>
#include <tuple>
#include <nlohmann/json.hpp>

namespace Realm {

using json = nlohmann::json;

/* ȷ�����𵽽���������
 * 
 */
template<typename ...Types>
class Realm {
public:
	//����
	using APIs = std::tuple<Types...>;

public:


public:
	Realm(Types... param) : contact(std::forward<Types>(param)...) {
		//(std::cout << ... << (std::get<Types>(param))) << std::endl;
	}

	// ʵ�����ܸ���
	Realm(const Realm&) = delete;
	Realm(const Realm&&) = delete;
	Realm operator=(const Realm&) = delete;
	Realm operator=(const Realm&&) = delete;
public:
	APIs contact;
};

}//namespace Realm