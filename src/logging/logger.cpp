#include "logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip> // for std::put_time
#include <sstream> // for std::stringstream

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
    std::stringstream ss;
    ss << "LysineDebugger-" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%H-%M-%S") << ".log";
    log_file.open(ss.str(), std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error: Could not open log file." << std::endl;
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