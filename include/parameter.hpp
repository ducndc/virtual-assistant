/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * paramater.hpp
 */

#ifndef PARAMATER_H
#define PARAMATER_H

#define T_CONST 1000
#define VERSION 			" Version 1.0.1 "
#define NAME_PROGRAM		" Virtual Assistant"
#define LOG_SYMBOL			"[*] "

#define NOTE_FILE_PATH		"./data/note.txt"
#define SONG_FILE_PATH		"./data/songs.txt"
#define MY_BEAT_FOLDER		"My_beat/"
#define LIST_FILE_PATH		"/list.txt"
#define TEMP_FILE_PATH		"data/temp.txt"
#define USER_SETTING_FILE	".user-settings"

#define QUIT_KEY    		'q'

#define CLEAR_SCREEN_CMD	"clear "
#define MAKE_DIR_CMD		"mkdir "
#define CREATE_FILE_CMD		"touch "
#define VIM_CMD				"gnome-terminal -- bash -c 'vim " NOTE_FILE_PATH "; exec bash' "
#define XDG_OPEN_CMD		"xdg-open "
#define SHUTDOWN_CMD		"shutdown "
#define RESTART_CMD			"reboot "
#define CHORME_CMD			"google-chrome "
#define FIREFOX_CMD			"firefox"
#define IFCONFIG_CMD		"ifconfig > /dev/null 2>&1"
#define NULL_OUTPUT			"> /dev/null 2>&1"

#define ESPEAK_CMD			"espeak -v mb-us1 "

#define AUTHOR				"Chung Duc Nguyen Dang"
#define USER_NAME			"DUCNDC"

#define GOOD_MORNING		"Good morning"
#define GOOD_AFTERNOON		"Good afternoon"
#define GOOD_EVENING		"Good evening"

#define TYPE_SYMBOL			"Type Here"
#define INPUT_SYMBOL		"Type: ---> "
#define AM_SYMBOL			"AM"
#define PM_SYMBOL			"PM"
#define HI_STR				"hi"
#define HEY_STR				"hey"
#define HELLO_STR			"hello"
#define HLO_STR 			"hlo"
#define PLAY_STR			"play"
#define PLAY_STR_1			"play "
#define SPACE_STR			" "
#define SPACE_STR_1			"  "
#define SPACE_STR_2			"   "
#define UPDATE_STR			"update"
#define UPDATING_STR		"updating"
#define EXIT_STR			"exit"
#define QUIT_STR			"quit"
#define FIND_IP_STR			"find ip"
#define FIND_MY_IP_STR		"find my ip"
#define IP_STR 				"ip"
#define SHUTDOWN_STR		"shutdown"
#define RESTART_STR			"restart"
#define WHAT_STR			"what"
#define WHO_STR				"who"
#define HOW_STR 			"how"
#define WHERE_STR			"where"
#define WHY_STR 			"why"
#define WHEN_STR			"when"
#define Q_STR 				"q"
#define SETTING_STR			"settings"
#define SETTING_STR_1		"setting"
#define SETTING_STR_2		"set"
#define SONG_STR			"song"
#define MUSIC_STR			"music"
#define INSTALL_STR			"install"
#define HELP_STR			"help"
#define MOVIE_STR			"movie"
#define PDF_STR				"pdf"
#define SEARCH_STR			"search"
#define CMD_STR				"cmd"
#define LIST_STR			"list"
#define BLOCK_STR			"block"
#define NOTE_STR			"note"
#define HACK_STR			"hack"
#define ALL_SONG_STR		"all songs"
#define SONGS_STR			"songs"
#define YOUTUBE_STR			"youtube"
#define WATCH_STR			"watch"
#define OPEN_STR			"open"
#define CHORME_STR			"chrome"
#define GOOGLE_CHORME_STR	"google chrome"
#define MOZILLA_STR			"mozilla"
#define FIREFOX_STR			"firefox"
#define ASK_AI				"ask"

#define CURL_OLLAMA			"curl -s http://localhost:11434/api/generate "
#define CONTENT_OLLAMA		"-H \"Content-Type: application/json\" "
#define MODE_AI				"gemma:2b"
#define LOAD_MODEL			"-d '{\"model\": \"" MODE_AI "\", \"prompt\": \"" 
#define END_LOAD_MODEL		"\"}'"

#endif /* PARAMATER_H */
