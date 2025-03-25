/*这个是作为一个引入的文件
*
*/

#pragma once
#include "base/Config.h"

int main(int argc, char** argv);

namespace Realm {

	class Application {
	public:
		Application* Init();
		Application* Run();
		Application* Quit();

		Application();
		~Application();
	private:
		static Application* CreateApplication();
		friend int ::main(int argc, char** argv);
		static Application* s_Instance;
	private:

	};
}
