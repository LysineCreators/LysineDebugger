#include "network.h" // 外部から参照される関数や変数の宣言を含むヘッダーファイル
#include <boost/beast/core.hpp>      // Boost.Beast のコア機能 (エラーハンドリング、バッファなど)
#include <boost/beast/websocket.hpp> // Boost.Beast のWebSocketプロトコル実装
#include <boost/asio/ip/tcp.hpp>     // Boost.Asio のTCP/IPネットワーク機能
#include <cstdlib>                   // 一般的なユーティリティ関数 (例: EXIT_SUCCESS)
#include <functional>                // 関数オブジェクト (例: std::function)
#include <iostream>                  // 標準入出力ストリーム (例: std::cout, std::cerr)
#include <string>                    // 文字列クラス (std::string)
#include <thread>                    // スレッド機能 (std::thread)
#include <vector>                    // 動的配列 (std::vector)

// Boost.Beast の名前空間エイリアス
namespace beast = boost::beast;
// Boost.Beast のWebSocket名前空間エイリアス
namespace websocket = beast::websocket;
// Boost.Asio の名前空間エイリアス
namespace net = boost::asio;
// TCPプロトコルのエイリアス
using tcp = boost::asio::ip::tcp;

// エラー発生時に情報を出力するヘルパー関数
// ec: エラーコード
// what: エラーが発生した場所や操作の説明
void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// 個々のWebSocketセッションを処理する関数
// クライアントからの接続を受け付け、メッセージをエコーバックする
// socket: クライアントとの通信に使用するTCPソケット (値渡しで所有権を移動)
void do_session(tcp::socket socket)
{
    try
    {
        // WebSocketストリームを作成し、ソケットを移動して関連付ける
        websocket::stream<tcp::socket> ws{std::move(socket)};
        
        // WebSocketハンドシェイクを受け付ける
        ws.accept();

        // 無限ループでメッセージの読み書きを行う
        for(;;)
        {
            // 受信したデータを格納するためのバッファ
           
             beast::flat_buffer buffer;
            // クライアントからメッセージを読み込む
            ws.read(buffer);
            
            // 受信したメッセージがテキスト形式であれば、送信もテキスト形式で行う
            ws.text(ws.got_text());
            
            // 受信したメッセージをそのままクライアントにエコーバックする
            ws.write(buffer.data());

            


















            
        }
    }
    // Boost.Beast のシステムエラーをキャッチ
    catch(beast::system_error const& se)
    {
        // 接続切断エラーでなければ、エラー情報を出力
        if(se.code() != websocket::error::closed)
            fail(se.code(), "session");
    }
    // その他の標準例外をキャッチ
    catch(std::exception const& e)
    {
        std::cerr << "Error in session: " << e.what() << std::endl;
    }
}

// WebSocketサーバーのメインロジック
// クライアントからの接続を待ち受け、新しいセッションを生成する
// ioc: Boost.Asio のI/Oコンテキスト
void server_logic(net::io_context& ioc)
{
    try
    {
        // サーバーがリッスンするIPアドレス (ここではすべてのインターフェース)
        auto const address = net::ip::make_address("0.0.0.0");
        // サーバーがリッスンするポート番号
        auto const port = static_cast<unsigned short>(8080);

        // TCPアクセプタを作成し、指定されたアドレスとポートで待ち受けを開始
        tcp::acceptor acceptor{ioc, {address, port}};
        std::cout << "WebSocket server listening on " << address.to_string() << ":" << port << std::endl;

        // 無限ループで新しい接続を待ち受ける
        for(;;)
        {
            // 新しい接続のためのソケットを作成
            tcp::socket socket{ioc};
            
            // クライアントからの接続を受け付ける
            acceptor.accept(socket);
            
            // 新しいスレッドでWebSocketセッションを処理し、スレッドをデタッチする
            // デタッチすることで、メインスレッドがセッションスレッドの終了を待たずに続行できる
            std::thread(&do_session, std::move(socket)).detach();
        }
    }
    // 標準例外をキャッチし、エラー情報を出力
    catch (const std::exception& e)
    {
        std::cerr << "Error in server_logic: " << e.what() << std::endl;
    }
}

// サーバーのI/O処理を行うコンテキスト
// グローバル変数として定義され、複数のスレッドからアクセスされる可能性がある
net::io_context ioc;
// サーバーのメインロジックを実行するスレッド
// グローバル変数として定義され、サーバーの起動/停止を制御するために使用される
std::thread server_thread;

// サーバーを起動する関数
// サーバーが既に実行中でなければ、新しいスレッドでサーバーロジックを開始する
void start_server()
{
    // iocが停止している場合、リセットして再利用可能にする
    if (ioc.stopped()) {
        ioc.restart();
    }
    
    // サーバーが既に実行中でなければ新しいスレッドで起動
    if (!server_thread.joinable()) {
        // ラムダ式を使用して、サーバーロジックとioc.run()を新しいスレッドで実行
        server_thread = std::thread([&]() {
            server_logic(ioc); // サーバーの接続待ち受けロジック
            ioc.run();         // I/O操作を実行
        });
        std::cout << "Server started." << std::endl;
    } else {
        std::cout << "Server is already running." << std::endl;
    }
}

// サーバーを停止する関数
// サーバーが実行中であれば、I/Oコンテキストを停止し、サーバーのスレッドの終了を待つ
void stop_server()
{
    if (server_thread.joinable())
    {
        ioc.stop(); // io_contextを停止してacceptorのブロックを解除し、すべてのI/O操作を停止
        server_thread.join(); // スレッドの終了を待つ (クリーンアップのため)
        std::cout << "Server stopped." << std::endl;
    } else {
        std::cout << "Server is not running." << std::endl;
    }
}

// このサンプルコードのメイン関数
// 実際のアプリケーションでは、このmain関数を独自のロジックに置き換えるか、
// 別の場所でstart_server()とstop_server()を呼び出す
// int main()
// {
//    std::cout << "Application started. Type 'start' to run the server, 'stop' to halt it, and 'exit' to quit." << std::endl;
//
//    std::string command;
//    while (std::cin >> command)
//    {
//        if (command == "start")
//        {
//            start_server();
//        }
//        else if (command == "stop")
//        {
//            stop_server();
//        }
//        else if (command == "exit")
//        {
//            stop_server(); // 終了前にサーバーを停止
//            break;
//        }
//    }
//
//    return EXIT_SUCCESS;
// }