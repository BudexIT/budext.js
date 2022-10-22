#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <hssml/files.hpp>

int main(int argc, char **argv) {
	std::string filename = "./index.scss";
	if(argc > 1) {
		filename = argv[1];
	}

	auto file = hssml::file::stringRead(filename);
	if(file.error().code()) {
		std::cout << file.error().string() << std::endl;
		return 1;
	}

	std::string input = file.unwrap();

	std::cout << input << std::endl;

	std::cout << std::endl << "> CHANGED TO <" << std::endl << std::endl;

	size_t index = 0;
	while(true) {
		index = input.find("build", index);
		if(index == std::string::npos) break;
		input.replace(index, 5, "destroy");
		index += 5;
	}
	
	std::cout << input << std::endl;

	auto res = hssml::file::stringWrite(filename + ".hssml_output", input);
	if(res.error().code()) {
		std::cout << file.error().string() << std::endl;
		return 1;
	}

	return 0;
}