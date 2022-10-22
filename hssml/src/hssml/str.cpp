#include <hssml/str.hpp>

namespace hssml {
namespace str {

std::string replace(std::string input, std::string_view to_replace, std::string_view replace_with) {
	size_t index = 0;
	while(true) {
		index = input.find(to_replace, index);
		if (index == std::string::npos) break;
		input.replace(index, to_replace.size(), replace_with);
		index += to_replace.size();
	}
	return input;
}

}
}