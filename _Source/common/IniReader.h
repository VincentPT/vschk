#pragma once
#include <string>
#include <map>

class IniReader
{
	std::map<std::string, std::string> _keyValueMap;
public:
	IniReader();
	~IniReader();
	void read(const std::string& fileName);

	bool get(const std::string& session, const  std::string& key, std::string& value);
};

