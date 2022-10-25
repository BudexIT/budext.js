#include <hssml/parser.hpp>

#include <iostream>

std::string parseStyle(const std::vector<hssml::LexInfo>& info) {
	std::string style = "";
	bool styleStarted = false;
	int toSkip = 0;
	for(const auto& entry : info) {
		if(styleStarted) {
			if(entry.code == hssml::LexCode::ContextClose) {
				toSkip -= 1;

				if(toSkip <= 0) {
					break;
				}
			}

			if(toSkip > 0) {
				style += entry.key;
			}

			if(entry.code == hssml::LexCode::ContextOpen) {
				toSkip += 1;
			}
			else if(toSkip == 0) {
				styleStarted = false;
			}
		}
		else if(entry.code == hssml::LexCode::Word && entry.key == "style") {
			styleStarted = true;
		}
	}
	return style;
}

std::string parseBody(std::string& style, const std::vector<hssml::LexInfo>& info) {
	std::string body = "";

	bool bodyStarted = false;
	int toSkip = 0;

	std::vector<std::string> words;
	std::vector<std::string> fullWords;

	fullWords.push_back("body");
	
	// std::vector<std::string> styles;

	for(size_t i = 0; i < info.size(); i++) {
		const hssml::LexInfo& entry = info[i];
		
		// body detection
		if(bodyStarted) {
			if(entry.code == hssml::LexCode::ContextClose) {
				toSkip -= 1;
				if(toSkip <= 0) {
					break;
				}
			}

			// body parsing
			if(toSkip > 0) {
				// sanity checks
				bool isProperStyle = entry.code == hssml::Stylus && info[i+1].code == hssml::Colon && info[i+2].code == hssml::Code && info[i+3].code == hssml::Semicolon;
				bool isProperTag = entry.code == hssml::Word && info[i+1].code == hssml::ContextOpen;
				bool isProperTagClose = entry.code == hssml::ContextClose;
				if(!(isProperStyle || isProperTag || isProperTagClose)) {
					std::cout << "ERROR: Improper syntax on line " << entry.line << ", column " << entry.column << std::endl;
				}

				if(entry.code == hssml::Word) {
					std::string mainName = hssml::str::split(hssml::str::replace(entry.key, "#", "."), ".")[0];
					std::string id = "";
					if(hssml::str::split(entry.key, "#").size() > 1) {
						id = hssml::str::split(hssml::str::split(entry.key, "#")[1], ".")[0];
					}
					std::string classes = "";
					if(hssml::str::split(entry.key, ".").size() > 1) {
						for(size_t j = 0; j < hssml::str::split(entry.key, ".").size(); j++) {
							classes += hssml::str::split(hssml::str::split(entry.key, ".")[j], "#")[0] + " ";
						}
					}
					body += "<" + mainName + " id=\"" + id + "\" class=\"" + classes + "\">";
					fullWords.push_back(entry.key);
					words.push_back(mainName);
				}
				if(entry.code == hssml::ContextClose) {
					body += "</" + words[words.size() - 1] + ">";
					words.pop_back();
					fullWords.pop_back();
				}

				// print content
				if(entry.code == hssml::Stylus && entry.key == "content") {
					body += info[i+2].key.substr(1, info[i+2].key.size() - 2);
				}
				else if(entry.code == hssml::Stylus) {
					for(const std::string& tagName : fullWords) {
						style += " " + tagName;
					}
					style+="{";
					style+=entry.key + ":" + info[i+2].key + ";";
					style+="}";
				}


				// skip unneeded entries
				if(isProperTag) {
					toSkip += 1;
					i+=1;
				}
				else if(isProperStyle) {
					i+=3;
				}
			}

			// close and open detection lol 
			if(entry.code == hssml::LexCode::ContextOpen) {
				toSkip += 1;
			}
			else if(toSkip == 0) {
				bodyStarted = false;
			}
		}
		else if(entry.code == hssml::LexCode::Word && entry.key == "body") {
			bodyStarted = true;
		}
	}

	return body;
}
