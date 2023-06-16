/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_utils.h
 */

#ifndef ASSISTANT_UTILS_H
#define ASSISTANT_UTILS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <ctype.h>
#include <ctime>
#include <thread>

namespace assistant_utils 
{
    void Init();
    void LoadSetting();

    void DisplayBanner();
    void Greeting();
    void LocalClock();

    void Typing(std::string);
    void Speak(std::string);

    void SaveSettings(std::string, int, int, int, int);

    std::string GetUserName();
}

#endif /* ASSISTANT_UTILS_H */