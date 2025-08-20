#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Config {
public:
    Config() = default;

    void init(const std::string& filename);
    bool load();
    bool save() const;
    std::string get(const std::string& key) const;
    void set(const std::string& key, const std::string& value);

private:
    std::string filename;
    std::unordered_map<std::string, std::string> data;
};

extern Config config;
