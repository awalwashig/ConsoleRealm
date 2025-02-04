#pragma once

#include <functional>
#include <nlohmann/json.hpp>

namespace Realm {

using json = nlohmann::json;

/* 确保了起到交换的作用
 * 
 */
class Realm {
public:


public:
	// 实例不能复制
	Realm(const Realm&) = delete;
	Realm(const Realm&&) = delete;
	Realm operator=(const Realm&) = delete;
	Realm operator=(const Realm&&) = delete;
private:

};



}//namespace Realm