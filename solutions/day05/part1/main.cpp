#include <day05/Utilities.ipp>

#include <algorithm>

// File auto-generated by StartNewDay

int main(int argc, char* argv[])
{
  const auto fileName = util::GetInputFile("day05.txt");
  const auto contents = util::Parse(fileName);

  const auto seatIDs = util::day05::GetSeatIDs(contents);

  const auto it = std::max_element(seatIDs.begin(), seatIDs.end());
  std::cout << *it << "\n";

  return EXIT_SUCCESS;
}
