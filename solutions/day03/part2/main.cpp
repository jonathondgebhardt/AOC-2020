#include <day03/Utilities.ipp>

#include <algorithm>
#include <iomanip>
#include <numeric>

int main(int argc, char* argv[])
{
  const auto fileName = util::GetInputFile("day03.txt");
  const auto contents = util::Parse(fileName);

  // Right 1, down 1.
  // Right 3, down 1. (This is the slope you already checked.)
  // Right 5, down 1.
  // Right 7, down 1.
  // Right 1, down 2.
  std::vector<std::pair<int, int>> slopes{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

  // Find the product of encountered trees for all of the slopes.
  const auto product =
      std::transform_reduce(slopes.begin(), slopes.end(), 1.0, std::multiplies<size_t>(),
                            [&contents](std::pair<int, int> x) {
                              return util::day03::GetNumberOfTreesForSlope(contents, x);
                            });

  std::cout << std::fixed << product << "\n";
}