#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "res.hpp"

namespace hssml {
namespace file {

using ResString = Res<std::string>;

ResString stringRead(const std::string& filename);

ResNull stringWrite(const std::string& filename, const std::string& content);

}
}