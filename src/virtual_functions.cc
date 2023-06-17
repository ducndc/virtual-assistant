/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_utils.cc
 */

#include "virtual_functions.h"


int pos = 0;
int l_pos = 0;
int g_count = 0;
int s_count = 0;

std::string g_userName;
std::string m_word;
std::string s_word;
std::string g_input;

void Repeat()
{
	system("clear");
	LocalClock();
	std::cout << " \n\n\nType Here  ---> ";
	std::cin.clear();
	getline(std::cin, g_input);  /*get command from user*/

	pos = g_input.find(" ");
	m_word = g_input.substr(0, pos); /*main command word*/
	l_pos = g_input.find('\0');
	s_word = g_input.substr(pos + 1, l_pos); /*rest word*/

	Check();
}

void Check()
{
	if (("hi" == m_word) || ("hey" == m_word) || ("hello" == m_word) || ("hlo" == m_word))
	{
		Typing("Hi " + g_userName + ", how can I help you..");
	}
	else if ("play" == m_word)
	{
		if (("play" == g_input) || ("play " == g_input) || (" " == s_word) || ("  " == s_word) || ("   " == s_word))
		{
			Speak("Sorry " + g_userName + " ,you does not enter song name");
		}
		else
		{
			PlaySong(s_word);
		}
	}
	else if (("update" == m_word) || ("updating" == m_word))
	{
		system("clear");
		CreateNewLine();
		Typing("Updating the song list...");
		usleep(T_CONST * 100);
		system("clear");
		CreateNewLine();
		Typing("Please wait");
		UpdateSong("punjabi");
		UpdateSong("english");
		UpdateSong("hindi");
		UpdateSong("others");
		system("clear");
		remove("data/songs.txt");
		rename("data/temp.txt", "data/songs.txt");
		CreateNewLine();
		Typing("All songs are updated in the file");
	}
	else if (g_input == "exit" || g_input == "q" || g_input == "quit")
	{
		Speak("Good bye," + g_userName);
		usleep(T_CONST * 600);
		std::cout << "\n\n\n\n\n\n\t\t\t\t\t";
		Typing("Created By : Chung Duc Nguyen Dang");
		usleep(T_CONST * 1000);
		system("clear");
		exit(1);
	}
	else if (g_input == "find ip" || g_input == "find my ip" || m_word == "ip")
	{
		Typing("Finding your IP address");
		system("ipconfig");
		system("pause");
	}
	else if (m_word == "shutdown" || m_word == "restart")
	{
		Typing("Your Pc will ");
		Typing(m_word);
		ShutdownTimer(5);
		Speak("Now , I am going to sleep");
		if (m_word == "shutdown")
			system("shutdown");
		else
			system("reboot");
		usleep(T_CONST * 10);
		exit(1);
	}

	else if (m_word == "what" || m_word == "who" || m_word == "how" || m_word == "when" || m_word == "where" || m_word == "why")
	{
		if (g_input == "what is your name")
		{
			Typing("My name is VA.");
		}
		else if (g_input == "who are you" || g_input == "who created you" || g_input == "who made you")
		{
			Typing("I am VA, a virtual assistant");
			usleep(T_CONST * 300);
			CreateNewLine();
			Typing("I was created on 16 June ,2023");
			usleep(T_CONST * 300);
		}
		else
			SearchKeyWord(g_input);
	}

	else if (g_input == "settings" || g_input == "setting" || g_input == "set")
		Settings();

	else if (m_word == "song" || m_word == "music")
		SearchKeyWord(s_word, "song");

	else if (g_input == "install")
	{
		system("mkdir My_beat");

		Install("hindi");
		Install("english");
		Install("punjabi");
		Install("others");
		std::cout << "\nCreating folders...";
		usleep(T_CONST * 200);
		std::cout << "\nCreating files...";
		usleep(T_CONST * 200);
		system("clear");

		Typing("\nAll files are installed");
		usleep(T_CONST * 300);
	}

	else if (g_input == "help")
		Help();

	else if (m_word == "movie")
		SearchKeyWord(s_word, "movie");

	else if (m_word == "pdf")
		SearchKeyWord(s_word, "pdf");

	else if (m_word == "search")
		SearchKeyWord(s_word);

	else if (m_word == "cmd")
		system(s_word.c_str());

	else if (g_input == "start hacking" || g_input == "hacking lab" || g_input == "hackingzone" || g_input == "hacking tools" || m_word == "hack")
	{
		Hacking();
	}
	else if (m_word == "list")
	{
		if (s_word == "all songs" || s_word == "songs")
			ShowSongLists("data/songs.txt");
	}
	else if (m_word == "block")
	{
		BlockWebsite(s_word);
	}
	else if (m_word == "yt" || m_word == "youtube" || m_word == "watch")
	{
		SearchKeyWord(s_word, "youtube");
	}
	else if (m_word == "open")
	{
		if (s_word == "chrome" || s_word == "google chrome")
		{
			system("chrome");
		}
		else if (s_word == "mozilla" || s_word == "firefox")
		{
			system("firefox");
		}
		else
			OpenFile(s_word);
	}
	else
	{
		Speak("Sorry " + g_userName + ", unknown command...");
		g_count++;
		if (g_count >= 3)
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
	Repeat();
}

void Settings()
{
	std::string un;
	int ss, sa, sp, ts;

	std::cout << "\n\n";
	Typing("Enter data in the following given format:\n");
	std::cout << "\n1.user name(single word only)";
	std::cout << "\n2.speak speed(in WPM)";
	std::cout << "\n3.speak volume(0-200)";
	std::cout << "\n4.speak pitch(0-99)";
	std::cout << "\n5.typing speed(in ms)";
	std::cout << "\n\nExample 1:\n";
	std::cout << "Duc 160 100 40 40";
	std::cout << "\n\nExample 2:\n";
	std::cout << "Duc 150 120 60 30";
	std::cout << "\n\n\n---> ";
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

void PlaySong(std::string item)
{
	std::ifstream file;
	std::string song_name;
	song_name = item;
	ConvertSpaceToUnderscore(item);
	char song[30], singer[30];
	char path[90] = "xdg-open My_beat/";
	file.open("data/songs.txt", std::ios::app);
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
	system("clear");

	if (song != item)
	{
		Typing(song_name);
		Typing(" not found.");
		if (s_count % 3 == 0)
		{
			usleep(T_CONST * 200);
			system("clear");
			Speak("But you can download the song by using the command");
			usleep(T_CONST * 1300);
			CreateNewLine();
			Typing("song ");
			Typing(song_name);
		}
		s_count++;
	}

	file.close();
}

void ConvertSpaceToUnderscore(std::string &c)
{

	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] == ' ')
			c[i] = '_';
		c[i] = tolower(c[i]);
	}
}

