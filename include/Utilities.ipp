#pragma once

#include <Export.hpp>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
  UTILITIES_EXPORT std::string GetInputFile(const std::string& x);

  UTILITIES_EXPORT std::vector<std::string> Parse(const std::string& x);

  template <class T> UTILITIES_EXPORT std::optional<T> StringTo(const std::string& x)
  {
    std::optional<T> resultOpt;

    try
    {
      T result;
      std::stringstream ss(x);
      ss >> result;

      resultOpt = result;
    }
    catch(const std::exception& e)
    {
      std::cerr << "Could not convert " << x << " to requested type" << std::endl;
    }

    return resultOpt;
  }

  template <class T> UTILITIES_EXPORT std::vector<T> ContainerTo(const std::vector<std::string>& x)
  {
    std::vector<T> converted;
    for(const auto& item : x)
    {
      const auto itemOpt = StringTo<T>(item);
      if(!itemOpt.has_value())
      {
        std::cerr << "Could not convert '" << item << "' to requested type\n";
        break;
      }

      converted.push_back(itemOpt.value());
    }

    return converted;
  }

  UTILITIES_EXPORT std::vector<std::string> Split(const std::string& x);
} // namespace util
