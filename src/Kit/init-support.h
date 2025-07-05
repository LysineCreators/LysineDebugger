#ifndef INIT_SUPPORT_H
#define INIT_SUPPORT_H

#include <string>
#include <windows.h> // FILETIME, HANDLE, etc.

// Function prototypes
std::string FileTimeToString(const FILETIME& ft);
void PrintFileTimes(const std::string& path);
std::string GetOwnExecutablePath();
void CPrint(const std::string print);
std::string formatTime(int timestamp);
std::string init_support_ver();

#endif // INIT_SUPPORT_H