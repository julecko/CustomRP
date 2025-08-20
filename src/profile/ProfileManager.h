#pragma once
#include "Profile.h"
#include <vector>
#include <string>
#include <memory>

class ProfileManager {
public:
    ProfileManager(const std::string& directory = "profiles");

    void LoadProfiles();
    void SaveProfiles() const;

    Profile* GetProfile(const std::string& name);
    std::vector<Profile>& GetAllProfiles() { return profiles; }

    void AddProfile(const Profile& profile);
    void RemoveProfile(const std::string& name);

    const std::string& GetDirectory() const { return directory; }

private:
    void EnsureDirectoryExists() const;
    std::string GetFilePath(const std::string& profileName) const;

    std::string directory;
    std::vector<Profile> profiles;
};
