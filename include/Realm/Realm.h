#pragma once

#include <functional>
#include <iostream>
#include <tuple>
#include <nlohmann/json.hpp>

namespace Realm {

using json = nlohmann::json;

/* 确保了起到交换的作用
 * 
 */
template<typename ...Types>
class Realm {
public:
	//类型
	using APIs = std::tuple<Types...>;

public:


public:
	Realm(Types... param) : contact(std::forward<Types>(param)...) {
		//(std::cout << ... << (std::get<Types>(param))) << std::endl;
	}

	// 实例不能复制
	Realm(const Realm&) = delete;
	Realm(const Realm&&) = delete;
	Realm operator=(const Realm&) = delete;
	Realm operator=(const Realm&&) = delete;
public:
	APIs contact;
};

}//namespace Realm