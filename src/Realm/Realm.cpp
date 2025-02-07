#include <Realm/Realm.h>
namespace Realm {

template<typename ...Types>
inline Realm<Types...>::Realm(APIs test)
	:ooo(test){
	std::cout << "okey" << std::endl;
}

}//namespace Realm