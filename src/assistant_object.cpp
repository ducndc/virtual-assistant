/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_object.cc
 */

#include <termios.h>
#include <algorithm>
#include <filesystem>
#include <atomic> 
#include <ncurses.h>
#include <vector>
#include <string>

#include "assistant_object.hpp"
#include "parameter.hpp"

extern std::atomic<bool> g_running;

void 
AssistantObject::Init(
	WINDOW* win)
{
	m_win = win;
	m_terminate = false;
    mvwprintw(m_win, 0, 2, VERSION);
    wrefresh(m_win);
	LoadSetting();
	LocalClock();
	Greeting();
}

void 
AssistantObject::DisplayBanner(void)
{
	mvwprintw(m_win, 6, 1, LOG_SYMBOL VERSION);
}

void 
AssistantObject::LoadSetting(void)
{
	std::ifstream file;
	file.open(USER_SETTING_FILE, std::ios::in);

	if (file.good())
	{
		std::string name;

		while (!file.eof())
		{
			file >> m_userName >> m_speedOfAssistant 
				 >> m_volumeOfAssistant >> m_pithOfAssistant 
				 >> m_tSpeedOfAssistant;
		}
	}
	else
	{
		m_userName = USER_NAME;
		m_speedOfAssistant = 130;
		m_pithOfAssistant = 50;
		m_volumeOfAssistant = 120;
		m_tSpeedOfAssistant = 50;
	}

	file.close();
}

void 
AssistantObject::SaveSettings(
	std::string un = USER_NAME, 
	int ss = 160, 
	int sa = 100, 
	int sp = 40, 
	int ts = 40)
{
	std::ofstream file;
	file.open(USER_SETTING_FILE, std::ios::out);
	file << un << " " << ss << " "  << sa << " "  << sp << " "  << ts;
	file.close();
}

void 
AssistantObject::Greeting(void)
{
	usleep(T_CONST * 300);
	Speak(m_greet);
	usleep(T_CONST * 400);
}

void 
AssistantObject::Speak(
	std::string s)
{
    std::string cmd = ESPEAK_CMD;
    cmd += " -a";
    cmd += std::to_string(m_volumeOfAssistant);
    cmd += " -p";
    cmd += std::to_string(m_pithOfAssistant);
    cmd += " -s";
    cmd += std::to_string(m_speedOfAssistant);
    cmd += " \"";
    cmd += s;
    cmd += "\"";
    system(cmd.c_str());
}

void 
AssistantObject::Typing(
	const std::string& message, 
	bool enableVoice)
{
	std::thread th;

	if (enableVoice)
		th = std::thread(&AssistantObject::Speak, this, message);

	werase(m_win);           
	int max_y, max_x;
	getmaxyx(m_win, max_y, max_x);
	int row = 5;
	int col = 2;
	scrollok(m_win, TRUE);

	for (char ch : message) 
	{
		if (ch == '\n') 
		{
			row++;
			col = 2;
		} 
		else 
		{
			if (col >= max_x - 2) 
			{
				row++;
				col = 2;
			}

			if (row >= max_y - 1) 
			{
				wmove(m_win, max_y - 1, 0);
				wscrl(m_win, 1);
				row = max_y - 2; 
			}

			mvwaddch(m_win, row, col++, ch);
		}

		wrefresh(m_win);
		napms(30);
	}

	wrefresh(m_win);

	if (enableVoice)
		th.join();
}



std::string 
AssistantObject::GetUserName(void)
{
	return m_userName;
}

