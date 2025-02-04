#pragma once
#include <Realm/WebSocket.h>
#include <Realm/Realm.h>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

// ����ͻ������ͣ�ʹ���� TLS �����ã�
typedef websocketpp::client<websocketpp::config::asio_client> client;

// Ϊ����д��ʹ�������ռ��е�ռλ���� bind
using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace Realm::test {
    void on_message(client* c, connection_hdl hdl, client::message_ptr msg) {
        std::cout << msg->get_payload() << std::endl;

        //// �����յ�����Ϣԭ�����ͻ�ȥ
        //websocketpp::lib::error_code ec;
        //c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
        //if (ec) {
        //    std::cout << "���ͻ���ʧ�ܣ�ԭ��: " << ec.message() << std::endl;
        //}
    }

    void test() {

    }

	void WebSocketTest() {
        // �����ͻ���ʵ��
        client c;

        try {
            // ��ѡ��������־������������ȫ����־�����ų���֡��������������ࣩ
            c.set_access_channels(websocketpp::log::alevel::all);
            c.clear_access_channels(websocketpp::log::alevel::frame_payload);

            // ��ʼ�� Asio
            c.init_asio();

            // ע����Ϣ��������������Ϣ����ʱ���� on_message
            c.set_message_handler(bind(&on_message, &c, _1, _2));

            // �趨Ҫ���ӵ� WebSocket URI
            std::string uri = "ws://172.22.1.1:5321";
            websocketpp::lib::error_code ec;

            // �������Ӷ���
            client::connection_ptr con = c.get_connection(uri, ec);
            if (ec) {
                std::cout << "�޷��������ӣ�ԭ��: " << ec.message() << std::endl;
            }

            // ��������
            c.connect(con);

            // ���� Asio io_service ������ѭ�����˵��û�����ֱ�����ӹرգ�
            c.run();
        }
        catch (websocketpp::exception const& e) {
            std::cout << "�쳣: " << e.what() << std::endl;
        }
	}
}