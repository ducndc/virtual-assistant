/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * main_assistant.c
 */

#include "virtual_functions.h"

extern std::string g_userName;

int main()
{
	Init();

	g_userName = GetUserName();

	Repeat();

	return 0;
}