#include <hssml/files.hpp>

namespace hssml {
namespace file {

ResString stringRead(const std::string& filename) {
	FILE *file = fopen(filename.c_str(), "r");
	if(file == nullptr) {
		return ResString(Err(1, "file not found"));
	}

	fseek(file, 0, SEEK_END);
	int fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);

	std::string text(fileLength, '\0');
	fread(&text[0], 1, fileLength, file);

	fclose(file);

	return ResString(std::move(text));
}

ResNull stringWrite(const std::string& filename, const std::string& content) {
	FILE *file = fopen(filename.c_str(), "w");
	if(file == nullptr) {
		return ResNull(Err(1, "can't create/open file to write"));
	}

	size_t writesize = fwrite(&content[0], 1, content.size(), file);

	fclose(file);

	if(writesize != content.size()) {
		return ResNull(Err(2, "can't write everything to the file"));
	}

	return ResNull(Err(0));
}

}
}