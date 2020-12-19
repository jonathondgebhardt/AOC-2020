#include <day16/Utilities.ipp>

#include <iomanip>

// File auto-generated by StartNewDay

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day16.txt");
  const auto contents = util::Parse(inputFile);

  const auto rules = util::day16::GetRules(contents);
  const auto nearbyTickets = util::day16::GetNearbyTickets(contents);

  util::day16::TicketMaster tm(rules, nearbyTickets);
  tm.removeInvalidTickets();
  tm.assignTicketFields();

  const auto myTicket = util::day16::GetYourTicket(contents);

  // 554 - too low
  std::cout << tm.sumDeparture(myTicket) << "\n";

  return EXIT_SUCCESS;
}
