#pragma once
namespace Realm {

//�趨��˫����෽������
class Realm {
public:
	// ʵ�����ܸ���
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