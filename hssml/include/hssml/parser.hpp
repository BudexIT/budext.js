#pragma once

#include "res.hpp"
#include "str.hpp"

namespace hssml {

enum ParseCode {
	Word = 0,
	ContextOpen = 1,
	ContextClose = 2,
	Semicolon = 3,
	Colon = 4,
	Code = 5,
	Stylus = 6
};
std::string parseCodeRep(unsigned int code) {
	switch(code) {
		case Word: return "Word";
		case ContextOpen: return "ContextOpen";
		case ContextClose: return "ContextClose";
		case Semicolon: return "Semicolon";
		case Colon: return "Colon";
		case Code: return "Code";
		case Stylus: return "Stylus";
		default: return "";
	}
}

struct ParseInfo {
	unsigned int code;
	std::string key;
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

	const std::vector<ParseInfo>& getParsed() {
		return m_parsed;
	}

	ResNull parse() {
		if(m_input.size() < 1) {
			return ResNull(Err(1, "string to parse not fed"));
		}

		std::string currentKey = "";

		bool isKeyCode = false;
		
		auto pushKey = [&](bool isStylus = false) {
			if(currentKey.size() > 0) {
				if(!isKeyCode) {
					if(isStylus) {
						m_parsed.push_back(
							ParseInfo{
								ParseCode::Stylus,
								currentKey
							}
						);
					}
					else {
						m_parsed.push_back(
							ParseInfo{
								ParseCode::Word,
								currentKey
							}
						);
					}
				}
				else {
					if(m_parsed[m_parsed.size()-1].code == ParseCode::Code) {
						m_parsed[m_parsed.size()-1].key += " " + currentKey;
					}
					else {
						m_parsed.push_back(
							ParseInfo{
								ParseCode::Code,
								currentKey
							}
						);
					}
				}
				currentKey = "";
			}
		};
	
		for(char curr : m_input) {
			switch(curr) {
				case ' ':
				case '\t':
				case '\n': {
					pushKey();
					break;
				}
				case '{': {
					pushKey();
					m_parsed.push_back(
						ParseInfo{
							ParseCode::ContextOpen,
							"{"
						}
					);
					break;
				}
				case '}': {
					pushKey();
					m_parsed.push_back(
						ParseInfo{
							ParseCode::ContextClose,
							"}"
						}
					);
					break;
				}
				case ';': {
					pushKey();
					isKeyCode = false;
					m_parsed.push_back(
						ParseInfo{
							ParseCode::Semicolon,
							";"
						}
					);
					break;
				}
				case ':': {
					pushKey(true);
					isKeyCode = true;
					m_parsed.push_back(
						ParseInfo{
							ParseCode::Colon,
							":"
						}
					);
					break;
				}
				default: {
					currentKey += curr; 
					break;
				}
			}
		}

		return ResNull();
	}

private:
	std::string m_input;
	std::vector<ParseInfo> m_parsed;

};

}
