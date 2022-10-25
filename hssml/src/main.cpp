#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <hssml/file.hpp>
#include <hssml/str.hpp>
#include <hssml/lexer.hpp>
#include <hssml/parser.hpp>

int main(int argc, char **argv) {
	std::string filename = "./index.hss";
	if(argc > 1) {
		filename = argv[1];
	}

	std::string filename_out = "./index.html";
	if(argc > 2) {
		filename_out = argv[2];
	}

	std::string htmlTemplate = "<!doctype html><html><head><style>{style}</style></head><body>{body}</body></html>";
	if(argc > 3) {
		std::string htmlFilename = argv[3];
		auto html = hssml::file::stringRead(htmlFilename);
		if(html.error().code()) {
			std::cout << "HTML Template: " << html.error().string() << ", fallback to standard template." << std::endl;
		}
		else {
			htmlTemplate = html.unwrap();
		}
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
	std::string output = hssml::str::replace(htmlTemplate, "{style}", style);
	output = hssml::str::replace(output, "{body}", body);

	// write to the output file
	auto res = hssml::file::stringWrite(filename_out, output);
	if(res.error().code()) {
		std::cout << res.error().string() << std::endl;
		return 1;
	}

	return 0;
}