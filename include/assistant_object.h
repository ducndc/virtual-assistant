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
    /**
     * Init for virtual assistant
     * 
     * @param:
     * @return
    */
    void Init(void);

    /**
     * @brief Load paramaters form file
     * 
     * @param:
     * @return
    */
    void LoadSetting(void);

    /**
     * Display banner of virtual assistant
     * 
     * @param:
     * @return
    */
    void DisplayBanner(void);

    /**
     * Get greet for virtual assistant
     * 
     * @param:
     * @return
    */
    void Greeting(void);

    /**
     * Get local clock
     * 
     * @param:
     * @return
    */
    void LocalClock(void);

    /**
     * Typing string from keyboard
     * 
     * @param:
     * @return
    */
    void Typing(std::string);

    /**
     * Convert text to speech
     * 
     * @param:
     * @return
    */
    void Speak(std::string);

    /**
     * Save setting of virtual assistant
     * 
     * @param:
     * @return
    */
    void SaveSettings(std::string, int, int, int, int);

    /**
     * Get user name for virtual assistant
     * 
     * @param:
     * @return
    */
    std::string GetUserName(void);

    /**
     * Compare the user input with defined commands 
     * 
     * @param 
     * @return
     * 
     */
    void Check(void);  

    /**
     * Create new line 
     * 
     * @param 
     * @return
     * 
     */
    void CreateNewLine(void); 

    /**
     * Ask user input again 
     * 
     * @param 
     * @return
     * 
     */
    void Repeat(void); 

    /**
     * Timer for shutdown 
     * 
     * @param 
     * @return
     * 
     */
    void ShutdownTimer(int);

    /**
     * Search the song from file(songs.txt) then play the song.
     * 
     * @param 
     * @return
     * 
     */
    void PlaySong(std::string); 

    /**
     * Show commands of virtual assistant
     * 
     * @param 
     * @return
     * 
     */
    void Help(void); 

    /**
     * Hacking
     * 
     * @param 
     * @return
     * 
     */
    void Hacking(void);

    /**
     * Create music folders
     * 
     * @param: Name of music folder
     * @return
     * 
     */
    void Install(std::string);

    /**
     * Block the websites
     * 
     * @param: Name of Website
     * @return
     * 
     */
    void BlockWebsite(std::string); 

    /**
     * Open the file directory
     * 
     * @param: Name of file
     * @return
     * 
     */
    void OpenFile(std::string); 

    /**
     * Show song list
     * 
     * @param: Name of song list
     * @return
     * 
     */
    void ShowSongLists(std::string); 

    /**
     * Convert 'space( )' to 'underscore'( _ ) and lowercase std::string
     * 
     * @param: string with space
     * @return
     * 
     */
    void ConvertSpaceToUnderscore(std::string&);

    /**
     * Search with keyword on google
     * 
     * @param: Keyword
     * @param: String extra
     * @return
     * 
     */
    void SearchKeyWord(std::string, std::string extra = "");

    /**
     * Copy song name from different files(list.txt) file into one file(songs.txt)
     * 
     * @param: Name of song
     * @return
     * 
    */
    void UpdateSong(std::string);

    /**
     * Setting for virtual assistant
     * 
     * @param:
     * @return
    */
    void Settings(void); 

    /**
     * Display clock
     * 
     * @param:
     * @return
    */
    void DisplayClock(int seconds);

    /**
     * Enter keyboard
     * 
     * @param 
     * @return
     */
    char GetHiddenInput(void);

    /**
     * Handle note
     * 
     * @param 
     * @return
     */
    void Note(void);
};

#endif /* ASSISTANT_OBJECT_H */
