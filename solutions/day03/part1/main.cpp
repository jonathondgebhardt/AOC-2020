#include <day03/Utilities.ipp>

int main(int argc, char* argv[])
{
  const auto fileName = util::GetInputFile("day03.txt");
  const auto contents = util::Parse(fileName);

  constexpr int right = 3;
  constexpr int down = 1;

  std::cout << util::day03::GetNumberOfTreesForSlope(contents, std::make_pair(right, down)) << "\n";
}