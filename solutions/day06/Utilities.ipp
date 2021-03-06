#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>

namespace util
{
  namespace day06
  {
    UTILITIES_EXPORT std::vector<std::vector<std::string>>
    GetGroups(const std::vector<std::string>& x)
    {
      std::vector<std::vector<std::string>> groups;

      std::vector<std::string> groupLines;
      for(const auto& line : x)
      {
        if(!line.empty())
        {
          groupLines.push_back(line);
        }
        else
        {
          groups.push_back(groupLines);
          groupLines.clear();
        }
      }

      if(!groupLines.empty())
      {
        groups.push_back(groupLines);
        groupLines.clear();
      }

      return groups;
    }
  } // namespace day06
} // namespace util
