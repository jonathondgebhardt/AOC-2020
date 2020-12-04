#pragma once

#include <Export.hpp>
#include <Utilities.ipp>

#include <string>
#include <vector>

namespace util
{
  namespace day03
  {
    UTILITIES_EXPORT size_t GetNumberOfTreesForSlope(const std::vector<std::string>& x,
                                                     std::pair<int, int> slope)
    {
      size_t numTrees = 0;
      int right = slope.first;
      int down = slope.second;

      // According to the prompt, we can skip the starting location at 0, 0.
      // I'm assuming that each row is exactly the same length.
      for(int i = down, j = right; i < x.size(); i += down, j = (j + right) % x[0].size())
      {
        // The pattern repeats infinitely horizontally so wrap around the side.
        if(x[i][j] == '#')
        {
          ++numTrees;
        }
      }

      return numTrees;
    }
  } // namespace day03
} // namespace util