#pragma once

#include "res.hpp"
#include "str.hpp"
#include "lexer.hpp"


std::string parseStyle(const std::vector<hssml::LexInfo>& info);

std::string parseBody(std::string& style, const std::vector<hssml::LexInfo>& info);