#include "pch/pch.h"
#include "DiscordPresence.h"
#include <chrono>

std::unique_ptr<MyDiscordPresence> m_discord;
std::thread m_discordThread;

MyDiscordPresence::MyDiscordPresence() : interrupted(false) {}

MyDiscordPresence::~MyDiscordPresence() {
    Shutdown();
}

bool MyDiscordPresence::Initialize(uint64_t clientId) {
    discord::Core* corePtr{};
    auto result = discord::Core::Create(clientId, DiscordCreateFlags_Default, &corePtr);
    if (result != discord::Result::Ok || !corePtr)
        return false;

    core.reset(corePtr);

    // Optional: debug log
    core->SetLogHook(discord::LogLevel::Debug, [](discord::LogLevel level, const char* msg) {
        OutputDebugStringA(msg);
        OutputDebugStringA("\n");
        });

    return true;
}

void MyDiscordPresence::UpdatePresence(const std::string& state, const std::string& details) {
    if (!core) return;

    discord::Activity activity{};
    activity.SetState(state.c_str());
    activity.SetDetails(details.c_str());
    activity.SetType(discord::ActivityType::Playing);

    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        // optional: handle success/failure
        });
}

void MyDiscordPresence::RunCallbacks() {
    while (!interrupted) {
        if (core) core->RunCallbacks();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void MyDiscordPresence::Shutdown() {
    interrupted = true;
    core.reset();
}
