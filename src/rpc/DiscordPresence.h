#pragma once
#include "discord.h"
#include <memory>
#include <thread>
#include <atomic>
#include <string>

class MyDiscordPresence {
public:
    MyDiscordPresence();
    ~MyDiscordPresence();

    // Initialize the Discord SDK
    bool Initialize(uint64_t clientId);

    // Update the Rich Presence
    void UpdatePresence(const std::string& state, const std::string& details);

    // Run callbacks (call periodically or in a separate thread)
    void RunCallbacks();

    // Stop callbacks and shutdown
    void Shutdown();

private:
    std::unique_ptr<discord::Core> core;
    std::atomic<bool> interrupted;
};
extern std::unique_ptr<MyDiscordPresence> m_discord;
extern std::thread m_discordThread;