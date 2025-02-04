#pragma once
#include <Realm/WebSocket.h>
#include <Realm/Realm.h>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

// 定义客户端类型（使用无 TLS 的配置）
typedef websocketpp::client<websocketpp::config::asio_client> client;

// 为简化书写，使用命名空间中的占位符和 bind
using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace Realm::test {
    void on_message(client* c, connection_hdl hdl, client::message_ptr msg) {
        std::cout << msg->get_payload() << std::endl;

        //// 将接收到的消息原样发送回去
        //websocketpp::lib::error_code ec;
        //c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
        //if (ec) {
        //    std::cout << "发送回显失败，原因: " << ec.message() << std::endl;
        //}
    }

    void test() {

    }

	void WebSocketTest() {
        // 创建客户端实例
        client c;

        try {
            // 可选：设置日志（这里启用了全部日志，但排除了帧数据内容以免过多）
            c.set_access_channels(websocketpp::log::alevel::all);
            c.clear_access_channels(websocketpp::log::alevel::frame_payload);

            // 初始化 Asio
            c.init_asio();

            // 注册消息处理函数，当有消息到达时调用 on_message
            c.set_message_handler(bind(&on_message, &c, _1, _2));

            // 设定要连接的 WebSocket URI
            std::string uri = "ws://172.22.1.1:5321";
            websocketpp::lib::error_code ec;

            // 创建连接对象
            client::connection_ptr con = c.get_connection(uri, ec);
            if (ec) {
                std::cout << "无法创建连接，原因: " << ec.message() << std::endl;
            }

            // 发起连接
            c.connect(con);

            // 启动 Asio io_service 的运行循环（此调用会阻塞直到连接关闭）
            c.run();
        }
        catch (websocketpp::exception const& e) {
            std::cout << "异常: " << e.what() << std::endl;
        }
	}
}