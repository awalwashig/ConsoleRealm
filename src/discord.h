#pragma once
#include <dpp/dpp.h>

#include "message.h"

namespace Realm{
class discord {
public:
	discord() = default;
	
	~discord() = default;

	

private:
	dpp::cluster bot;
};
	
}//End Realm