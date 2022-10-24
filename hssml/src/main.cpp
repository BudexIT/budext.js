#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <hssml/file.hpp>
#include <hssml/str.hpp>

#include <hssml/innards/index.html.h>

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

	std::string style = "";
	// std::string script = "";

	std::string output = hssml::str::replace(g_innard_index_html, "{body}", input);

	std::string aaaaaaa = "abc/xdefgh/ijkl/mnoper/st";

	auto x = hssml::str::split(aaaaaaa, "/");
	for(auto& v : x) {
		std::cout << "-- ENTRY - " << v << std::endl;
	}

	auto res = hssml::file::stringWrite(filename_out, output);
	if(res.error().code()) {
		std::cout << res.error().string() << std::endl;
		return 1;
	}

	return 0;
}