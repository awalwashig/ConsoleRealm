#include <Realm/Realm.h>

#include <dpp/cluster.h>
#include <QQ/API.h>

int main(int argc, char* argv[]) {
	//std::tuple<QQ::API, dpp::cluster> args(QQ::API(), dpp::cluster());


	Realm::Realm instance(1, dpp::cluster("a"));

	std::get<dpp::cluster>(instance.contact).message_create(dpp::message());
}