#pragma once
#include "Profile.h"
#include <string>
#include <unordered_set>

struct ProfileHash {
    std::size_t operator()(const Profile& p) const {
        return std::hash<std::string>()(p.GetName());
    }
};

struct ProfileEqual {
    bool operator()(const Profile& lhs, const Profile& rhs) const {
        return lhs.GetName() == rhs.GetName();
    }
};

class ProfileManager {
public:
    ProfileManager(const std::string& dir = "profiles");

    void LoadProfiles();
    void SaveProfiles() const;

    Profile* GetProfile(const std::string& name);
    const Profile* GetProfile(const std::string& name) const;
    const std::unordered_set<Profile, ProfileHash, ProfileEqual>& GetAllProfiles() const { return profiles; }

    void AddProfile(Profile profile);
    void RemoveProfile(const std::string& name);

    const std::string& GetDirectory() const { return directory; }

    std::string GetUniqueName(const std::string& baseName) const;

    void SetCurrentProfile(const std::string& name) { currentProfile = GetProfile(name); }
    Profile* GetCurrentProfile() const { return currentProfile; }

private:
    Profile* currentProfile = nullptr;

    std::string GetFilePath(const std::string& profileName) const;

    std::string directory;
    std::unordered_set<Profile, ProfileHash, ProfileEqual> profiles;
};
