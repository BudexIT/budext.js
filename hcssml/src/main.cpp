#include <main.hpp>
#include <fstream>

int main() {
		printf("eeeeeeeeeeeee\n");
	std::ifstream file;
		printf("eeeeeeeeeeeee\n");
	std::string filename = "./index.html";
		printf("eeeeeeeeeeeee\n");
	// if(argc > 1) {
	// 	filename = argv[1];
	// }
	file.open(filename);
		printf("eeeeeeeeeeeee\n");
	if(!file.is_open()) {
		printf("Error: couldn't find file %s!\n", filename.c_str());
	}

		printf("eeeeeeeeeeeee\n");

	
	return 0;
}