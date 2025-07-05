#include <iostream>
#include <string>
#include <cctype>

#include "./../Kit/init-support.h"
#include "./../network/network.h"
#include "./../logging/logger.h" // 新しいロギングヘッダー

using namespace std;

std::string  LDP_version(){
    return "1.1.0";
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

void send_int(){
    std::string input_str;
    std::cout << "Enter message to send: ";
    std::cin >> input_str;

    try {
        int value = std::stoi(input_str);
        send2Clientbysocket(value);
        log_message("Sent int '" + input_str + "' to client.");
        std::cout << "Sent int '" << input_str << "' to client." << std::endl;
    } catch (const std::invalid_argument& e) {
        send2Clientbysocket(input_str);
        log_message("Sent string '" + input_str + "' to client.");
        std::cout << "Sent string '" << input_str << "' to client." << std::endl;
    } catch (const std::out_of_range& e) {
        send2Clientbysocket(input_str);
        log_message("Sent string (out of range) '" + input_str + "' to client.");
        std::cout << "Sent string (out of range) '" << input_str << "' to client." << std::endl;
    }
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
                    log_message("qsh: start,exit,help,hug,netch,send");
                    std::cout << "qsh: start,exit,help,hug,netch,send" << std::endl; // コンソールにも出力
                    log_message("qsh: OK");
                    std::cout << "qsh: OK" << std::endl; // コンソールにも出力
                }else if(command == "send"){
                    send_int();
                }else if(command == "netch"){
                    log_message("netch");
                    netch();
                    log_message("qsh: OK");
                    std::cout << "qsh: OK" << std::endl; // コンソールにも出力
                }else{
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
