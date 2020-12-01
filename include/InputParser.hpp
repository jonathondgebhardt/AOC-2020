#pragma once

#include <Export.hpp>
#include <string>
#include <vector>

class EXPORT InputParser
{
public:
  static std::vector<std::string> Parse(const std::string& x);

private:
};