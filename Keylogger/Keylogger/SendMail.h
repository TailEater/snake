#pragma once
#include <fstream>
#include <vector>
#include "IO.h"
#include "Timer.h"
#include "Helper.h"
#include "stdafx.h"

namespace SMail
{
	std::string StringReplace(std::string s, const std::string& what, const std::string& with)
	{
		if (what.empty())
			return s;
		size_t sp = 0;
		while ((sp = s.find(what, sp)) != std::string::npos)
			s.replace(sp, what.length(), with), sp += with.length();
		return s;
	}
	bool CheckFileExists(const std::string& f)
	{
		std::ifstream file(f);
		return (bool)file;
	}
	Timer m_timer;
	int SendMail(const std::string& subject, const std::string& body)
	{
		::CoInitialize(NULL);
		IMailPtr oSmtp = NULL;
		oSmtp.CreateInstance("EASendMailObj.Mail");
		oSmtp->LicenseCode = _T("TryIt");
		// Set your gmail email address
		oSmtp->FromAddr = _T("rystryey@gmail.com");

		// Add recipient email address
		oSmtp->AddRecipientEx(_T("rystryey@gmail.com"), 0);

		// Set email subject
		oSmtp->Subject = _T(subject.c_str());

		// Set email body
		oSmtp->BodyText = _T(body.c_str());

		// Gmail SMTP server address
		oSmtp->ServerAddr = _T("smtp.gmail.com");

		// Use SSL 465 port, 
		oSmtp->ServerPort = 465;

		// detect SSL/TLS automatically
		oSmtp->SSL_init();

		// Gmail user authentication should use your 
		// Gmail email address as the user name. 
		// For example: your email is "gmailid@gmail.com", then the user should be "gmailid@gmail.com"
		oSmtp->UserName = _T("rystryey@gmail.com");
		oSmtp->Password = _T("bastibubu");

		_tprintf(_T("Start to send email via gmail account ...\r\n"));

		if (oSmtp->SendMail() == 0)
		{
			_tprintf(_T("email was sent successfully!\r\n"));
		}
		else
		{
			_tprintf(_T("failed to send email with the following error: %s\r\n"),
				(const TCHAR*)oSmtp->GetLastErrDescription());
		}

		if (oSmtp != NULL)
			oSmtp.Release();
		return 0;
	}
}