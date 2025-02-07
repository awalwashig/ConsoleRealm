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

	
public:
	typedef std::tuple<Types...> APIs;

public:
	Realm(APIs test);

	// ʵ�����ܸ���
	Realm(const Realm&) = delete;
	Realm(const Realm&&) = delete;
	Realm operator=(const Realm&) = delete;
	Realm operator=(const Realm&&) = delete;
private:
	APIs ooo;
};

}//namespace Realm