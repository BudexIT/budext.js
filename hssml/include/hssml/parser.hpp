#pragma once

#include <regex>

namespace hssml {

struct ParsePair {
	std::regex key;
	unsigned int code;
};

class Parser {
public:
	Parser() {

	}
	~Parser() {

	}

	void feed(const std::string& input) {
		m_input = input;
	}
	void parsePair(std::regex key, unsigned int code) {
		m_parsePairs.push_back(ParsePair{key, code});
	}
	void parse() {
		
	}

private:
	std::string m_input;
	std::vector<ParsePair> m_parsePairs;
	std::vector<std::string> m_parsed;

};

}
