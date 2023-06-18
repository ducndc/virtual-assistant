/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_object.cc
 */

#include "assistant_object.h"
#include "parameter.h"

void AssistantObject::Init()
{
	system("mkdir data");
	system("clear");
	LoadSetting();
	LocalClock();
	DisplayBanner();
	Greeting();
}

void AssistantObject::DisplayBanner()
{
	system("clear");
	std::cout << VERSION;
}

void AssistantObject::LoadSetting()
{
	std::ifstream file;
	file.open(".user-settings", std::ios::in);

	if (file.good())
	{
		std::string name;

		while (!file.eof())
		{
			file >> m_userName >> m_speedOfAssistant >> m_volumeOfAssistant >> m_pithOfAssistant >> m_tSpeedOfAssistant;
		}
	}
	else
	{
		m_userName = "Duc";
		m_speedOfAssistant = 160;
		m_pithOfAssistant = 80;
		m_volumeOfAssistant = 100;
		m_tSpeedOfAssistant = 40;
	}
	file.close();
}

void AssistantObject::SaveSettings(std::string un = "Duc", int ss = 160, int sa = 100, int sp = 40, int ts = 40)
{
	std::ofstream file;
	file.open(".user-settings", std::ios::out);
	file << un << " " << ss << " "  << sa << " "  << sp << " "  << ts;
	file.close();
}

void AssistantObject::Greeting()
{
	std::cout << "\n";
	usleep(T_CONST * 300);
	Speak(m_greet);
	usleep(T_CONST * 400);
}

