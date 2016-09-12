#include "Helper.h"
#include <string>
#include <sstream>
#include <ctime>
#include <fstream>

namespace Helper
{
	template<class T>
	std::string ToString(const T& e)
	{
		std::ostringstream s;
		s << e;
		return s.str();
	}
	void WriteAppLog(const std::string& error_msg)
	{
		std::ofstream file("AppLog.txt", std::ios::app);
		file << "[" << Helper::DateTime().GetDateTimeString() << "]"
			<< std::endl << error_msg << std::endl;
		file.close();
	}
	struct DateTime
	{
		DateTime()
		{
			time_t ms;
			time(&ms);
			struct tm *info;
			localtime_s(info, &ms);
			int dt_year = 1900 + info->tm_year;
			int dt_month = info->tm_mon + 1;
			int dt_day = info->tm_mday;
			int dt_hour = info->tm_hour;
			int dt_minute = info->tm_min;
			int dt_second = info->tm_sec;
		}
		DateTime(int dt_year, int dt_month, int dt_day, int dt_hour, int dt_minute, int dt_second)
			: dt_year(dt_year), dt_month(dt_month), dt_day(dt_day),
			dt_hour(dt_hour), dt_minute(dt_minute), dt_second(dt_second)
		{}
		DateTime(int dt_year, int dt_month, int dt_day)
			: dt_year(dt_year), dt_month(dt_month), dt_day(dt_day),
			dt_hour(0), dt_minute(0), dt_second(0)
		{}
		DateTime now() const
		{
			return DateTime();
		}
		int dt_year, dt_month, dt_day, dt_hour, dt_minute, dt_second;

		std::string GetDateString() const
		{
			return std::string(dt_day < 10 ? "0" : "") + ToString(dt_day) +
				std::string(dt_month < 10 ? ".0" : ".") + ToString(dt_month) + "." +
				ToString(dt_year);
		}

		std::string GetTimeString(const std::string &sep = ":")
		{
			return std::string(dt_hour < 10 ? "0" : "") + ToString(dt_hour) + sep +
				std::string(dt_minute < 10 ? "0" : "") + ToString(dt_minute) + sep +
				std::string(dt_second < 10 ? "0" : "") + ToString(dt_second);
		}
		std::string GetDateTimeString(const std::string & sep = ":")
		{
			return GetDateString() + " " + GetTimeString(sep);
		}
	};
}