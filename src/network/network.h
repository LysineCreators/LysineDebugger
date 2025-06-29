#ifndef NETWORK_H
#define NETWORK_H

#include <boost/asio/io_context.hpp>
#include <thread>

namespace net = boost::asio; // 追加

// サーバーを起動するためのグローバルな変数 (extern 宣言)
extern net::io_context ioc;
extern std::thread server_thread;

// サーバーを起動/停止する関数宣言
void start_server();
void stop_server();
int send2Client();
void send2Clientbysocket(int value);
void send2Clientbysocket(const std::string& message);
#endif // NETWORK_H
