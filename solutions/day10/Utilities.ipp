#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>

#include <algorithm>
#include <iterator>
#include <numeric>

namespace util
{
  namespace day10
  {
    struct UTILITIES_EXPORT JoltageCombination
    {
      void dump(std::ostream& os)
      {
        os << this->beginJoltage << "\n";

        os << "(";
        std::copy(this->joltages.begin(), this->joltages.end(),
                  std::ostream_iterator<size_t>(os, ", "));
        os << ")\n";

        os << this->endJoltage << "\n\n";
      }

      std::vector<size_t> joltages;
      size_t beginJoltage;
      size_t endJoltage;
    };

    std::vector<size_t> UTILITIES_EXPORT GetJoltages(const std::vector<std::string>& x)
    {
      std::vector<size_t> joltages;

      // According to the prompt, 0 is implied but not included in the input file.
      joltages.push_back(0);

      std::transform(x.begin(), x.end(), std::back_inserter(joltages),
                     [](std::string xStr) { return util::StringTo<size_t>(xStr).value(); });

      std::sort(joltages.begin(), joltages.end());

      // According to the prompt, (largest joltage + 3) is implied but not included in the input
      // file.
      if(!joltages.empty())
      {
        joltages.push_back(joltages.back() + 3);
      }

      return joltages;
    }

    std::vector<size_t> UTILITIES_EXPORT GetJoltageDeltas(const std::vector<size_t>& x)
    {
      std::vector<size_t> deltas;

      for(auto it = x.begin() + 1; it != x.end(); it++)
      {
        deltas.push_back(*it - *(it - 1));
      }

      return deltas;
    }

    bool UTILITIES_EXPORT GetIsValidAdapterSequence(const std::vector<size_t>& x)
    {
      const auto deltas = GetJoltageDeltas(x);
      return std::all_of(deltas.begin(), deltas.end(), [](size_t delta) { return delta <= 3; });
    }

    size_t UTILITIES_EXPORT GetValidCombinations(const JoltageCombination& jc)
    {
      size_t count = 0;

      // This is a feels bad. I decided to be lazy and get combinations by hand. This is very
      // specific to the problem that we're solving for day 10.
      const auto getCombinations =
          [](const JoltageCombination& jc) -> std::vector<std::vector<size_t>> {
        std::vector<std::vector<size_t>> combinations;

        if(jc.joltages.size() == 3)
        {
          combinations.push_back({jc.beginJoltage, jc.joltages[0], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[1], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[2], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[0], jc.joltages[1], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[0], jc.joltages[2], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[1], jc.joltages[2], jc.endJoltage});
          combinations.push_back(
              {jc.beginJoltage, jc.joltages[0], jc.joltages[1], jc.joltages[2], jc.endJoltage});
        }
        else if(jc.joltages.size() == 2)
        {
          combinations.push_back({jc.beginJoltage, jc.joltages[0], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[1], jc.endJoltage});
          combinations.push_back({jc.beginJoltage, jc.joltages[0], jc.joltages[1], jc.endJoltage});
        }

        return combinations;
      };

      const auto combinations = getCombinations(jc);
      return std::count_if(
          combinations.begin(), combinations.end(),
          [](const std::vector<size_t>& x) { return GetIsValidAdapterSequence(x); });
    }

  } // namespace day10
} // namespace util