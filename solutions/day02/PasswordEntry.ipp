#pragma once

#include <Utilities.ipp>
#include <day02/Export.hpp>
#include <string>
#include <vector>

struct DAY02_EXPORT PasswordEntry
{
  enum TokenIndex
  {
    LengthRequirement = 0,
    Letter,
    Password
  };

  explicit PasswordEntry(const std::string& x)
  {
    // Example lines:
    // 1-3 a: abcde
    // 1-3 b: cdefg
    // 2-9 c: ccccccccc
    const auto tokens = util::Split(x);

    const auto lowerUpperBound = this->getLowerUpperBound(tokens[TokenIndex::LengthRequirement]);
    this->lowerBound = lowerUpperBound.first;
    this->upperBound = lowerUpperBound.second;

    this->letter = this->getLetter(tokens[TokenIndex::Letter]);
    this->password = tokens[TokenIndex::Password];
  }

  std::pair<int, int> getLowerUpperBound(const std::string& x) const
  {
    // I'm assuming that there will always be a hyphen.
    const auto hyphenIndex = x.find('-');
    const auto lowerBoundStr = x.substr(0, hyphenIndex);
    const auto upperBoundStr = x.substr(hyphenIndex + 1, x.length());

    // This could throw an exception but I'm choosing not to handle it.
    return std::make_pair(std::stoi(lowerBoundStr), std::stoi(upperBoundStr));
  }

  char getLetter(const std::string& x) const { return x[0]; }

  // Let solutions determine what it means to be valid.
  virtual bool isValid() const = 0;

  std::string password;
  int upperBound;
  int lowerBound;
  char letter;
};
