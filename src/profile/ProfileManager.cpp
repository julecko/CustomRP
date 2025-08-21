#include "pch/pch.h"
#include "ProfileManager.h"
#include <filesystem>

namespace fs = std::filesystem;

ProfileManager::ProfileManager(const std::string& dir) : directory(dir) {
    if (!fs::exists(directory)) {
        fs::create_directory(directory);
    }
    LoadProfiles();
}

std::string ProfileManager::GetFilePath(const std::string& profileName) const {
    return directory + "/" + profileName + ".txt";
}

void ProfileManager::LoadProfiles() {
    profiles.clear();
    if (!fs::exists(directory)) return;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            Profile p;
            if (p.LoadFromFile(entry.path().string())) {
                profiles.insert(p);
            }
        }
    }
}

void ProfileManager::SaveProfiles() const {
    for (const auto& p : profiles) {
        p.SaveToFile(GetFilePath(p.GetName()));
    }
}

Profile* ProfileManager::GetProfile(const std::string& name) {
    auto it = std::find_if(profiles.begin(), profiles.end(),
        [&](const Profile& p) { return p.GetName() == name; });

    return (it != profiles.end()) ? const_cast<Profile*>(&(*it)) : nullptr;
}

const Profile* ProfileManager::GetProfile(const std::string& name) const {
    auto it = std::find_if(profiles.begin(), profiles.end(),
        [&](const Profile& p) { return p.GetName() == name; });
    return (it != profiles.end()) ? &(*it) : nullptr;
}

void ProfileManager::AddProfile(Profile profile) {
    profile.SetName(GetUniqueName(profile.GetName()));

    profiles.insert(profile);
    profile.SaveToFile(GetFilePath(profile.GetName()));
}

void ProfileManager::RemoveProfile(const std::string& name) {
    auto it = std::find_if(profiles.begin(), profiles.end(),
        [&](const Profile& p) { return p.GetName() == name; });

    if (it != profiles.end()) {
        fs::remove(GetFilePath(name));
        profiles.erase(it);
    }
}

std::string ProfileManager::GetUniqueName(const std::string& baseName) const {
    std::string name = baseName;
    int counter = 1;

    while (GetProfile(name)) { // while name exists
        name = baseName + std::to_string(counter);
        counter++;
    }

    return name;
}
