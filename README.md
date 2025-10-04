# [ConsoleRealm]
不知道为什么就是想到了这个（

我还没完善docker，前面的区域以后再探索吧
~~说实话我不想完善，玩意有人找我喝茶了就不好了~~

~~只是qq和discord互相扔史的bot（bushi~~

~~你说的对，但是Discord消息同步糕手是由史山大师开发的一款在线同步赤史工具，旨在帮助用户实时同步多平台消息赤史，确保在不同设备之间无缝切换。传说这款工具的灵感源自史山大师多年来对通信技术赤史的深入研究以及对社交网络赤史发展趋势的敏锐赤史。随着Discord用户数量的激增，传统的消息同步方式显得力不从心，而这款工具正是为了填补这一空白而诞生的。~~
~~在研发过程中，史山大师秉持着追求极致完美赤史的精神，将先进的赤史技术与高效的分布式赤史系统完美结合。用户只需在入群，便可享受到在手机、平板、电脑等多终端之间赤史的消息传递体验，不再为信息长城或高级延迟而赤不到史烦恼。~~

> [!IMPORTANT]
> 2天搓出来的史山，触碰需谨慎!
> 需要root环境运行（

配置文件（记得修改源代码开头的定义）
```json
{
  "discord": {
    "token": "<token>",
    "webhook": "channel_webhook_",
    "channel": <channelID>,
    "cache": "<set__your_cache_path>"
  },
  "qq": {
    "ip": "<ip>",
    "http": <port>,
    "ws": <port>,
    "token": "114514",
    "group": 638380392,
    "domain_name": "https://<图床网址>", //图床需要设置 /root/.config/QQ （你也可以自己修改源代码）
    "useip": "http://<IP>:<port>"
  }
}
```

## build
不能编译（，没包括文件最好是下个vs2022（bushi)或者等我搓完docker
```bash
g++ -std=c++20 \ -Iinclude -Iinclude/twobot -Iinclude/twobot/include \ src/Application.cpp include/twobot/twobot.cc include/twobot/apiset.cc \ -o twobot -O2 -Wall -Wextra -pthread -ldpp -lcurl -lssl -lcrypto
```

docker（还没搓好）
