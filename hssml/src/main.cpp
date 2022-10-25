#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <hssml/file.hpp>
#include <hssml/str.hpp>
#include <hssml/lexer.hpp>

#include <hssml/innards/index.html.h>

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

int main(int argc, char **argv) {
	std::string filename = "./index.hss";
	if(argc > 1) {
		filename = argv[1];
	}
	std::string filename_out = "./index.html";
	if(argc > 2) {
		filename_out = argv[2];
	}

	auto file = hssml::file::stringRead(filename);
	if(file.error().code()) {
		std::cout << file.error().string() << std::endl;
		return 1;
	}
	std::string input = file.unwrap();

	// Parse the input code 
	hssml::Lexer hssmlLexer; 

	hssmlLexer.feed(input);
	
	auto parseRes = hssmlLexer.lex();
	if(parseRes.error().code()) {
		std::cout << parseRes.error().string() << std::endl;
		return 1;
	}

	// Log parser's output
	// std::cout << "Parsed:\n";
	// for(const auto& entry : hssmlLexer.getParsed()) {
	// 	std::cout << "-- " << hssml::parseCodeRep(entry.code) << ":\n" << entry.key << std::endl;
	// }
	// std::cout << "Finito" << std::endl;

	// find style stuff
	std::string style = parseStyle(hssmlLexer.getLexed());

	// find body stuff idk
	std::string body = parseBody(style, hssmlLexer.getLexed());

	// output it all lol
	std::string output = hssml::str::replace(g_innard_index_html, "{style}", style);
	output = hssml::str::replace(output, "{body}", body);

	// write to the output file
	auto res = hssml::file::stringWrite(filename_out, output);
	if(res.error().code()) {
		std::cout << res.error().string() << std::endl;
		return 1;
	}

	return 0;
}