void 
AssistantObject::LocalClock(void)
{
	std::string day[] = 
		{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	std::string day_no[] = 
		{"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"};
	std::string month[] = 
		{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	time_t now = time(0);
	tm *l_time = localtime(&now);

	if (l_time->tm_hour < 12)
    {
		m_greet = GOOD_MORNING;
    }
	else if (l_time->tm_hour >= 12)
    {
		if (l_time->tm_hour > 16)
        {
			m_greet = GOOD_EVENING;
        }
		else
        {
			m_greet = GOOD_AFTERNOON;
        }
    }

    mvwprintw(m_win, 1, 15, "%s %d %s %d", month[l_time->tm_mon].c_str(), 
    	l_time->tm_mday, day_no[l_time->tm_mday % 10].c_str(), l_time->tm_year + 1900);

	if ("Monday" == day[l_time->tm_wday])
    {
		mvwprintw(m_win, 1, 2, LOG_SYMBOL "(Sunday)");
    }
	else
    {
    	mvwprintw(m_win, 1, 2, LOG_SYMBOL "%s", day[l_time->tm_wday - 1].c_str());
    }

	m_greet += " ";
	m_greet += m_userName;
    
    mvwprintw(m_win, 2, 2, LOG_SYMBOL "%s", m_greet.c_str());
    mvwprintw(m_win, 3, 2, LOG_SYMBOL "Time: %dh%dm %s", 
    	(l_time->tm_hour <= 12 ? l_time->tm_hour : l_time->tm_hour - 12), 
    	l_time->tm_min, (l_time->tm_hour < 12 ? AM_SYMBOL : PM_SYMBOL));
}

void 
AssistantObject::Repeat(void)
{
    char input[128] = {0};
    int max_y, max_x;
    getmaxyx(m_win, max_y, max_x);

    int input_row = max_y - 2;

    while (g_running) 
    {
    	werase(m_win);
        
        mvwprintw(m_win, 0, 2, NAME_PROGRAM VERSION);
        LocalClock();
		char input[128] = {0};
		int pos = 0;
		mvwhline(m_win, input_row, 1, ' ', max_x - 2);
		mvwprintw(m_win, input_row, 2, LOG_SYMBOL INPUT_SYMBOL);
		wmove(m_win, input_row, 4);
		int ch;

		if (m_terminate)
			break;

		while (true) 
		{
		    ch = wgetch(m_win);

		    if (ch == '\n') 
		    {
		        input[pos] = '\0';
		        break;
		    } 
		    else if ((ch == KEY_BACKSPACE || ch == 127 || ch == 8) && pos > 0) 
		    {
		        pos--;
		        input[pos] = '\0';
		        mvwaddch(m_win, input_row, 18 + pos, ' ');
		        wmove(m_win, input_row, 18 + pos);
		    } 
		    else if (isprint(ch) && pos < sizeof(input) - 1) 
		    {
		        input[pos++] = ch;
		        mvwaddch(m_win, input_row, 18 + pos - 1, ch);
		    }

		    wrefresh(m_win);
		}

        m_input = input;
        std::transform(m_input.begin(), m_input.end(), m_input.begin(), ::tolower);
        m_pos = m_input.find(" ");
        m_mWord = m_input.substr(0, m_pos);
        m_lPos = m_input.find('\0');
        m_sWord = m_input.substr(m_pos + 1, m_lPos);
        Check();
        wrefresh(m_win);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    if (m_terminate)
    	return;
}

void 
AssistantObject::Check(void)
{
	if ((HI_STR == m_mWord) || (HEY_STR == m_mWord) || 
		(HELLO_STR == m_mWord) || (HLO_STR == m_mWord))
	{
		Typing("Hi " + m_userName + ", how can I help you..", true);
	}
	else if (PLAY_STR == m_mWord)
	{
		if ((PLAY_STR == m_input) || (PLAY_STR_1 == m_input) || 
			(SPACE_STR == m_sWord) || (SPACE_STR_1 == m_sWord) || (SPACE_STR_2 == m_sWord))
		{
			Speak("Sorry " + m_userName + " ,you does not enter song name");
		}
		else
		{
			PlaySong(m_sWord);
		}
	}
	else if ((UPDATE_STR == m_mWord) || (UPDATING_STR == m_mWord))
	{
		Typing("Updating the song list...", true);
		usleep(T_CONST * 100);
		Typing("Please wait", true);
		UpdateSong("punjabi");
		UpdateSong("english");
		UpdateSong("hindi");
		UpdateSong("others");
		remove("data/songs.txt");
		rename(TEMP_FILE_PATH, "data/songs.txt");
		
		Typing("All songs are updated in the file", true);
	}
	else if ((EXIT_STR == m_input) || (Q_STR == m_input) || (QUIT_STR == m_input))
	{
		Speak("Good bye," + m_userName);
		usleep(T_CONST * 600);
		Typing("Created By : " AUTHOR, true);
		usleep(T_CONST * 1000);
		m_terminate = true;
	}
	else if ((FIND_IP_STR == m_input) || (FIND_MY_IP_STR == m_input) || (IP_STR == m_mWord))
	{
		Typing("Finding your IP address", true);
		system(IFCONFIG_CMD);
	}
	else if ((SHUTDOWN_STR == m_mWord) || (RESTART_STR == m_mWord))
	{
		Typing("Your Pc will ", true);
		Typing(m_mWord, true);
		ShutdownTimer(5);
		Speak("Now , I am going to sleep");
		if (SHUTDOWN_STR == m_mWord)
			system(SHUTDOWN_CMD);
		else
			system(RESTART_CMD);
		usleep(T_CONST * 10);
		exit(1);
	}
	else if ((WHAT_STR == m_mWord) || (WHO_STR == m_mWord) || 
		(HOW_STR == m_mWord) || (WHEN_STR == m_mWord) || 
		(WHERE_STR == m_mWord) || (WHY_STR == m_mWord))
	{
		if (m_input == "what is your name")
		{
			Typing("My name is VA.", true);
		}
		else if (("who are you?" == m_input) || 
			("who created you?" == m_input) || 
			("who made you?" == m_input))
		{
			Typing("I am VA, a virtual assistant, I was created on 16 June ,2023", true);
		}
		else
        {
			SearchKeyWord(m_input);
        }
    }
	else if ((SETTING_STR == m_input) || (SETTING_STR_1 == m_input) || (SETTING_STR_2 == m_input))
	{	
        Settings();
    }
	else if ((SONG_STR == m_mWord) || (MUSIC_STR == m_mWord))
	{	
        SearchKeyWord(m_sWord, SONG_STR);
    }
	else if (INSTALL_STR == m_input)
	{
		system(MAKE_DIR_CMD "My_beat");
		Install("hindi");
		Install("english");
		Install("punjabi");
		Install("others");
		usleep(T_CONST * 200);
		usleep(T_CONST * 200);
		Typing("\nAll files are installed", true);
		usleep(T_CONST * 300);
	}
	else if (HELP_STR == m_input)
	{	
        Help();
    }
	else if (MOVIE_STR == m_mWord)
	{	
        SearchKeyWord(m_sWord, MOVIE_STR);
    }
    else if (PDF_STR == m_mWord)
	{	
        SearchKeyWord(m_sWord, PDF_STR);
    }
    else if (SEARCH_STR == m_mWord)
	{	
        SearchKeyWord(m_sWord);
    }
    else if (CMD_STR == m_mWord)
	{	
        system(m_sWord.c_str());
    }
    else if (HACK_STR == m_mWord)
	{
		Hacking();
	}
	else if (LIST_STR == m_mWord)
	{
		if ((ALL_SONG_STR == m_sWord) || (SONGS_STR == m_sWord))
			ShowSongLists(SONG_FILE_PATH);
	}
	else if (BLOCK_STR == m_mWord)
	{
		BlockWebsite(m_sWord);
	}
	else if (NOTE_STR == m_mWord)
	{
		Note();
	}
	else if ((YOUTUBE_STR == m_mWord) || (WATCH_STR == m_mWord))
	{
		SearchKeyWord(m_sWord, YOUTUBE_STR);
	}
	else if (OPEN_STR == m_mWord)
	{
		if ((CHORME_STR == m_sWord) || (GOOGLE_CHORME_STR == m_sWord))
		{
			system(CHORME_CMD);
		}
		else if ((MOZILLA_STR == m_sWord) || (FIREFOX_STR == m_sWord))
		{
			system(FIREFOX_CMD);
		}
		else
			OpenFile(m_sWord);
	}
	else if (ASK_AI == m_mWord)
	{
		Typing(AskOllama(m_input), false);
		WaitOut();
	}
	else
	{
		Speak("Sorry " + m_userName + ", unknown command...");
		m_count++;

		if (m_count >= 3)
		{	usleep(T_CONST * 600);
			Speak("I think ");
			usleep(T_CONST * 500);
			Speak("you are a new user");
			usleep(T_CONST * 600);
			Speak("You need some help...");
			Help();
		}
	}

	usleep(T_CONST * 700);
}

void 
AssistantObject::Settings(void)
{
	std::string un;
	int ss, sa, sp, ts;

    m_count = 0;
    int row = 4;
    std::vector<std::string> commands = {
    	"Enter data in the following given format:",
        "1.user name(single word only)",
        "2.speak speed(in WPM)",
        "3.speak volume(0-200)",
        "4.speak pitch(0-99)",
        "5.typing speed(in ms)",
        "Example 1:",
        "Duc 160 100 40 40"
    };

    werase(m_win);           
            

    for (const auto& cmd : commands) 
    {
        mvwprintw(m_win, row++, 10, "%s", cmd.c_str());
    }

    wrefresh(m_win);

	std::cin >> un >> ss >> sa >> sp >> ts;

	if ((sa <= 200 && sa > 0) && (sp <= 99 && sp > 0 ))
	{
		SaveSettings(un, ss, sa, sp, ts);
		Typing("Restart me to see changes", true);
	}
	else
	{
		Speak("Something went wrong");
	}

	std::cin.ignore('\n');
}

void 
AssistantObject::PlaySong(
	std::string item)
{
	std::ifstream file;
	std::string song_name;
	song_name = item;
	ConvertSpaceToUnderscore(item);
	char song[30], singer[30];
	char path[90] = XDG_OPEN_CMD MY_BEAT_FOLDER;
	file.open(SONG_FILE_PATH, std::ios::app);

	while (file >> song >> singer)
	{
		if (song == item)
		{
			Typing("Playing the song ", true);
			usleep(T_CONST * 150);
			Typing(song_name, true);
			strcat(path, singer);
			strcat(path, "/");
			strcat(path, song);
			strcat(path, ".mp3");
			system(path);
			break;
		}
	}

	usleep(T_CONST * 150);
	

	if (song != item)
	{
		Typing(song_name, true);
		Typing(" not found.", true);

		if (m_sCount % 3 == 0)
		{
			usleep(T_CONST * 200);
			
			Speak("But you can download the song by using the command");
			usleep(T_CONST * 1300);
			
			Typing("song ", true);
			Typing(song_name, true);
		}

		m_sCount++;
	}

	file.close();
}

void 
AssistantObject::ConvertSpaceToUnderscore(
	std::string &c)
{

	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] == ' ')
			c[i] = '_';
		c[i] = tolower(c[i]);
	}
}

