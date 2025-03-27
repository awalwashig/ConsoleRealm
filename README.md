# [控制台境界]
不知道为什么就是想到了这个（

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
g++ Application.cpp Application.h -std=c++20 -l"dpp" -l"pthread" -l"curl"
```

docker（还没搓好）