#include "pch/pch.h"
#include "Util.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <windows.h>
#include <shlobj.h>

namespace fs = std::filesystem;

namespace Util {

    std::string GetAppDataFolder() {
        wchar_t path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, path))) {
            std::wstring folder = std::wstring(path) + L"\\CustomRP\\";
            fs::create_directories(folder);
            return std::string(folder.begin(), folder.end());
        }
        return "";
    }

    bool EnsureDirectoryExists(const std::string& path) {
        try {
            return fs::create_directories(path) || fs::exists(path);
        }
        catch (...) {
            return false;
        }
    }

    bool EnsureFileExists(const std::string& path, const std::string& defaultContent) {
        if (!fs::exists(path)) {
            std::ofstream out(path);
            if (!out.is_open()) return false;
            out << defaultContent;
            out.close();
        }
        return true;
    }

}
