#include <dpp/dpp.h>
#include <nlohmann/json.hpp>
#include <httplib.h>

namespace Realm {
	class ConsoleRealm {
	public:
		ConsoleRealm()
		{

		}


		void add_instance(std::unique_ptr<discord>&& obj);
		void add_instance(std::unique_ptr<qq>&& obj);
		//写一些主要管理操作
		//....
		
		//扩展功能
		virtual void EXoperation();
		void move_ptr();

	private:
		//现在要调用的实例
		std::unique_ptr<discord> DC;
		std::unique_ptr<qq> QQ;
	private:
		//储存的实例
		std::vector<std::string, std::pair<std::unique_ptr<discord>, std::unique_ptr<qq>>> obj_v;
	};

	class discord {

	};

	class qq {

	};
}