#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace hssml {
namespace str {

std::string replace(std::string input, std::string_view to_replace, std::string_view replace_with);

}
}