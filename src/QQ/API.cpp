#include <QQ/API.h>

namespace QQ {
API::API(std::string ip)
	:ip(ip){
	
}

API* API::on_message(){
	return this;
}
API::~API() {
	
}

}// namespace QQ