#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "init-support.cpp"

using namespace std;
std::string formatTime(int timestamp);


int main() {
    CPrint("");
    cout << "Lysine Logger V1" << endl;
    CPrint("Hello");
    PrintFileTimes(GetOwnExecutablePath());

    int timestamp = static_cast<int>(std::time(nullptr));  // 現在の時刻を取得
    std::string formattedTime = formatTime(timestamp);


    //// ログファイルを開く（追記モード）
    std::ofstream log_file("LysineDebugger-"+ formattedTime + ".log", std::ios::app);
    std::string log_line;

    while (std::getline(std::cin, log_line)) {  // 標準入力から1行ずつ受信
        std::cout << "Godot Log: " << log_line << std::endl; // コンソールに出力
        log_file << log_line << std::endl; // ファイルに保存
    }

    log_file.close();
    return 0;
}

std::string formatTime(int timestamp) {
    // time_t に変換
    std::time_t rawTime = static_cast<std::time_t>(timestamp);
    std::tm* timeinfo = std::localtime(&rawTime);

    // AM or PM 判定
    std::string am_pm = (timeinfo->tm_hour < 12) ? "AM" : "PM";

    // 12時間形式の時間
    int hour12 = timeinfo->tm_hour % 12;
    if (hour12 == 0) hour12 = 12;  // 0時 or 12時の場合に対応

    // 文字列に変換
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d-")  // 日付
        << am_pm << '-'                          // AM/PM
        << std::setw(2) << std::setfill('0') << hour12 << '-'  // hh
        << std::setw(2) << std::setfill('0') << timeinfo->tm_min << '-'  // mm
        << std::setw(2) << std::setfill('0') << timeinfo->tm_sec;        // ss

    return oss.str();
}