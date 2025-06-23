/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * eye_object.cc
 */

#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>
#include <cstring>
#include <sys/sysinfo.h>
#include <fstream>
#include <sys/statvfs.h>
#include <unistd.h>

#include "eye_object.hpp"
#include "parameter.hpp"

extern std::atomic<bool> g_running;

void 
EyeObject::Init(WINDOW* win)
{
    m_win = win;
    int height, width;
    getmaxyx(m_win, height, width);
    m_width = width - 2;   
    m_height = height - 2;

    if (has_colors()) 
    {
        start_color();
        use_default_colors();
        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_YELLOW, -1);
        init_pair(3, COLOR_RED, -1);
    }
}

void 
EyeObject::DisplayEye(void)
{
    while (g_running) 
    {
        werase(m_win);
        box(m_win, 0, 0);
        struct sysinfo info;
        sysinfo(&info);

        static long prevIdle = 0, prevTotal = 0;
        long idle, total;
        {
            std::ifstream file("/proc/stat");
            std::string label;
            long user, nice, system, idleTime, iowait, irq, softirq;
            file >> label >> user >> nice >> system >> idleTime >> iowait >> irq >> softirq;
            idle = idleTime + iowait;
            total = user + nice + system + idle + irq + softirq;
        }

        float cpu_percent = 0;
        long deltaTotal = total - prevTotal;
        long deltaIdle = idle - prevIdle;

        if (deltaTotal > 0)
            cpu_percent = 100.0f * (deltaTotal - deltaIdle) / deltaTotal;

        prevIdle = idle;
        prevTotal = total;
        float ram_used = info.totalram - info.freeram;
        float ram_percent = (ram_used / info.totalram) * 100.0f;
        struct statvfs disk;
        float disk_percent = 0;

        if (statvfs("/", &disk) == 0) 
        {
            unsigned long total = disk.f_blocks * disk.f_frsize;
            unsigned long free = disk.f_bfree * disk.f_frsize;
            disk_percent = 100.0f * (total - free) / total;
        }

        float battery_percent = -1.0f;
        std::ifstream bat("/sys/class/power_supply/BAT0/capacity");

        if (bat.is_open()) 
        {
            int val;
            bat >> val;
            battery_percent = static_cast<float>(val);
        }

        int uptime_minutes = info.uptime / 60;
        int uptime_hours = uptime_minutes / 60;
        uptime_minutes %= 60;
        float loadavg1 = info.loads[0] / 65536.0;

        auto draw_bar = [&](int row, const std::string& label, float percent, int color_threshold) 
        {
            int barWidth = m_width - 20;
            int filled = (int)((percent / 100.0f) * barWidth);
            mvwprintw(m_win, row, 2, "%-8s", (label + ":").c_str());

            if (has_colors()) 
            {
                if (percent > color_threshold) 
                    wattron(m_win, COLOR_PAIR(3));
                else if (percent > 70) 
                    wattron(m_win, COLOR_PAIR(2));
                else 
                    wattron(m_win, COLOR_PAIR(1));
            }

            for (int i = 0; i < barWidth; ++i) 
            {
                mvwaddch(m_win, row, 12 + i, (i < filled ? ACS_CKBOARD : ' '));
            }

            if (has_colors()) 
                wattroff(m_win, COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));

            wprintw(m_win, " %3.0f%%", percent);
        };

        draw_bar(2, "CPU", cpu_percent, 85);
        draw_bar(3, "RAM", ram_percent, 80);
        draw_bar(4, "DISK", disk_percent, 90);

        if (battery_percent >= 0)
            draw_bar(5, "BATTERY", battery_percent, 30);

        wattron(m_win, A_BOLD);
        mvwprintw(m_win, m_height - 2, 2,
                  "Uptime: %dh %02dm   Load avg: %.2f   PID: %d",
                  uptime_hours, uptime_minutes, loadavg1, getpid());
        wattroff(m_win, A_BOLD);
        wrefresh(m_win);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}