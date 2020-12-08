#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>
#include <cassert>

namespace util
{
  namespace day05
  {
    size_t BinarySpacePartition(const std::string& x, int ub, char front)
    {
      auto lb = 0;
      auto range = ub + 1;

      for(const auto letter : x)
      {
        range /= 2;
        letter == front ? ub -= range : lb += range;
      }

      assert(ub == lb);

      return ub;
    }

    UTILITIES_EXPORT size_t GetRowNumber(const std::string& x)
    {
      return BinarySpacePartition(x, 127, 'F');
    }

    UTILITIES_EXPORT size_t GetSeatNumber(const std::string& x)
    {
      return BinarySpacePartition(x, 7, 'L');
    }

    UTILITIES_EXPORT size_t GetSeatID(size_t rowNumber, size_t seatNumber)
    {
      return rowNumber * 8 + seatNumber;
    }
  } // namespace day05
} // namespace util