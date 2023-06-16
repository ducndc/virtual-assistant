/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_utils.h
 */

#ifndef VIRTUAL_FUNCTION_H
#define VIRTUAL_FUNCTION_H

#include "assistant_utils.h"

using namespace assistant_utils;

#define T_CONST 1000

void Check();   //compare the user input with defined commands
void CreateNewLine();      // create new CreateNewLine
void Repeat();     //ask user input again.
void ShutdownTimer(int);
void PlaySong(std::string);  //search the song from file(songs.txt) then play the song.
void Help();          //show commands
void Hacking();
void Install(std::string); // create music folders
void BlockWebsite(std::string);  //block the websites
void OpenFile(std::string);   // open the file directory
void ShowSongLists(std::string);   //show song list
void ConvertSpaceToUnderscore(std::string&);   //convert 'space( )' to 'underscore'( _ ) and lowercase std::string
void SearchKeyWord(std::string, std::string extra = "");
void UpdateSong(std::string);   //copy song name from different files(list.txt) file into one file(songs.txt)
void Settings(); // user Settings

#endif /* VIRTUAL_FUNCTION_H */