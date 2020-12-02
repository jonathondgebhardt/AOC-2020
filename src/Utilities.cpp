#include <InputDirectoryConfig.ipp>
#include <Utilities.ipp>

#include <fstream>
#include <iostream>
#include <iterator>

std::string util::GetInputFile(const std::string& x)
{
  return config::GetInputFilePath() + "/" + x;
}

std::vector<std::string> util::Parse(const std::string& x)
{
  std::vector<std::string> contents;

  std::ifstream ifs(x);
  if(ifs.is_open())
  {
    for(std::string line; std::getline(ifs, line);)
    {
      // const auto tokens = util::Split(line);
      // std::copy(tokens.begin(), tokens.end(), std::back_inserter(contents));
      contents.push_back(line);
    }
  }
  else
  {
    std::cerr << "Could not open '" << x << "'\n";
  }

  return contents;
}

std::vector<std::string> util::Split(const std::string& x)
{
  std::stringstream ss(x);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;

  return {begin, end};
}
