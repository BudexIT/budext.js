#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <hssml/files.hpp>

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

	std::string HTML = "<>";


	return 0;
}