void UpdateSong(std::string name)
{
	std::fstream a, b;
	char word[20], old[20];
	system("clear");
	a.open("My_beat/" + name + "/list.txt");
	b.open("data/temp.txt", std::ios::app | std::ios::ate);
	while (a >> word)
	{
		b << word << " " << name << "\n";
	}
	b.close();
	a.close();
}

void DisplayClock(int seconds)
{
	int h, m;
	h = m = 0;

	system("clear");
	std::cout << "\n\n";
	std::cout << std::setfill(' ') << std::setw(75) << "	        TIMER	      	\n";
	std::cout << std::setfill(' ') << std::setw(75) << " --------------------------\n";
	std::cout << std::setfill(' ') << std::setw(29);
	std::cout << "| " << std::setfill('0') << std::setw(2) << h << " hrs | ";
	std::cout << std::setfill('0') << std::setw(2) << m << " min | ";
	std::cout << std::setfill('0') << std::setw(2) << seconds << " sec |" << std::endl;
	std::cout << std::setfill(' ') << std::setw(75) << " --------------------------\n";
}

void ShutdownTimer(int t)
{
	while (t)
	{
		DisplayClock(t);
		usleep(T_CONST * 900);
		t--;
	}
}

void SearchKeyWord(std::string query, std::string extra)
{
	for (int i = 0; query[i] != '\0'; i++)
	{
		if (query[i] == ' ')
			query[i] = '+';
	}

	usleep(T_CONST * 200);
	system("clear");
	CreateNewLine();
	Typing("Cheking internet connection...");

	if (s_count % 5 == 0)
	{
		CreateNewLine();
		usleep(T_CONST * 90);
		std::cout << "Colleting information..\n";
		usleep(T_CONST * 50);
		std::cout << "securing the data..\n";
		usleep(T_CONST * 30);
		std::cout << "clear the cookies..\n";
		usleep(T_CONST * 100);
		system("ifconfig");
		CreateNewLine();
		Typing("All protocols are secured...");
	}

	usleep(T_CONST * 250);
	Speak("Connecting to your browser.");
	std::string url;

	if (extra == "youtube")
	{
		url = "xdg-open https://www.youtube.com/results?search_query=";
		url += query;
		system(std::string(url).c_str());
	}
	else if (extra == "song")
	{
		// for international songs
		url = "xdg-open https://en.muzmo.org/search?q=";
		url += query;
		system(std::string(url).c_str());
		usleep(T_CONST * 50);

		url = "xdg-open https://m.soundcloud.com/search?q=";
		url += query;
		system(std::string(url).c_str());

		url = "xdg-open https://www.google.com/search?q=";
		url += query;
		url += "+djpunjab";
		system(std::string(url).c_str());
		usleep(T_CONST * 50);
	}
	else if (extra == "pdf")
	{
		url = "xdg-open https://www.google.com/search?q=filetype%3Apdf+";
		url += query;
		system(std::string(url).c_str());
	}
	else if (extra == "movie")
	{
		url = "xdg-open https://www.google.com/search?q=";
		url += query;
		url += "+-inurl%3A(htm%7Chtml%7Cphp%7Cpls%7Ctxt)+intitle%3Aindeof+%22last+modified%22(mp4%7Cmkv%7Cwma%7Caac%7Cavi)";
		system(std::string(url).c_str());
	}
	else
	{
		url = "xdg-open https://www.google.com/search?q=";
		url += query;
		system(std::string(url).c_str());
	}

	s_count++;
}

