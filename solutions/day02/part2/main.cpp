#include <Utilities.ipp>
#include <algorithm>
#include <day02/PasswordEntry.ipp>

struct PasswordEntry_Part2 : PasswordEntry
{
  explicit PasswordEntry_Part2(const std::string& x) : PasswordEntry(x) {}

  bool isValid() const override
  {
    //     // Note: non-zero based indexing
    //     // "1-3 a: abcde" is valid: position 1 contains a and position 3 does not.
    //     // "1-3 b: cdefg" is invalid: neither position 1 nor position 3 contains b.
    const auto lowerBoundCharacter = this->password[lowerBound - 1];
    const auto upperBoundCharacter = this->password[upperBound - 1];

    const auto lowerBoundContainsCharacter = lowerBoundCharacter == letter;
    const auto upperBoundContainsCharacter = upperBoundCharacter == letter;

    return (lowerBoundContainsCharacter && !upperBoundContainsCharacter) ||
           (!lowerBoundContainsCharacter && upperBoundContainsCharacter);
  }
};

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day02.txt");
  const auto contents = util::Parse(inputFile);

  std::vector<PasswordEntry_Part2> passwordEntries;
  std::transform(contents.begin(), contents.end(), std::back_inserter(passwordEntries),
                 [](const std::string& x) { return PasswordEntry_Part2(x); });

  const auto count = std::count_if(passwordEntries.begin(), passwordEntries.end(),
                                   [](const PasswordEntry_Part2& x) { return x.isValid(); });
  std::cout << count << "\n";
}