#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <ctime>
#include "./../Kit/init-support.cpp"
void writelog(){  
   //// ログファイルを開く（追記モード）
            std::ofstream log_file("LysineDebugger-"+ formattedTime + ".log", std::ios::app);
           std::string log_line;

              while (std::getline(std::cin, log_line)) {  // 標準入力から1行ずつ受信
                std::cout << "Godot Log: " << log_line << std::endl; // コンソールに出力
               log_file << log_line << std::endl; // ファイルに保存
           }

            log_file.close();
}