void 
AssistantObject::UpdateSong(
	std::string name)
{
	std::fstream a, b;
	char word[20], old[20];
	
	a.open(MY_BEAT_FOLDER + name + LIST_FILE_PATH);
	b.open(TEMP_FILE_PATH, std::ios::app | std::ios::ate);

	while (a >> word)
	{
		b << word << " " << name << "\n";
	}

	b.close();
	a.close();
}

void 
AssistantObject::DisplayClock(
	int seconds)
{
	int h, m;
	h = m = 0;
	
	//std::cout << "\n\n";
	//std::cout << std::setfill(' ') << std::setw(75) << "	        TIMER	      	\n";
	//std::cout << std::setfill(' ') << std::setw(75) << " --------------------------\n";
	//std::cout << std::setfill(' ') << std::setw(29);
	//std::cout << "| " << std::setfill('0') << std::setw(2) << h << " hrs | ";
	//std::cout << std::setfill('0') << std::setw(2) << m << " min | ";
	//std::cout << std::setfill('0') << std::setw(2) << seconds << " sec |" << std::endl;
	//std::cout << std::setfill(' ') << std::setw(75) << " --------------------------\n";
}

void 
AssistantObject::ShutdownTimer(
	int t)
{
	while (t)
	{
		DisplayClock(t);
		usleep(T_CONST * 900);
		t--;
	}
}

