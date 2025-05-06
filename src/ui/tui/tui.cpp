#include "../monitor/temperature.hpp"

void TUI::run() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    timeout(0);

    CpuMonitor cpu;
    MemoryMonitor memory;
    NetworkMonitor network;
    TemperatureMonitor tempMonitor;

    while (true) {
        clear();
        auto usage = cpu.getUsage();
        auto mem = memory.getUsage();
        auto netStats = network.getStats();

        auto temps = tempMonitor.getTemperatures();
        mvprintw(line++, 0, "Температура процессора:");
        for (const auto& t : temps) {
            mvprintw(line++, 0, "%s: %.1f°C", t.label.c_str(), t.temperature);
        }

        for (size_t i = 0; i < usage.size(); ++i) {
            mvprintw(i, 0, "CPU %zu: %5.1f%%", i, usage[i].usagePercent);
        }

        mvprintw(usage.size() + 1, 0, "RAM: %lu MB / %lu MB", mem.usedRAM, mem.totalRAM);

        mvprintw(usage.size() + 2, 0, "SWAP: %lu MB / %lu MB", mem.usedSwap, mem.totalSwap);

        int line = usage.size() + 4;
        mvprintw(line++, 0, "Сетевой трафик (за последнюю секунду):");
        for (const auto& [iface, stats] : netStats) {
            mvprintw(line++, 0, "%s: Rx %lu bytes, Tx %lu bytes", iface.c_str(), stats.rxBytes, stats.txBytes);
        }

        mvprintw(line + 1, 0, "Нажмите 'q' для выхода");

        refresh();

        if (getch() == 'q') break;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    endwin();
}
