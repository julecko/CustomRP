#include "pch/pch.h"
#include "ProfileManager.h"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

ProfileManager::ProfileManager(const std::string& dir) : directory(dir) {
    EnsureDirectoryExists();
    LoadProfiles();
}

void ProfileManager::EnsureDirectoryExists() const {
    if (!fs::exists(this->directory)) {
        fs::create_directory(this->directory);
    }
}

std::string ProfileManager::GetFilePath(const std::string& profileName) const {
    return this->directory + "/" + profileName + ".txt";
}

void ProfileManager::LoadProfiles() {
    this->profiles.clear();
    if (!fs::exists(this->directory)) return;

    for (const auto& entry : fs::directory_iterator(this->directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            Profile p;
            if (p.LoadFromFile(entry.path().string())) {
                this->profiles.push_back(p);
            }
        }
    }
}

void ProfileManager::SaveProfiles() const {
    for (const auto& p : this->profiles) {
        p.SaveToFile(GetFilePath(p.GetName()));
    }
}

Profile* ProfileManager::GetProfile(const std::string& name) {
    auto it = std::find_if(this->profiles.begin(), this->profiles.end(),
        [&](const Profile& p) { return p.GetName() == name; });

    return (it != this->profiles.end()) ? &(*it) : nullptr;
}

void ProfileManager::AddProfile(const Profile& profile) {
    this->profiles.push_back(profile);
    this->profiles.back().SaveToFile(GetFilePath(profile.GetName()));
}

void ProfileManager::RemoveProfile(const std::string& name) {
    this->profiles.erase(
        std::remove_if(this->profiles.begin(), this->profiles.end(),
            [&](const Profile& p) {
                if (p.GetName() == name) {
                    std::filesystem::remove(GetFilePath(name));
                    return true;
                }
                return false;
            }),
        this->profiles.end()
    );
}
