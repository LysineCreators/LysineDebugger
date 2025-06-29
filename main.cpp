#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <ctime>

#include "src/Kit/init-support.cpp"
#include "src/network/network.h"
using namespace std;
std::string formatTime(int timestamp);

std::string  LDP_version(){
    return "1.0.0";
}
int main() {
    //logo表示とかバージョン云々
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
    CPrint("[i]Application started.");
    CPrint("[i]Debug Server is starting...");
    start_server();
    int timestamp = static_cast<int>(std::time(nullptr));  // 現在の時刻を取得
    std::string formattedTime = formatTime(timestamp);
                std::ofstream log_file("LysineDebugger-"+ formattedTime + ".log", std::ios::app);
           std::string log_line;

              while (std::getline(std::cin, log_line)) {  // 標準入力から1行ずつ受信
                std::cout << "Godot Log: " << log_line << std::endl; // コンソールに出力
               log_file << log_line << std::endl; // ファイルに保存
           }

            log_file.close();
    return 0;
}
