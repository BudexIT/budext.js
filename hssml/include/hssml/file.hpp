#pragma once

#include "res.hpp"

#include <string>

namespace hssml {
namespace file {

using ResString = Res<std::string>;

ResString stringRead(const std::string& filename);

ResNull stringWrite(const std::string& filename, const std::string& content);

}
}