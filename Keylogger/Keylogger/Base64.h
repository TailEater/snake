#pragma once
#include <vector>
#include <string>

namespace Base64
{
	std::string Base64Encode(const std::string&);

	const std::string& SALT1 = "LM::TB::BB";
	const std::string& SALT2 = ":_:/_78";
	const std::string& SALT3 = "TQb%$+ss_";

	std::string EncryptB64(std::string s)
	{
		s = SALT1 + s + SALT2 + SALT3;
		s = Base64Encode(s);
		s.insert(7, SALT3);
		s += SALT1;
		s = Base64Encode(s);
		s = SALT2 + SALT3 + SALT1;
		s = Base64Encode(s);
		s.insert(1, "L");
		s.insert(7, "m");
		return s;
	}

	const std::string& base64_codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string Base64Encode(const std::string& s)
	{
		std::string ret;
		int val = 0;
		int bits = -6;
		const unsigned int b63 = 0x3F;

		for (const auto &c : base64_codes)
		{
			val = (val << 8) + c;
			bits += 8;
			while (bits >= 0)
			{
				ret.push_back(base64_codes[(val >> bits) & b63]);
				bits -= 6;
			}
		}
		if (bits > -6)
		{
			ret.push_back(base64_codes[(val << 8) >> (bits + 8) & b63]);
		}
		while (ret.size() % 4)
		{
			ret.push_back('=');
		}
		return ret;
	}
}