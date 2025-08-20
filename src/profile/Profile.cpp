#include "pch/pch.h"
#include "Profile.h"
#include <fstream>
#include <sstream>

Profile::Profile(const std::string& name) : name(name) {}

bool Profile::LoadFromFile(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) return false;

    std::getline(in, this->name);
    std::getline(in, this->state);
    std::getline(in, this->details);

    return true;
}

bool Profile::SaveToFile(const std::string& filepath) const {
    std::ofstream out(filepath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << this->name << "\n";
    out << this->state << "\n";
    out << this->details << "\n";

    return true;
}
