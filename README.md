# CustomRP

**CustomRP** is a Windows application that provides **custom Discord Rich Presence**. It runs as a tray icon application, allowing you to manage profiles and update your Discord presence directly from the system tray.

## Features

- Tray icon-based interface for quick access.
- Multiple profiles support.
- Connect, Disconnect, and Refresh Discord Rich Presence per profile.
- Automatically updates Discord presence based on selected profile.
- Lightweight and runs silently in the background.

## Installation

1. Create an application in the [Discord Developer Portal](https://discord.com/developers/applications):
   - Set the **name** of the application (this will be shown on Discord).
   - Add an **icon** in the application settings (this will appear in Discord Rich Presence).
   - Copy the **Discord Client ID** to use in CustomRP.

2. Download the latest **release** from the releases page.

3. Run `CustomRP.msi` to install CustomRP on your PC.

4. Start `CustomRP.exe` from the Windows Start Menu. A tray icon will appear in the bottom right corner.

5. Right-click the tray icon and open **Settings** to set your Discord Client ID and configure profiles:
   - Each profile can have its own **Details** and **State** for Discord Rich Presence.

## Usage

1. Right-click the tray icon to open the menu.
2. Select a profile from the **Profiles** submenu.
3. Use **Connect**, **Disconnect**, or **Refresh** to update Discord Rich Presence.
4. Open **Settings** from the tray menu to manage profiles and configure Discord Client ID.

## Possible Error Situations

- **Invalid Discord Client ID**: The application will not connect. Make sure the ID is correct.
- **Discord not running**: Start Discord before running CustomRP.
- In either case, restart CustomRP after fixing the problem.
- For any other issues, submit an [issue on GitHub](https://github.com/julecko/CustomRP) or contact the author at **julecko@dilino.sk**.

## Requirements

- Windows 10 or later.
- Discord installed.

## Development

- Language: **C++**
- Framework: **MFC**
- Dependencies:
  - Discord SDK
  - Standard C++ libraries
  - Windows Shell API

---

## License

**All rights reserved.** You may edit or modify this software for personal use. Redistribution or commercial use is not allowed without explicit permission from the author.
