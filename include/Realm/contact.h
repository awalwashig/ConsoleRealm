#pragma once

#include <functional>
#include <iostream>
#include <tuple>
#include <nlohmann/json.hpp>
#include <map>

namespace Realm {

using json = nlohmann::json;

/**确保了起到交换的作用
 * 
 */
template<typename ...Types>
class contact {
	friend class Realm;

public:
	//类型
	using APIs = std::tuple<Types...>;
public:
	

public:
	explicit contact(Types... param)
		: contact(std::forward<Types>(param)...) {

	}

	// 实例不能复制
	contact(const contact&) = delete;
	contact(const contact&&) = delete;
	contact operator=(const contact&) = delete;
	contact operator=(const contact&&) = delete;
public:
	APIs m_contact;
};

}//namespace Realm