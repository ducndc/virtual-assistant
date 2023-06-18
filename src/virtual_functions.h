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

/**
 * Compare the user input with defined commands 
 * 
 * @param 
 * @return
 * 
 */
void Check();   

/**
 * Create new line 
 * 
 * @param 
 * @return
 * 
 */
void CreateNewLine();      

/**
 * Ask user input again 
 * 
 * @param 
 * @return
 * 
 */
void Repeat();     

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
void Help(); 

/**
 * Hacking
 * 
 * @param 
 * @return
 * 
 */
void Hacking();

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
void Settings(); 

#endif /* VIRTUAL_FUNCTION_H */