#include "init-support.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
// convert int to String
std::string FileTimeToString(const FILETIME& ft) {
    SYSTEMTIME stUTC, stLocal;
    FileTimeToSystemTime(&ft, &stUTC);
    SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);

    char buffer[100];
    sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
              stLocal.wYear, stLocal.wMonth, stLocal.wDay,
              stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
    return std::string(buffer);
}

// パスを引数にとって作成・アクセス・更新時刻を表示する関数
void PrintFileTimes(const std::string& path) {
    HANDLE hFile = CreateFileA(
        path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    FILETIME creationTime, accessTime, writeTime;
    if (GetFileTime(hFile, &creationTime, &accessTime, &writeTime)) {
        std::cout << "Debugger path    : " << path << "\n";
        std::cout << "Creation time    : " << FileTimeToString(creationTime) << "\n";
        std::cout << "Last access time : " << FileTimeToString(accessTime) << "\n";
        std::cout << "Last write time  : " << FileTimeToString(writeTime) << "\n";
    } else {
        std::cerr << "Failed to get file times." << std::endl;
    }

    CloseHandle(hFile);
}
//この関数を呼び出したプログラムのPathを戻り値で返す関数
std::string GetOwnExecutablePath() {
    char path[MAX_PATH];
    DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
    if (length == 0 || length == MAX_PATH) {
        return ""; // 失敗
    }
    return std::string(path, length);
}
//CっぽいPrintを追加する糞コード
void CPrint(const std::string print){
    std::cout << print << std::endl;
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


std::string init_support_ver(){ 
    return "1.0.0";
}