void CreateNewLine()
{
	std::cout << "\n";
}

void Install(std::string fold)
{
	std::fstream file;
	std::string foldname, filename;
	foldname = "mkdir My_beat/";

	foldname += fold;
	system(std::string(foldname).c_str());
	filename = "My_beat/";
	filename += fold;
	filename += "/list.txt";
	file.open(filename, std::ios::app);
	file.close();
}

void ShowSongLists(std::string link)
{
	std::fstream file;
	int g_count = 0;
	char word[50], old[50];
	file.open(link);

	while (file >> word >> old)
	{
		g_count++;
		std::cout << word << "\n";
	}
	std::cout << "\n\t\tTotal songs available :" << g_count << std::endl;
	std::string p, s = "Only ";
	p = g_count;
	s += p;
	s += "songs are available";
	if (g_count != 0)
	{
		Speak(s);
	}
	file.close();
	system("pause");
}

void Hacking()
{
	system("clear");
	system("color f");
	Speak("You are Welcome in the Hacking Lab");
	std::cout << std::setfill(' ') << std::setw(50) << "      ________       \n";
	usleep(T_CONST * 100);
	std::cout << std::setfill(' ') << std::setw(50) << "     |        |      \n";
	usleep(T_CONST * 100);
	std::cout << std::setfill(' ') << std::setw(50) << "     |  #   # |      \n";
	usleep(T_CONST * 100);
	std::cout << std::setfill(' ') << std::setw(50) << "     |  #   # |      \n";
	usleep(T_CONST * 100);
	std::cout << std::setfill(' ') << std::setw(50) << "     |   # #  |      \n";
	usleep(T_CONST * 100);
	std::cout << std::setfill(' ') << std::setw(50) << "     |    #   |      \n";
	usleep(T_CONST * 100);
	std::cout << std::setfill(' ') << std::setw(50) << "     |________|      \n";
	CreateNewLine();
	usleep(T_CONST * 1000);
	system("color c");
	std::cout << std::setfill(' ') << std::setw(50) << " Duc Hacking Lab  \n";
	usleep(T_CONST * 1000);
	CreateNewLine();
	Typing("Still in development...");
}

void BlockWebsite(std::string website)
{
	std::fstream file;
	file.open("C:/WINDOWS/system32/drivers/etc/hosts", std::ios::app);
	file << "\n127.0.0.2 www." << website;
	Typing("Blocking the website..");
	file.close();
}

void OpenFile(std::string location)
{
	std::string path = "xdg-open ", item = location;
	ConvertSpaceToUnderscore(item);
	path += item;
	Typing("Open....");
	Typing(location);
	system(std::string(path).c_str());
}

void Help()
{
	g_count = 0;
	Speak("you can use only these cammands");
	system("clear");
	std::cout << "\n\n";
	system("color f");
	CreateNewLine();
	std::cout << std::setfill(' ') << std::setw(75) << "----------------------------\n";
	std::cout << std::setfill(' ') << std::setw(75) << "          Commands          \n";
	std::cout << std::setfill(' ') << std::setw(75) << "--------------------------\n\n";
	std::cout << std::setfill(' ') << std::setw(75) << "    1.search (any question)  \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    2.open (google,mozilla)  \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    3.block (website name)   \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    4.song (song name)       \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    5.update                 \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    6.watch (videoname)      \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    7.pdf (pdfname)          \n";
	std::cout << std::setfill(' ') << std::setw(75) << "    8.movie (moviename)      \n";
	std::cout << std::setfill(' ') << std::setw(85) << "    9.what/how/where/who/why (question)\n";
	std::cout << std::setfill(' ') << std::setw(75) << "   10.cmd (cmd commands)     \n";
	std::cout << std::setfill(' ') << std::setw(75) << "   11.find my ip             \n";
	std::cout << std::setfill(' ') << std::setw(75) << "   12.play (song name)       \n";
	std::cout << std::setfill(' ') << std::setw(75) << "   13.list songs             \n";
	std::cout << std::setfill(' ') << std::setw(75) << "   10.exit/quit/q            \n";
	std::cout << std::setfill(' ') << std::setw(75) << "   11.shutdown/restart       \n";
	std::cout << std::setfill(' ') << std::setw(75) << "   12.install                \n";
	usleep(T_CONST * 3000);
}