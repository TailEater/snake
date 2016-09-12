#pragma once
#include <string>
#include <sstream>
#include <ctime>
namespace Helper
{
	template<class T>
	std::string ToString(const T&);
	
	void WriteAppLog(const std::string& error_msg);
}