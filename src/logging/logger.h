#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// ロギング関数
void log_message(const std::string& message);
void initialize_logger();
void shutdown_logger();

#endif // LOGGER_H