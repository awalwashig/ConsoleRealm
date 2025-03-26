#pragma once
#include <dpp/dpp.h>
#include <memory>

#include "message.h"

namespace Realm{
class discord {
public:
	discord();
	
	~discord() = default;

	

private:
	std::unique_ptr<dpp::cluster> m_bot;
};
	
}//End Realm