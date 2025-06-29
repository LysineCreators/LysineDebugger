#include <iostream>
#include <string>
#include <cctype>

#include "src/Kit/init-support.cpp"
#include "src/network/network.h"
#include "src/logging/logger.h" // 新しいロギングヘッダー

using namespace std;

std::string  LDP_version(){
    return "1.0.0";
}
void netch(){    //logo表示とかバージョン云々
    CPrint("");
    CPrint("################################################");
    CPrint("   __       __  __    ______    __    ______ ___     ______               ");
    CPrint("  /\\ \\     /\\ \\_\\ \\  /\\   __\\  /\\_\\  /\\  _  \\\\  \\  /\\  ____\\          ");
    CPrint("  \\ \\ \\__  \\ \\____ \\ \\ \\____ \\ \\/\\ \\ \\ \\ \\\\  \\\\  \\ \\ \\  ____\\                        "); 
    CPrint("   \\ \\____\\ \\/___/\\ \\ \\/\\_____\\ \\ \\ \\ \\ \\_\\\\______\\ \\ \\______\\                       ");
    CPrint("    \\/____/      \\/_/  \\/_____/  \\/_/  \\/_/_______/  \\/______/                       ");
    CPrint("");
    CPrint("################################################");
    CPrint("   Lysine");
    CPrint("   Debugger");
    CPrint("   Pro");
    CPrint("   Created by CloverTech1105");
    CPrint("##################[Build data]##################");
    PrintFileTimes(GetOwnExecutablePath());
    CPrint("################[Module version]################");
    CPrint("init_kit Version : " + init_support_ver());
    CPrint("LDP Version      : " + LDP_version());
}


int main() {
    initialize_logger(); // ロガーを初期化
    netch();
    log_message("[i]Application started.");
    std::cout << "[i]Application started." << std::endl; // コンソールにも出力
    log_message("[i]Debug Server is starting...");
    std::cout << "[i]Debug Server is starting..." << std::endl; // コンソールにも出力
    start_server();
    
    std::string command;
    std::string qsh = "LDPConsole";
    std::cout << qsh + ":/>";
    while (std::cin >> command){

                if (command == "start"){
                    start_server();
                    log_message("OK");
                    std::cout << "OK" << std::endl; // コンソールにも出力
                }else if(command == "exit"){
                    log_message("qsh: OK");
                    std::cout << "qsh: OK" << std::endl; // コンソールにも出力
                    log_message("[i]exit form LDP's command!");
                    break;
                }else if(command == "help"){
                    log_message("qsh: start,exit,help,hug,netch,send_text");
                    std::cout << "qsh: start,exit,help,hug,netch,send_text" << std::endl; // コンソールにも出力
                    log_message("qsh: OK");
                    std::cout << "qsh: OK" << std::endl; // コンソールにも出力
                }else if(command == "send_text"){
                    send2Clientbysocket("AVC");
                    log_message("Sent 'AVC' to client.");
                    std::cout << "Sent 'AVC' to client." << std::endl; // コンソールにも出力
                }else if(command == "netch"){
                    netch();
                }else {
                    log_message(command + " is unavabile command!");
                    std::cout << command + " is unavabile command!" << std::endl; // コンソールにも出力
                }
            // ここで標準入力からのログ行の処理は不要になるため削除
            // if(command == "exit"){
            //     break;
            // }
            std::cout << qsh +  ":/>";
            } 
            shutdown_logger(); // ロガーをシャットダウン
    return 0;
}
