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
    AssistantObject assistantFriend;
    EyeObject eye;
    
    eye.Init();
    std::thread eyeThread([&]() {
        eye.DisplayEye();  // chạy song song
    });

    assistantFriend.Init();
    assistantFriend.Repeat();

    // khi Repeat() kết thúc, dừng chương trình
    running = false;
    eyeThread.join();

    return 0;
}