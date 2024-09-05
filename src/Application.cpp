#include <ConsoleRealm.h>

int main() {
	dpp::cluster bot("MTE0MDE2NjU3ODE3NzA2OTA3Nw.Gkh0eS.8l_NIfiGGGs61oQPnorpPTGJTS7QNvTSzDpVXc");
	bot.on_log(dpp::utility::cout_logger());
	bot.start(dpp::st_wait);
	return 9;
}