#include <dpp/cluster.h>
#include <QQ/API.h>

#include <Realm/Application.h>
#include <Realm/contact.h>
#include <Realm/Realm.h>

int main(int argc, char* argv[]) {

	Realm::contact A(QQ::API(""));

	std::get<QQ::API>(A.m_contact).on_message();
} 