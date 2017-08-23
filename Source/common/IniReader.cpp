#include "IniReader.h"
#include "string_util.hpp"
#include <fstream>

IniReader::IniReader()
{
}


IniReader::~IniReader()
{
}



void IniReader::read(const std::string& fileName) {
	std::ifstream infile(fileName);
	if (!infile.is_open()) {
		return;
	}
	std::string line;
	std::string current_session;
	_keyValueMap.clear();
	while (std::getline(infile, line)) {
		trim(line);
		if (line[0] == '[' && line[line.size() - 1] == ']') {
			current_session = line.substr(1, line.size() - 2);
			trim(current_session);
		}
		else {
			auto idx = line.find_first_of('=');
			if (idx == std::string::npos) {
				continue;
			}
			auto key = line.substr(0, idx);
			trim(key);
			auto value = line.substr(idx + 1);
			trim(value);

			key = current_session + "_" + key;
			_keyValueMap[key] = value;
		}
	}

	infile.close();
}

bool IniReader::get(const std::string& session, const std::string& key, std::string& value) {
	auto it = _keyValueMap.find(session + "_" + key);
	if (it == _keyValueMap.end()) {
		return false;
	}
	value = it->second;

	return true;
}
