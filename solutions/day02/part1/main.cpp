#include <day02/Utilities.ipp>

#include <algorithm>

struct PasswordEntry_Part1 : util::day02::PasswordEntry
{
  explicit PasswordEntry_Part1(const std::string& x) : PasswordEntry(x) {}

  bool isValid() const override
  {
    const auto letterCount = std::count(this->password.begin(), this->password.end(), this->letter);
    return letterCount >= lowerBound && letterCount <= upperBound;
  }
};

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day02.txt");
  const auto contents = util::Parse(inputFile);

  std::vector<PasswordEntry_Part1> passwordEntries;
  std::transform(contents.begin(), contents.end(), std::back_inserter(passwordEntries),
                 [](const std::string& x) { return PasswordEntry_Part1(x); });

  const auto count = std::count_if(passwordEntries.begin(), passwordEntries.end(),
                                   [](const PasswordEntry_Part1& x) { return x.isValid(); });
  std::cout << count << "\n";
}