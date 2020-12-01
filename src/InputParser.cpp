#include <InputParser.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

std::vector<std::string> InputParser::Parse(const std::string& x)
{
  std::vector<std::string> contents;

  std::ifstream ifs(x);
  if(ifs.is_open())
  {

    const auto split = [](const std::string& x) -> std::vector<std::string> {
      std::stringstream ss(x);
      std::istream_iterator<std::string> begin(ss);
      std::istream_iterator<std::string> end;

      return {begin, end};
    };

    for(std::string line; std::getline(ifs, line);)
    {
      const auto tokens = split(line);
      std::copy(tokens.begin(), tokens.end(), std::back_inserter(contents));
    }

    std::copy(contents.begin(), contents.end(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
  }
  else
  {
    std::cerr << "Could not open '" << x << "'\n";
  }

  return contents;
}