void AssistantObject::Speak(std::string s)
{
	std::string cmd = "espeak -a";
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

void AssistantObject::Typing(std::string t)
{
	std::thread th(&AssistantObject::Speak, this, t); //using std::thread for TTS

	for (int i = 0; t[i] != '\0'; i++)
	{
		std::cout << t[i] << std::flush;
		usleep(T_CONST * m_tSpeedOfAssistant); // speed 40ms
	}

	th.join();//finish std::thread after complete TTS (text to speech)
}

std::string AssistantObject::GetUserName()
{
	return m_userName;
}

void AssistantObject::LocalClock()
{
	std::string day[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	std::string day_no[] = {"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"};
	std::string month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	time_t now = time(0);
	tm *l_time = localtime(&now);

	if (l_time->tm_hour < 12)
    {
		m_greet = "Good morning";
    }
	else if (l_time->tm_hour >= 12)
    {
		if (l_time->tm_hour > 16)
        {
			m_greet = "Good evening";
        }
		else
        {
			m_greet = "Good Afternoon";
        }
    }

	std::cout << "   " << month[l_time->tm_mon];
	std::cout << " " << l_time->tm_mday << day_no[l_time->tm_mday % 10];
	std::cout << " " << l_time->tm_year + 1900 ;

	if ("Monday" == day[l_time->tm_wday])
    {
		std::cout << " (Sunday)";
    }
	else
    {
		std::cout << " (" << day[l_time->tm_wday - 1] << ")";
    }

	m_greet += " ";
	m_greet += m_userName;
    
	std::cout << "\t\t\t\t\t";
	std::cout << m_greet;
	std::cout << "\n   Time:-" << ( l_time->tm_hour <= 12 ? l_time->tm_hour : l_time->tm_hour - 12);
	std::cout << ":" << l_time->tm_min << (l_time->tm_hour < 12 ? "am" : "pm");
}

void AssistantObject::Repeat()
{
	system("clear");
	LocalClock();
	std::cout << " \n\n\nType Here  ---> ";
	std::cin.clear();
	getline(std::cin, m_input);  /*get command from user*/

	m_pos = m_input.find(" ");
	m_mWord = m_input.substr(0, m_pos); /*main command word*/
	m_lPos = m_input.find('\0');
	m_sWord = m_input.substr(m_pos + 1, m_lPos); /*rest word*/
	Check();
}

void AssistantObject::Check()
{
	if (("hi" == m_mWord) || ("hey" == m_mWord) || ("hello" == m_mWord) || ("hlo" == m_mWord))
	{
		Typing("Hi " + m_userName + ", how can I help you..");
	}
	else if ("play" == m_mWord)
	{
		if (("play" == m_input) || ("play " == m_input) || (" " == m_sWord) || ("  " == m_sWord) || ("   " == m_sWord))
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
	else if (("exit" == m_input) || ("q" == m_input) || ("quit" == m_input))
	{
		Speak("Good bye," + m_userName);
		usleep(T_CONST * 600);
		std::cout << "\n\n\n\n\n\n\t\t\t\t\t";
		Typing("Created By : Chung Duc Nguyen Dang");
		usleep(T_CONST * 1000);
		system("clear");
		exit(1);
	}
	else if (("find ip" == m_input) || ("find my ip" == m_input) || ("ip" == m_mWord))
	{
		Typing("Finding your IP address");
		system("ipconfig");
		system("pause");
	}
	else if (("shutdown" == m_mWord) || ("restart" == m_mWord))
	{
		Typing("Your Pc will ");
		Typing(m_mWord);
		ShutdownTimer(5);
		Speak("Now , I am going to sleep");
		if ("shutdown" == m_mWord)
			system("shutdown");
		else
			system("reboot");
		usleep(T_CONST * 10);
		exit(1);
	}
	else if (("what" == m_mWord) || ("who" == m_mWord) || ("how" == m_mWord) || ("when" == m_mWord) || ("where" == m_mWord) || ("why" == m_mWord))
	{
		if (m_input == "what is your name")
		{
			Typing("My name is VA.");
		}
		else if (("who are you" == m_input) || ("who created you" == m_input) || ("who made you" == m_input))
		{
			Typing("I am VA, a virtual assistant");
			usleep(T_CONST * 300);
			CreateNewLine();
			Typing("I was created on 16 June ,2023");
			usleep(T_CONST * 300);
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
    else if (("start hacking" == m_input) || ("hacking lab" == m_input) || ("hackingzone" == m_input) || ("hacking tools" == m_input) || ("hack" == m_mWord))
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
	else if (("yt" == m_mWord) || ("youtube" == m_mWord) || ("watch" == m_mWord))
	{
		SearchKeyWord(m_sWord, "youtube");
	}
	else if ("open" == m_mWord)
	{
		if (("chrome" == m_sWord) || ("google chrome" == m_sWord))
		{
			system("chrome");
		}
		else if (("mozilla" == m_sWord) || ("firefox" == m_sWord))
		{
			system("firefox");
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
	Repeat();
}

void AssistantObject::Settings()
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

void AssistantObject::PlaySong(std::string item)
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
		if (m_sCount % 3 == 0)
		{
			usleep(T_CONST * 200);
			system("clear");
			Speak("But you can download the song by using the command");
			usleep(T_CONST * 1300);
			CreateNewLine();
			Typing("song ");
			Typing(song_name);
		}
		m_sCount++;
	}

	file.close();
}

void AssistantObject::ConvertSpaceToUnderscore(std::string &c)
{

	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] == ' ')
			c[i] = '_';
		c[i] = tolower(c[i]);
	}
}

void AssistantObject::UpdateSong(std::string name)
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

void AssistantObject::DisplayClock(int seconds)
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

void AssistantObject::ShutdownTimer(int t)
{
	while (t)
	{
		DisplayClock(t);
		usleep(T_CONST * 900);
		t--;
	}
}

void AssistantObject::SearchKeyWord(std::string query, std::string extra)
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

	if (m_sCount % 5 == 0)
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

	if ("youtube" == extra)
	{
		url = "xdg-open https://www.youtube.com/results?search_query=";
		url += query;
		system(std::string(url).c_str());
	}
	else if ("song" == extra)
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
	else if ("pdf" == extra)
	{
		url = "xdg-open https://www.google.com/search?q=filetype%3Apdf+";
		url += query;
		system(std::string(url).c_str());
	}
	else if ("movie" == extra)
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

	m_sCount++;
}

void AssistantObject::CreateNewLine()
{
	std::cout << "\n";
}

void AssistantObject::Install(std::string fold)
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

void AssistantObject::ShowSongLists(std::string link)
{
	std::fstream file;
	int count = 0;
	char word[50], old[50];
	file.open(link);

	while (file >> word >> old)
	{
		count++;
		std::cout << word << "\n";
	}
	std::cout << "\n\t\tTotal songs available :" << count << std::endl;
	std::string p, s = "Only ";
	p = count;
	s += p;
	s += "songs are available";
	if (count != 0)
	{
		Speak(s);
	}
	file.close();
	system("pause");
}

void AssistantObject::Hacking()
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

void AssistantObject::BlockWebsite(std::string website)
{
	std::fstream file;
	file.open("echo", std::ios::app);
	file << "\n127.0.0.2 www." << website;
	Typing("Blocking the website..");
	file.close();
}

void AssistantObject::OpenFile(std::string location)
{
	std::string path = "xdg-open ", item = location;
	ConvertSpaceToUnderscore(item);
	path += item;
	Typing("Open....");
	Typing(location);
	system(std::string(path).c_str());
}

void AssistantObject::Help()
{
	m_count = 0;
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