/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * main.h
 */

#include <ncurses.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>

#include "assistant_object.hpp"
#include "eye_object.hpp"

std::atomic<bool> running(true);

int main()
{
    initscr();            // khởi tạo ncurses
    cbreak();
    noecho();
    curs_set(1);          // hiển thị con trỏ gõ
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    int eye_height = height / 2;
    int input_height = height - eye_height;

    WINDOW* eye_win = newwin(eye_height, width, 0, 0);
    WINDOW* input_win = newwin(input_height, width, eye_height, 0);

    EyeObject eye;
    AssistantObject assistant;

    eye.Init(eye_win);             // truyền window vào EyeObject
    assistant.Init(input_win);     // truyền window vào AssistantObject

    // chạy mắt xoay song song
    std::thread eye_thread([&]() {
        eye.DisplayEye();
    });

    // chạy giao diện nhập
    assistant.Repeat();

    // khi Repeat kết thúc, dừng mắt xoay
    running = false;
    eye_thread.join();

    delwin(eye_win);
    delwin(input_win);
    endwin();

    return 0;
}