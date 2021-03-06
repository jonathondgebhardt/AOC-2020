#include <day04/Utilities.ipp>

#include <cassert>
#include <iostream>

// File auto-generated by StartNewDay

struct Credential_Part2 : public util::day04::Credential
{
  explicit Credential_Part2(const std::vector<std::string>& x) : util::day04::Credential(x) {}

  bool isValid() override
  {
    if(util::day04::Credential::isValid())
    {
      const auto validBYR = util::day04::ValidateBirthYear(this->credentials["byr"]);
      const auto validIYR = util::day04::ValidateIssueYear(this->credentials["iyr"]);
      const auto validEYR = util::day04::ValidateExpirationYear(this->credentials["eyr"]);
      const auto validHGT = util::day04::ValidateHeight(this->credentials["hgt"]);
      const auto validHCL = util::day04::ValidateHairColor(this->credentials["hcl"]);
      const auto validECL = util::day04::ValidateEyeColor(this->credentials["ecl"]);
      const auto validPassportID = util::day04::ValidatePassportID(this->credentials["pid"]);

      return validBYR && validIYR && validEYR && validHGT && validHCL && validECL &&
             validPassportID;
    }

    return false;
  }
};

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day04.txt");
  const auto contents = util::Parse(inputFile);

  std::vector<std::string> credentialLines;
  std::vector<Credential_Part2> credentials;

  for(const auto& line : contents)
  {
    if(!line.empty())
    {
      credentialLines.push_back(line);
    }
    else
    {
      credentials.emplace_back(credentialLines);
      credentialLines.clear();
    }
  }

  if(!credentialLines.empty())
  {
    credentials.emplace_back(credentialLines);
    credentialLines.clear();
  }

  const auto validCredentials = std::count_if(credentials.begin(), credentials.end(),
                                              [](Credential_Part2& x) { return x.isValid(); });

  std::cout << validCredentials << "\n";

  return EXIT_SUCCESS;
}
