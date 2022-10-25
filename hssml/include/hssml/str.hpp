#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace hssml {
namespace str {

std::string replace(std::string input, const std::string& to_replace, const std::string& replace_with);
std::vector<std::string> split(const std::string& input, const std::string& where);

}
}