/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_object.h
 */

#ifndef ASSISTANT_OBJECT_H
#define ASSISTANT_OBJECT_H

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

class AssistantObject {
private:
    int m_pithOfAssistant;
    int m_speedOfAssistant;
    int m_volumeOfAssistant;
    int m_tSpeedOfAssistant;

    int m_pos = 0;
    int m_lPos = 0;
    int m_count = 0;
    int m_sCount = 0;

    std::string m_mWord;
    std::string m_sWord;
    std::string m_input;

    std::string m_userName;
    std::string m_greet;

public:
    void Init();
    void LoadSetting();
    void DisplayBanner();
    void Greeting();
    void LocalClock();
    void Typing(std::string);
    void Speak(std::string);
    void SaveSettings(std::string, int, int, int, int);
    std::string GetUserName();

    void Check();  
    void CreateNewLine(); 
    void Repeat(); 
    void ShutdownTimer(int);
    void PlaySong(std::string); 
    void Help(); 
    void Hacking();
    void Install(std::string);
    void BlockWebsite(std::string); 
    void OpenFile(std::string); 
    void ShowSongLists(std::string); 
    void ConvertSpaceToUnderscore(std::string&);
    void SearchKeyWord(std::string, std::string extra = "");
    void UpdateSong(std::string);
    void Settings(); 
    void DisplayClock(int seconds);
};

#endif /* ASSISTANT_OBJECT_H */