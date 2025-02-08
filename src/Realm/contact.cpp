#include <Realm/contact.h>

namespace Realm {

template<typename ...Types>
contact<Types...>::contact(Types... param)
    : contact(std::forward<Types>(param)...) {

}

}//namespace Realm