# ArchSysMon
ArchSysMon is a lightweight system monitor written in modern C++ for Arch Linux. It provides a real-time overview of CPU load, memory usage, network traffic, temperature, and disk I/O via a clean terminal-based (TUI) interface.

## 📌 Features

- Per-core CPU usage
- RAM and SWAP monitoring
- Network traffic (Rx / Tx)
- CPU temperature via `lm_sensors`
- Disk I/O statistics
- Real-time updates with configurable interval
- ncurses-based TUI interface with color themes

## 🖥️ Screenshot

> _A preview screenshot will be added when the UI is ready_

## ⚙️ Build and Run

### Dependencies

Make sure the following packages are installed on your Arch Linux system:

```bash
sudo pacman -S base-devel cmake gcc ncurses lm_sensors
```

Build Instructions
```
git clone https://github.com/yourusername/archsysmon.git
cd archsysmon
mkdir build && cd build
cmake ..
make
./ArchSysMon
```

📁 Project Structure
ArchSysMon/
├── src/                # Source code
├── include/            # Header files
├── build/              # Build directory
├── CMakeLists.txt      # Build configuration
└── README.md           # Project documentation


🔒 Permissions
```
sudo sensors-detect
sudo systemctl start lm_sensors
```

🛠 Planned Features
 Optional Qt GUI frontend

 Live graphs with ImGui

 System data logging to file

 Export to JSON / CSV

 Interactive filters and views

📜 License
This project is licensed under the MIT License.

## 👨‍💻 About Me

Hi! I'm a developer passionate about low-level systems, Linux internals, and real-time graphics. My current focus is on creating efficient C++ tools for system monitoring, graphics rendering, and game development.

- 🎮 Aspiring senior game developer with experience in Unreal Engine, Vulkan, and C++
- 🐧 Daily driver: Arch Linux — I like understanding and controlling every layer of my system
- 💻 Comfortable with systemd, shell scripting, Linux APIs, and performance profiling
- 📚 I enjoy building tools that make system behavior visible, interactive, and insightful

This repository is part of my journey to master systems programming on Linux and build a solid portfolio for game and engine development roles.
