#pragma once
namespace Realm {

//设定好双方或多方的领域
class Realm {
public:
	// 实例不能复制
	Realm(const Realm&) = delete;
	Realm(const Realm&&) = delete;
	Realm operator=(const Realm&) = delete;
	Realm operator=(const Realm&&) = delete;

public:
	typedef int A;

public:
	Realm* on_event();


private:

};

}