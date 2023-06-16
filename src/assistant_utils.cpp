/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * assistant_utils.cpp
 */

#include "assistant_utils.h"

#define T_CONST 1000
#define VERSION "ASSISTANT VERTION 1"

std::string g_greet;
std::string g_nameUser;

int g_pithOfAssistant;
int g_speedOfAssistant;
int g_volumeOfAssistant;
int g_tSpeedOfAssistant;

void assistant_utils::Init()
{
	system("mkdir data");
	system("clear");

	LoadSetting();
	LocalClock();
	DisplayBanner();
	Greeting();
}

void assistant_utils::DisplayBanner()
{
	system("clear");
	std::cout << "ASSISTANT VERTION 1";
}

void assistant_utils::LoadSetting()
{
	std::ifstream file;
	file.open(".user-settings", std::ios::in);

	if (file.good())
	{
		std::string name;

		while (!file.eof())
		{
			file >> g_nameUser >> g_speedOfAssistant >> g_volumeOfAssistant >> g_pithOfAssistant >> g_tSpeedOfAssistant;
		}

	}
	else
	{
		g_nameUser = "Duc";
		g_speedOfAssistant = 160;
		g_pithOfAssistant = 40;
		g_volumeOfAssistant = 100;
		g_tSpeedOfAssistant = 40;
	}
	file.close();
}

void assistant_utils::SaveSettings(std::string un = "Duc", int ss = 160, int sa = 100, int sp = 40, int ts = 40)
{
	std::ofstream file;
	file.open(".user-settings", std::ios::out);

	file << un << " " << ss << " "  << sa << " "  << sp << " "  << ts;

	file.close();
}

void assistant_utils::Greeting()
{
	std::cout << "\n";
	usleep(T_CONST * 300);
	Speak(g_greet);
	usleep(T_CONST * 400);
}


void assistant_utils::Speak(std::string s)
{
	std::string cmd = "espeak -a";
	cmd += std::to_string(g_volumeOfAssistant);
	cmd += " -p";
	cmd += std::to_string(g_pithOfAssistant);
	cmd += " -s";
	cmd += std::to_string(g_speedOfAssistant);
	cmd += " \"";
	cmd += s;
	cmd += "\"";

	system(cmd.c_str());

}

void assistant_utils::Typing(std::string t)
{

	std::thread th(assistant_utils::Speak, t); //using std::thread for TTS

	for (int i = 0; t[i] != '\0'; i++)
	{
		std::cout << t[i] << std::flush;
		usleep(T_CONST * g_tSpeedOfAssistant); // speed 40ms
	}

	th.join();//finish std::thread after complete TTS (text to speech)
}

std::string assistant_utils::GetUserName()
{
	return g_nameUser;
}

void assistant_utils::LocalClock()
{
	std::string day[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	std::string day_no[] = {"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"};
	std::string month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	time_t now = time(0);
	tm *l_time = localtime(&now);

	if (l_time->tm_hour < 12)
    {
		g_greet = "Good morning";
    }
	else if (l_time->tm_hour >= 12)
    {
		if (l_time->tm_hour > 16)
        {
			g_greet = "Good evening";
        }
		else
        {
			g_greet = "Good Afternoon";
        }
    }

	std::cout << "   " << month[l_time->tm_mon];
	std::cout << " " << l_time->tm_mday << day_no[l_time->tm_mday % 10];
	std::cout << " " << l_time->tm_year + 1900 ;

	if (day[l_time->tm_wday] == "Monday")
    {
		std::cout << " (Sunday)";
    }
	else
    {
		std::cout << " (" << day[l_time->tm_wday - 1] << ")";
    }

	g_greet += " ";
	g_greet += g_nameUser;
    
	std::cout << "\t\t\t\t\t";
	std::cout << g_greet;
	std::cout << "\n   Time:-" << ( l_time->tm_hour <= 12 ? l_time->tm_hour : l_time->tm_hour - 12);
	std::cout << ":" << l_time->tm_min << (l_time->tm_hour < 12 ? "am" : "pm");
}