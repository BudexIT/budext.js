#include <main.hpp>
#include <fstream>

int main(int argc, char** argv) {
	FILE* file = nullptr;
	const char* filename = "./index.scss";
	if(argc > 1) {
		filename = argv[1];
	}
	file = fopen(filename, "r");
	if(file == nullptr) {
		printf("Error: couldn't find file %s!\n", filename);
	}

	
	return 0;
}