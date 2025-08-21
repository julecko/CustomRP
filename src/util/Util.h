#pragma once
#include <string>

namespace Util {
    std::string GetAppDataFolder();       // Returns "C:\Users\<user>\AppData\Roaming\CustomRP\"
    bool EnsureDirectoryExists(const std::string& path); // Creates folder if missing
    bool EnsureFileExists(const std::string& path, const std::string& defaultContent = ""); // Creates file if missing
}
