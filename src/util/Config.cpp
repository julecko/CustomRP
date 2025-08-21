#include "pch/pch.h"
#include "Config.h"
#include "util/Util.h"
#include <fstream>

Config config;
const std::vector<std::string> required = { "DISCORD_CLIENT_ID" };

void Config::init(const std::string& filename) {
    this->filename = Util::GetAppDataFolder() + filename;
    Util::EnsureDirectoryExists(Util::GetAppDataFolder());
    Util::EnsureFileExists(this->filename, "# Default config\n");
}

bool Config::load() {
    std::ifstream in(this->filename);
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#') continue;

            auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            this->data[key] = value;
        }
        in.close();
    }

    for (const auto& key : required) {
        if (this->data.find(key) == this->data.end()) {
            this->data[key] = "";
        }
    }

    return save();
}

bool Config::save() const {
    std::ofstream out(this->filename);
    if (!out.is_open()) return false;

    for (const auto& [key, value] : this->data) {
        out << key << "=" << value << "\n";
    }
    return true;
}

std::string Config::get(const std::string& key) const {
    auto it = this->data.find(key);
    return (it != this->data.end()) ? it->second : "";
}

void Config::set(const std::string& key, const std::string& value) {
    this->data[key] = value;
}