void 
AssistantObject::SearchKeyWord(
	std::string query, 
	std::string extra)
{
	for (int i = 0; query[i] != '\0'; i++)
	{
		if (query[i] == ' ')
			query[i] = '+';
	}

	usleep(T_CONST * 200);
	Typing("Cheking internet connection...", true);

	if (m_sCount % 5 == 0)
	{
		
		usleep(T_CONST * 90);
		Typing("Colleting information...", true);
		usleep(T_CONST * 50);
		system(IFCONFIG_CMD);
		Typing("All protocols are secured...", true);
	}

	usleep(T_CONST * 250);
	Speak("Connecting to your browser.");
	std::string url;

	if ("youtube" == extra)
	{
		url = "xdg-open https://www.youtube.com/results?search_query=";
		url += query;
		url += NULL_OUTPUT;
		system(std::string(url).c_str());
	}
	else if ("song" == extra)
	{
		url = XDG_OPEN_CMD "https://m.soundcloud.com/search?q=";
		url += query;
		url += NULL_OUTPUT;
		system(std::string(url).c_str());

		url = XDG_OPEN_CMD "https://www.google.com/search?q=";
		url += query;
		url += NULL_OUTPUT;
		system(std::string(url).c_str());
		usleep(T_CONST * 50);
	}
	else
	{
		url = XDG_OPEN_CMD "https://www.google.com/search?q=";
		url += query;
		url += NULL_OUTPUT;
		system(std::string(url).c_str());
	}

	m_sCount++;
}

