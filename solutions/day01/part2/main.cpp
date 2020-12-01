#include <Utilities.ipp>
#include <algorithm>
#include <optional>

struct Answer
{
  int first;
  int second;
  int third;
  int product;
};

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day01.txt");
  const auto numbers = util::ContainerTo<int>(util::Parse(inputFile));

  std::optional<Answer> aOpt;
  for(auto firstIt = numbers.begin(); firstIt != numbers.end(); firstIt++)
  {
    for(auto secondIt = firstIt + 1; secondIt != numbers.end(); secondIt++)
    {
      auto thirdIt = std::find_if(secondIt, numbers.end(), [firstIt, secondIt](auto other) {
        return *firstIt + *secondIt + other == 2020;
      });
      if(thirdIt != numbers.end())
      {
        Answer a;
        a.first = *firstIt;
        a.second = *secondIt;
        a.third = *thirdIt;
        a.product = a.first * a.second * a.third;

        aOpt = a;
        break;
      }
    }
  }

  if(!aOpt.has_value())
  {
    std::cerr << "Found no two numbers that sum to 2020\n";
    return EXIT_FAILURE;
  }

  const auto a = aOpt.value();
  std::cout << a.first << " + " << a.second << " + " << a.third << " = "
            << a.first + a.second + a.third << "\n";
  std::cout << a.first << " * " << a.second << " * " << a.third << " = " << a.product << "\n";

  return EXIT_SUCCESS;
}