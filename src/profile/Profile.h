#pragma once
#include <string>

class Profile {
public:
    Profile() = default;
    Profile(const std::string& name);

    const std::string& GetName() const { return name; }
    void SetName(const std::string& n) { name = n; }

    const std::string& GetState() const { return state; }
    void SetState(const std::string& s) { state = s; }

    const std::string& GetDetails() const { return details; }
    void SetDetails(const std::string& d) { details = d; }

    // Serialize/deserialize
    bool LoadFromFile(const std::string& filepath);
    bool SaveToFile(const std::string& filepath) const;

private:
    std::string name;
    std::string state;
    std::string details;
};
