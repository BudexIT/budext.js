#pragma once

#include "res.hpp"
#include "str.hpp"

namespace hssml {

enum LexCode {
	Word = 0,
	ContextOpen = 1,
	ContextClose = 2,
	Semicolon = 3,
	Colon = 4,
	Code = 5,
	Stylus = 6
};
inline std::string lexCodeRep(unsigned int code) {
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

struct LexInfo {
	unsigned int code;
	std::string key;
	unsigned int line;
	unsigned int column;
};

class Lexer {
public:
	Lexer() {
	}
	~Lexer() {
	}

	void feed(const std::string& input) {
		m_input = input;
	}

	const std::vector<LexInfo>& getLexed() {
		return m_lexed;
	}

	ResNull lex() {
		if(m_input.size() < 1) {
			return ResNull(Err(1, "string to lex not fed"));
		}

		std::string currentKey = "";

		bool isKeyCode = false;
		
		unsigned int line = 1;
		unsigned int column = 1;

		auto pushKey = [&](bool isStylus = false) {
			if(currentKey.size() > 0) {
				if(!isKeyCode) {
					if(isStylus) {
						m_lexed.push_back(
							LexInfo{
								LexCode::Stylus,
								currentKey,
								line,
								column
							}
						);
					}
					else {
						m_lexed.push_back(
							LexInfo{
								LexCode::Word,
								currentKey,
								line,
								column
							}
						);
					}
				}
				else {
					if(m_lexed[m_lexed.size()-1].code == LexCode::Code) {
						m_lexed[m_lexed.size()-1].key += " " + currentKey;
					}
					else {
						m_lexed.push_back(
							LexInfo{
								LexCode::Code,
								currentKey,
								line,
								column
							}
						);
					}
				}
				currentKey = "";
			}
		};

		for(char curr : m_input) {
			switch(curr) {
				case '\n': {
					line += 1;
					column = 0;
				}
				case ' ':
				case '\t': {
					pushKey();
					break;
				}
				case '{': {
					pushKey();
					m_lexed.push_back(
						LexInfo{
							LexCode::ContextOpen,
							"{",
							line,
							column
						}
					);
					break;
				}
				case '}': {
					pushKey();
					m_lexed.push_back(
						LexInfo{
							LexCode::ContextClose,
							"}",
							line,
							column
						}
					);
					break;
				}
				case ';': {
					pushKey();
					isKeyCode = false;
					m_lexed.push_back(
						LexInfo{
							LexCode::Semicolon,
							";",
							line,
							column
						}
					);
					break;
				}
				case ':': {
					pushKey(true);
					isKeyCode = true;
					m_lexed.push_back(
						LexInfo{
							LexCode::Colon,
							":",
							line,
							column
						}
					);
					break;
				}
				default: {
					currentKey += curr; 
					break;
				}
			}
			column += 1;
		}

		return ResNull();
	}

private:
	std::string m_input;
	std::vector<LexInfo> m_lexed;

};

}
