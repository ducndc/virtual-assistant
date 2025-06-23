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

std::atomic<bool> g_running(true);

int main()
{
    initscr();           
    cbreak();
    noecho();
    curs_set(1);          
    keypad(stdscr, TRUE);
    int height;
    int width;
    getmaxyx(stdscr, height, width);
    int eyeHeight = height / 4;
    int inputHeight = height - eyeHeight;
    WINDOW* eyeWin = newwin(eyeHeight, width, 0, 0);
    WINDOW* inputWin = newwin(inputHeight, width, eyeHeight, 0);
    EyeObject eye;
    AssistantObject assistant;
    eye.Init(eyeWin);            
    assistant.Init(inputWin);    
    std::thread eye_thread([&]() {
        eye.DisplayEye();
    });
    assistant.Repeat();
    g_running = false;
    eye_thread.join();
    delwin(eyeWin);
    delwin(inputWin);
    endwin();
    
    return 0;
}