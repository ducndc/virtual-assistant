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

#include "assistant_object.hpp"
#include "parameter.hpp"

extern std::atomic<bool> running;

void 
AssistantObject::Init(WINDOW* win)
{
	m_win = win;
	m_terminate = false;
    box(m_win, 0, 0);
    mvwprintw(m_win, 0, 2, " Virtual Assistant ");
    wrefresh(m_win);
	//system(MAKE_DIR_CMD "data");
	LoadSetting();
	LocalClock();
	DisplayBanner();
	Greeting();
}

void 
AssistantObject::DisplayBanner(void)
{
	
	//std::cout << VERSION;
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
	//std::cout << "\n";
	usleep(T_CONST * 300);
	Speak(m_greet);
	usleep(T_CONST * 400);
}

void 
AssistantObject::Speak(
	std::string s)
{
    std::string cmd = ESPEAK_CMD;
    // volume: dùng option -a (0-200)
    cmd += " -a";
    cmd += std::to_string(m_volumeOfAssistant);
    // pitch: option -p (0-99)
    cmd += " -p";
    cmd += std::to_string(m_pithOfAssistant);
    // speed: option -s (80-450)
    cmd += " -s";
    cmd += std::to_string(m_speedOfAssistant);
    cmd += " \"";
    cmd += s;
    cmd += "\"";
    system(cmd.c_str());
}

void 
AssistantObject::Typing(
	const std::string& message)
{
	std::thread th(&AssistantObject::Speak, this, message); //using std::thread for TTS
	wmove(m_win, 10, 10);
	
    for (char ch : message) {
    	waddch(m_win, ch);
        refresh();
        napms(50);
    }
    
    th.join();//finish std::thread after complete TTS (text to speech)
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
		mvwprintw(m_win, 1, 2, "[*] (Sunday)");
    }
	else
    {
    	mvwprintw(m_win, 1, 2, "[*] %s", day[l_time->tm_wday - 1].c_str());
    }

	m_greet += " ";
	m_greet += m_userName;
    
    mvwprintw(m_win, 2, 2, "[*] %s", m_greet.c_str());
    mvwprintw(m_win, 3, 2, "[*] Time: %dh%dm %s", 
    	(l_time->tm_hour <= 12 ? l_time->tm_hour : l_time->tm_hour - 12), 
    	l_time->tm_min, (l_time->tm_hour < 12 ? "am" : "pm"));
}

void 
AssistantObject::Repeat(void)
{
    char input[128] = {0};
    int max_y, max_x;
    getmaxyx(m_win, max_y, max_x);

    int input_row = max_y - 2;

    while (running) 
    {
        box(m_win, 0, 0);
        mvwprintw(m_win, 0, 2, " Virtual Assistant ");
        LocalClock();
		char input[128] = {0};
		int pos = 0;
		mvwhline(m_win, input_row, 1, ' ', max_x - 2);
		mvwprintw(m_win, input_row, 2, "[*] Type: ---> ");
		wmove(m_win, input_row, 4);
		wrefresh(m_win);
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
        refresh();
        Check();
    }

    if (m_terminate)
    	return;
}

