#include <Utilities.ipp>
#include <algorithm>
#include <optional>

struct Answer
{
  int first;
  int second;
  int product;
};

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day01.txt");
  const auto numbers = util::ContainerTo<int>(util::Parse(inputFile));

  std::optional<Answer> aOpt;

  for(auto it = numbers.begin(); it != numbers.end(); it++)
  {
    auto otherIt =
        std::find_if(it, numbers.end(), [it](auto other) { return *it + other == 2020; });
    if(otherIt != numbers.end())
    {
      Answer a;
      a.first = *it;
      a.second = *otherIt;
      a.product = a.first * a.second;

      aOpt = a;
      break;
    }
  }

  if(!aOpt.has_value())
  {
    std::cerr << "Found no two numbers that sum to 2020\n";
    return EXIT_FAILURE;
  }

  const auto a = aOpt.value();
  std::cout << a.first << " + " << a.second << " = " << a.first + a.second << "\n";
  std::cout << a.first << " * " << a.second << " = " << a.product << "\n";

  return EXIT_SUCCESS;
}