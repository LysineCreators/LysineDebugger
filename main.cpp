#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    cout << "Lysine Logger V1" << endl;
    std::ofstream log_file("godot_logs.txt", std::ios::app); // ログファイルを開く（追記モード）
    std::string log_line;

    while (std::getline(std::cin, log_line)) {  // 標準入力から1行ずつ受信
        std::cout << "Godot Log: " << log_line << std::endl; // コンソールに出力
        log_file << log_line << std::endl; // ファイルに保存
    }

    log_file.close();
    return 0;
}
