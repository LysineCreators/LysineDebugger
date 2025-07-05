#include "logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip> // for std::put_time
#include <sstream> // for std::stringstream
#include <filesystem> // For std::filesystem
#include "./../Kit/init-support.h"

std::ofstream log_file;

// タイムスタンプをフォーマットするヘルパー関数
std::string get_current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void initialize_logger() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss_dir;
    std::stringstream ss_file;

    // ログディレクトリのパスを生成 (例: logs/YYYY-MM-DD)
    ss_dir << "logs/" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    std::string log_dir_path = ss_dir.str();

    // ディレクトリが存在しない場合は作成
    // create_directoriesは親ディレクトリも同時に作成します
    if (!std::filesystem::create_directories(log_dir_path)) {
        // ディレクトリ作成に失敗した場合、または既に存在する場合
        // エラーハンドリングをここに追加できます
        if (!std::filesystem::exists(log_dir_path)) {
            std::cerr << "Error: Could not create log directory: " << log_dir_path << std::endl;
            return; // ログファイルを開くのを中止
        }
    }

    // ログファイルのパスを生成
    ss_file << log_dir_path << "/LysineDebugger-" << std::put_time(std::localtime(&in_time_t), "%H-%M-%S") << ".log";
    
    log_file.open(ss_file.str(), std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error: Could not open log file: " << ss_file.str() << std::endl;
    }
}

void log_message(const std::string& message) {
    if (log_file.is_open()) {
        log_file << "[" << get_current_timestamp() << "] " << message << std::endl;
    } else {
        std::cerr << "Log file not open. Message: " << message << std::endl;
    }
}

void shutdown_logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}