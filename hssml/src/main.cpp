#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <hssml/file.hpp>

int main(int argc, char **argv) {
	std::string filename = "./index.hss";
	if(argc > 1) {
		filename = argv[1];
	}

	auto file = hssml::file::stringRead(filename);

	if(file.error().code()) {
		std::cout << file.error().string() << std::endl;
		return 1;
	}

	std::string templateHTML = 
	#include <innards/index.html.h>
	
	std::string input = file.unwrap();

	std::string output;

	auto res = hssml::file::stringWrite(filename + ".html", templateHTML);
	if(res.error().code()) {
		std::cout << res.error().string() << std::endl;
		return 1;
	}

	return 0;
}