#pragma once
#include <map>
#include <string>

class KeyPair
{
public:
	KeyPair(const std::string &vk = "", const std::string &in_name = "");
	std::string vk_name;
	std::string name;
};

class Keys
{
public:
	static std::map<int, KeyPair> keys;
};