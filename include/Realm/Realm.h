#pragma once

#include <functional>
#include <nlohmann/json.hpp>

namespace Realm {

using json = nlohmann::json;

/* ȷ�����𵽽���������
 * 
 */
class Realm {
public:


public:
	// ʵ�����ܸ���
	Realm(const Realm&) = delete;
	Realm(const Realm&&) = delete;
	Realm operator=(const Realm&) = delete;
	Realm operator=(const Realm&&) = delete;
private:

};



}//namespace Realm