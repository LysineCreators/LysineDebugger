#include <windows.h>
#include <iostream>
#include <string>


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
        std::cout << "File path        : " << path << "\n";
        std::cout << "Creation time    : " << FileTimeToString(creationTime) << "\n";
        std::cout << "Last access time : " << FileTimeToString(accessTime) << "\n";
        std::cout << "Last write time  : " << FileTimeToString(writeTime) << "\n";
    } else {
        std::cerr << "Failed to get file times." << std::endl;
    }

    CloseHandle(hFile);
}
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