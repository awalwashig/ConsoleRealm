#pragma once

#include <functional>
#include <iostream>
#include <tuple>
#include <nlohmann/json.hpp>
#include <map>

namespace Realm {

using json = nlohmann::json;

/**ȷ�����𵽽���������
 * 
 */
template<typename ...Types>
class contact {
	friend class Realm;

public:
	//����
	using APIs = std::tuple<Types...>;
public:
	

public:
	explicit contact(Types... param)
		: contact(std::forward<Types>(param)...) {

	}

	// ʵ�����ܸ���
	contact(const contact&) = delete;
	contact(const contact&&) = delete;
	contact operator=(const contact&) = delete;
	contact operator=(const contact&&) = delete;
public:
	APIs m_contact;
};

}//namespace Realm