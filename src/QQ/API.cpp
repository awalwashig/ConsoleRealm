#include <QQ/API.h>

namespace QQ {
API::API(std::string& ip){
	
}
API* API::set_token(std::string& param){
	token = param;
	return this;
}
API* API::on_message(){
	return this;
}
API::~API() {
	
}

}// namespace QQ