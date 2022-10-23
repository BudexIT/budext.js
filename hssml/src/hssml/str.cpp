#include <hssml/str.hpp>

namespace hssml {
namespace str {

std::string replace(std::string input, std::string_view to_replace, std::string_view replace_with) {
	size_t index = 0;
	while(true) {
		index = input.find(to_replace, index);
		if(index == std::string::npos) break;
		
		input.replace(index, to_replace.size(), replace_with);
		index += to_replace.size();
	}
	return input;
}

std::vector<std::string> split(const std::string& input, std::string_view where) {
	std::vector<std::string> returned;

	size_t index = 0;
	while(true) {
		size_t prevIndex = index;
		index = input.find(where, index);
		if(index == std::string::npos) {
			index = prevIndex;
			break;
		}

		std::string thisPart = input.substr(prevIndex, index-prevIndex);
		returned.push_back(thisPart);
	
		index += where.size();
	}
	returned.push_back(input.substr(index, input.size()-index));
	
	return std::move(returned);
}

}
}