void 
AssistantObject::Check(void)
{
	if (("hi" == m_mWord) || ("hey" == m_mWord) || 
		("hello" == m_mWord) || ("hlo" == m_mWord))
	{
		Typing("Hi " + m_userName + ", how can I help you..");
	}
	else if ("play" == m_mWord)
	{
		if (("play" == m_input) || ("play " == m_input) || 
			(" " == m_sWord) || ("  " == m_sWord) || ("   " == m_sWord))
		{
			Speak("Sorry " + m_userName + " ,you does not enter song name");
		}
		else
		{
			PlaySong(m_sWord);
		}
	}
	else if (("update" == m_mWord) || ("updating" == m_mWord))
	{
		
		
		Typing("Updating the song list...");
		usleep(T_CONST * 100);
		
		
		Typing("Please wait");
		UpdateSong("punjabi");
		UpdateSong("english");
		UpdateSong("hindi");
		UpdateSong("others");
		
		remove("data/songs.txt");
		rename(TEMP_FILE_PATH, "data/songs.txt");
		
		Typing("All songs are updated in the file");
	}
	else if (("exit" == m_input) || ("q" == m_input) || ("quit" == m_input))
	{
		Speak("Good bye," + m_userName);
		usleep(T_CONST * 600);
		Typing("Created By : " AUTHOR);
		usleep(T_CONST * 1000);
		m_terminate = true;
		
		//exit(1);
	}
	else if (("find ip" == m_input) || ("find my ip" == m_input) || ("ip" == m_mWord))
	{
		Typing("Finding your IP address");
		system(IFCONFIG_CMD);
		//WaitOut();
	}
	else if (("shutdown" == m_mWord) || ("restart" == m_mWord))
	{
		Typing("Your Pc will ");
		Typing(m_mWord);
		ShutdownTimer(5);
		Speak("Now , I am going to sleep");
		if ("shutdown" == m_mWord)
			system(SHUTDOWN_CMD);
		else
			system(RESTART_CMD);
		usleep(T_CONST * 10);
		exit(1);
	}
	else if (("what" == m_mWord) || ("who" == m_mWord) || 
		("how" == m_mWord) || ("when" == m_mWord) || 
		("where" == m_mWord) || ("why" == m_mWord))
	{
		if (m_input == "what is your name")
		{
			Typing("My name is VA.");
		}
		else if (("who are you?" == m_input) || 
			("who created you?" == m_input) || 
			("who made you?" == m_input))
		{
			Typing("I am VA, a virtual assistant, I was created on 16 June ,2023");
		}
		else
        {
			SearchKeyWord(m_input);
        }
    }
	else if (("settings" == m_input) || ("setting" == m_input) || ("set" == m_input))
	{	
        Settings();
    }
	else if (("song" == m_mWord) || ("music" == m_mWord))
	{	
        SearchKeyWord(m_sWord, "song");
    }
	else if ("install" == m_input)
	{
		system(MAKE_DIR_CMD "My_beat");
		Install("hindi");
		Install("english");
		Install("punjabi");
		Install("others");
		//std::cout << "\nCreating folders...";
		usleep(T_CONST * 200);
		//std::cout << "\nCreating files...";
		usleep(T_CONST * 200);
		

		Typing("\nAll files are installed");
		usleep(T_CONST * 300);
	}
	else if ("help" == m_input)
	{	
        Help();
    }
	else if ("movie" == m_mWord)
	{	
        SearchKeyWord(m_sWord, "movie");
    }
    else if ("pdf" == m_mWord)
	{	
        SearchKeyWord(m_sWord, "pdf");
    }
    else if ("search" == m_mWord)
	{	
        SearchKeyWord(m_sWord);
    }
    else if ("cmd" == m_mWord)
	{	
        system(m_sWord.c_str());
    }
    else if (("start hacking" == m_input) || ("hacking lab" == m_input) || 
    	("hackingzone" == m_input) || ("hacking tools" == m_input) || ("hack" == m_mWord))
	{
		Hacking();
	}
	else if ("list" == m_mWord)
	{
		if (("all songs" == m_sWord) || ("songs" == m_sWord))
			ShowSongLists("data/songs.txt");
	}
	else if ("block" == m_mWord)
	{
		BlockWebsite(m_sWord);
	}
	else if ("note" == m_mWord)
	{
		Note();
	}
	else if (("yt" == m_mWord) || ("youtube" == m_mWord) || ("watch" == m_mWord))
	{
		SearchKeyWord(m_sWord, "youtube");
	}
	else if ("open" == m_mWord)
	{
		if (("chrome" == m_sWord) || ("google chrome" == m_sWord))
		{
			system(CHORME_CMD);
		}
		else if (("mozilla" == m_sWord) || ("firefox" == m_sWord))
		{
			system(FIREFOX_CMD);
		}
		else
			OpenFile(m_sWord);
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
	//Repeat();
}

void 
AssistantObject::Settings(void)
{
	std::string un;
	int ss, sa, sp, ts;
	//std::cout << "\n\n";
	Typing("Enter data in the following given format:\n");
	//std::cout << "\n1.user name(single word only)";
	//std::cout << "\n2.speak speed(in WPM)";
	//std::cout << "\n3.speak volume(0-200)";
	//std::cout << "\n4.speak pitch(0-99)";
	//std::cout << "\n5.typing speed(in ms)";
	//std::cout << "\n\nExample 1:\n";
	//std::cout << "Duc 160 100 40 40";
	//std::cout << "\n\nExample 2:\n";
	//std::cout << "Duc 150 120 60 30";
	//std::cout << "\n\n\n---> ";
	std::cin >> un >> ss >> sa >> sp >> ts;

	if ((sa <= 200 && sa > 0) && (sp <= 99 && sp > 0 ))
	{
		SaveSettings(un, ss, sa, sp, ts);
		Typing("Restart me to see changes");
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
			Typing("Playing the song ");
			usleep(T_CONST * 150);
			Typing(song_name);
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
		Typing(song_name);
		Typing(" not found.");

		if (m_sCount % 3 == 0)
		{
			usleep(T_CONST * 200);
			
			Speak("But you can download the song by using the command");
			usleep(T_CONST * 1300);
			
			Typing("song ");
			Typing(song_name);
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
	
	
	Typing("Cheking internet connection...");

	if (m_sCount % 5 == 0)
	{
		
		usleep(T_CONST * 90);
		//std::cout << "Colleting information..\n";
		usleep(T_CONST * 50);
		//std::cout << "securing the data..\n";
		usleep(T_CONST * 30);
		//std::cout << "clear the cookies..\n";
		usleep(T_CONST * 100);
		system(IFCONFIG_CMD);
		
		Typing("All protocols are secured...");
	}

	usleep(T_CONST * 250);
	Speak("Connecting to your browser.");
	std::string url;

	if ("youtube" == extra)
	{
		url = "xdg-open https://www.youtube.com/results?search_query=";
		url += query;
		system(std::string(url).c_str());
	}
	else if ("song" == extra)
	{
		// for international songs
		url = XDG_OPEN_CMD "https://en.muzmo.org/search?q=";
		url += query;
		system(std::string(url).c_str());
		usleep(T_CONST * 50);

		url = XDG_OPEN_CMD "https://m.soundcloud.com/search?q=";
		url += query;
		system(std::string(url).c_str());

		url = XDG_OPEN_CMD "https://www.google.com/search?q=";
		url += query;
		system(std::string(url).c_str());
		usleep(T_CONST * 50);
	}
	else
	{
		url = XDG_OPEN_CMD "https://www.google.com/search?q=";
		url += query;
		system(std::string(url).c_str());
	}

	m_sCount++;
}

void 
AssistantObject::CreateNewLine(void)
{
	//std::cout << "\n";
}

void 
AssistantObject::Install(
	std::string fold)
{
	std::fstream file;
	std::string foldname, filename;
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
		//std::cout << word << "\n";
	}

	//std::cout << "\n\t\tTotal songs available :" << count << std::endl;
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
	//std::cout << std::setfill(' ') << std::setw(50) << "      ________       \n";
	usleep(T_CONST * 100);
	//std::cout << std::setfill(' ') << std::setw(50) << "     |        |      \n";
	usleep(T_CONST * 100);
	//std::cout << std::setfill(' ') << std::setw(50) << "     |  #   # |      \n";
	usleep(T_CONST * 100);
	//std::cout << std::setfill(' ') << std::setw(50) << "     |  #   # |      \n";
	usleep(T_CONST * 100);
	//std::cout << std::setfill(' ') << std::setw(50) << "     |   # #  |      \n";
	usleep(T_CONST * 100);
	//std::cout << std::setfill(' ') << std::setw(50) << "     |    #   |      \n";
	usleep(T_CONST * 100);
	//std::cout << std::setfill(' ') << std::setw(50) << "     |________|      \n";
	
	usleep(T_CONST * 1000);
	//std::cout << std::setfill(' ') << std::setw(50) << " Duc Hacking Lab  \n";
	usleep(T_CONST * 1000);
	
	Typing("Still in development...");
	//WaitOut();
}

void 
AssistantObject::BlockWebsite(
	std::string website)
{
	std::fstream file;
	file.open("echo", std::ios::app);
	file << "\n127.0.0.2 www." << website;
	Typing("Blocking the website..");
	file.close();
}

void 
AssistantObject::Note(void)
{
	std::string cmd = VIM_CMD NOTE_FILE_PATH; 

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
	Typing("Open....");
	Typing(location);
	system(std::string(path).c_str());
}

void 
AssistantObject::Help(void)
{
	m_count = 0;
	
	
	//std::cout << "-----------------------------\n";
	//std::cout << "           Commands          \n";
	//std::cout << "-----------------------------\n";
	//std::cout << "    1.search (any question)  \n";
	//std::cout << "    2.open (google,mozilla)  \n";
	//std::cout << "    3.block (website name)   \n";
	//std::cout << "    4.song (song name)       \n";
	//std::cout << "    5.update                 \n";
	//std::cout << "    6.watch (videoname)      \n";
	//std::cout << "    7.pdf (pdfname)          \n";
	//std::cout << "    8.movie (moviename)      \n";
	//std::cout << "    9.what/how/where/who/why (question)\n";
	//std::cout << "   10.cmd (cmd commands)     \n";
	//std::cout << "   11.find my ip             \n";
	//std::cout << "   12.play (song name)       \n";
	//std::cout << "   13.list songs             \n";
	//std::cout << "   10.exit/quit/q            \n";
	//std::cout << "   11.shutdown/restart       \n";
	//std::cout << "   12.install                \n";
	//std::cout << "   13.note                   \n";
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
	//std::cout << "   Enter q to continue" << std::endl;
	do {
		wait = GetHiddenInput();
	    usleep(T_CONST * 100);
	} while (wait != QUIT_KEY);
}