void 
AssistantObject::Install(
	std::string fold)
{
	std::fstream file;
	std::string foldname;
	std::string filename;
	foldname = MAKE_DIR_CMD MY_BEAT_FOLDER;
	foldname += fold;
	system(std::string(foldname).c_str());
	filename = MY_BEAT_FOLDER;
	filename += fold;
	filename += LIST_FILE_PATH;
	file.open(filename, std::ios::app);
	file.close();
}

void 
AssistantObject::ShowSongLists(
	std::string link)
{
	std::fstream file;
	int count = 0;
	char word[50], old[50];
	file.open(link);

	while (file >> word >> old)
	{
		count++;
	}

	std::string p, s = "Only ";
	p = count;
	s += p;
	s += "songs are available";

	if (count != 0)
	{
		Speak(s);
	}

	file.close();
}

void 
AssistantObject::Hacking(void)
{
	
	Speak("You are Welcome in the Hacking Lab");
	Typing("Still in development...", true);
}

void 
AssistantObject::BlockWebsite(
	std::string website)
{
	std::fstream file;
	file.open("echo", std::ios::app);
	file << "\n127.0.0.2 www." << website;
	Typing("Blocking the website..", true);
	file.close();
}

void 
AssistantObject::Note(void)
{
	std::string cmd = VIM_CMD; 

	if (std::filesystem::exists(NOTE_FILE_PATH)) 
	{
		system(std::string(cmd).c_str());
	}
	else
	{
		std::string createFileCMD = CREATE_FILE_CMD NOTE_FILE_PATH;
		system(std::string(createFileCMD).c_str());
		system(std::string(cmd).c_str());
	}
}

