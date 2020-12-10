#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>

#include <algorithm>
#include <numeric>
#include <unordered_map>

namespace util
{
  namespace day09
  {
    // Numbers in this challenge are large.
    typedef int64_t NumberType;

    std::vector<NumberType> UTILITIES_EXPORT GetPreamble(const std::vector<NumberType>& x,
                                                         size_t length, size_t offset)
    {
      std::vector<NumberType> preamble;

      if(offset + length <= x.size())
      {
        const auto begin = x.begin() + offset;
        std::copy_n(begin, length, std::back_inserter(preamble));
      }

      return preamble;
    }

    bool UTILITIES_EXPORT GetCanFindSum(NumberType target, const std::vector<NumberType>& x)
    {
      std::unordered_map<NumberType, NumberType> numberNeeds;
      for(auto num : x)
      {
        const auto need = target - num;
        if(numberNeeds.find(need) != numberNeeds.end())
        {
          return true;
        }
        else
        {
          numberNeeds[num] = need;
        }
      }

      return false;
    }

    std::vector<NumberType> GetContiguousSum(NumberType target, const std::vector<NumberType>& x)
    {
      std::vector<NumberType> contiguousSum;

      // Only search from the beginning up to our target.
      const auto end = std::find(x.begin(), x.end(), target);
      if(end != x.end())
      {
        auto begin = x.begin();
        auto it = begin + 1;
        NumberType sum = 0;
        while(it != end - 1 && sum != target)
        {
          sum = std::reduce(begin, it, int64_t{0});
          if(sum < target)
          {
            it++;
          }
          else if(sum > target)
          {
            begin++;
            it = begin + 1;
          }
        }

        if(sum == target)
        {
          contiguousSum = {begin, it};
        }
      }

      return contiguousSum;
    }
  } // namespace day09
} // namespace util