void 
AssistantObject::OpenFile(
	std::string location)
{
	std::string path = XDG_OPEN_CMD, item = location;
	ConvertSpaceToUnderscore(item);
	path += item;
	Typing("Open....", true);
	Typing(location, true);
	system(std::string(path).c_str());
}

void 
AssistantObject::Help(void)
{
    m_count = 0;
    int row = 4;
    std::vector<std::string> commands = {
        "1. search (any question)",
        "2. open (google,mozilla)",
        "3. block (website name)",
        "4. song (song name)",
        "5. update",
        "6. watch (videoname)",
        "7. pdf (pdfname)",
        "8. movie (moviename)",
        "9. what/how/where/who/why (question)",
        "10. cmd (cmd commands)",
        "11. find my ip",
        "12. play (song name)",
        "13. list songs",
        "14. exit/quit/q",
        "15. shutdown/restart",
        "16. install",
        "17. note",
        "18. deepseek question"
    };

    werase(m_win);                   

    for (const auto& cmd : commands) 
    {
        mvwprintw(m_win, row++, 10, "%s", cmd.c_str());
    }

    wrefresh(m_win);
    WaitOut();
}

char 
AssistantObject::GetHiddenInput(void) 
{
	termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void 
AssistantObject::WaitOut(void)
{
	char wait;

	do 
	{
		wait = GetHiddenInput();
	    usleep(T_CONST * 100);
	} while (wait != QUIT_KEY);
}

std::string 
AssistantObject::AskDeepSeek(
	const std::string& user_input) 
{
    std::ofstream req("request.json");
    req << R"({
        "model": "deepseek/deepseek-chat",
        "messages": [
            { "role": "system", "content": "You are a helpful assistant." },
            { "role": "user", "content": ")" << user_input << R"(" }
        ]
    })";
    req.close();

    std::string cmd = "curl -s https://openrouter.ai/api/v1/chat/completions "
                      "-H 'Authorization: Bearer API_KEY' "
                      "-H 'Content-Type: application/json' "
                      "-d @request.json > response.json";

    system(cmd.c_str());
    std::ifstream res("response.json");
    std::ostringstream ss;
    ss << res.rdbuf();
    std::string json = ss.str();
    size_t pos = json.find("\"content\":\"");

    if (pos != std::string::npos) 
    {
        pos += 11;
        size_t end = json.find("\"", pos);
        std::string content = json.substr(pos, end - pos);
        return content;
    }

    return "I do not know!";
}

std::string 
AssistantObject::DecodeUnicodeEscapes(
	const std::string& input) 
{
    std::string output = input;
    size_t pos;

    while ((pos = output.find("\\u003c")) != std::string::npos)
        output.replace(pos, 6, "<");

    while ((pos = output.find("\\u003e")) != std::string::npos)
        output.replace(pos, 6, ">");

    while ((pos = output.find("\\u0026")) != std::string::npos)
        output.replace(pos, 6, "&");

    return output;
}

std::string 
AssistantObject::AskOllama(
	const std::string& user_input) 
{
    std::string cmd = CURL_OLLAMA CONTENT_OLLAMA LOAD_MODEL + user_input + END_LOAD_MODEL;
    FILE* fp = popen(cmd.c_str(), "r");

    if (!fp) 
        return "Error: Failed to call Ollama.";

    char buffer[1024];
    std::ostringstream oss;

    while (fgets(buffer, sizeof(buffer), fp)) 
    {
        std::string line = buffer;
        std::size_t pos = line.find("\"response\":\"");

        if (pos != std::string::npos) 
        {
            pos += 12; 
            std::size_t end = line.find("\"", pos);
            std::string part = line.substr(pos, end - pos);
            size_t p = 0;

            while ((p = part.find("\\n", p)) != std::string::npos)
                part.replace(p, 2, "\n");

            p = 0;

            while ((p = part.find("\\\"", p)) != std::string::npos)
                part.replace(p, 2, "\"");

            part = DecodeUnicodeEscapes(part);
            oss << part;
        }
    }

    pclose(fp);
    return oss.str();
}