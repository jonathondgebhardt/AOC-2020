#include <day13/Utilities.ipp>

#include <algorithm>
#include <deque>
#include <future>
#include <thread>

// File auto-generated by StartNewDay

std::optional<util::day13::Time> getEarliestTime(const std::vector<util::day13::Bus>& buses,
                                                 util::day13::Time lowerBound,
                                                 util::day13::Time upperBound)
{
  std::optional<util::day13::Time> earlistTimeOpt;

  const auto& firstBus = buses.front();

  while(lowerBound != 0 && lowerBound < upperBound)
  {
    const auto firstMultiple = firstBus.busId * lowerBound;

    if(std::all_of(buses.begin(), buses.end(), [firstMultiple](const util::day13::Bus b) {
         return (firstMultiple + b.departureOffset) % b.busId == 0;
       }))
    {
      earlistTimeOpt = firstMultiple;
      break;
    }

    ++lowerBound;
  }

  return earlistTimeOpt;
}

int main(int argc, char* argv[])
{
  const auto inputFile = util::GetInputFile("day13.txt");
  const auto contents = util::Parse(inputFile);

  const auto departureTime = util::day13::GetEarliestTimeToDepart(contents);
  auto buses = util::day13::GetBuses(contents, departureTime);
  const auto& firstBus = buses.front();

  size_t multiplier = 0;
  util::day13::Time range = 100000000000000;

  std::optional<util::day13::Time> earliestTimeOpt;
  std::deque<std::future<std::optional<util::day13::Time>>> futures;

  while(true)
  {
    while(futures.size() < std::thread::hardware_concurrency())
    {
      const auto lowerBound = range * multiplier + 1;
      const auto upperBound = range * ++multiplier;

      std::cout << "Trying " << lowerBound << ", " << upperBound << "\n";

      futures.push_back(std::async(getEarliestTime, buses, lowerBound, upperBound));
    }

    while(futures.size() > 0)
    {
      earliestTimeOpt = futures.front().get();
      if(earliestTimeOpt.has_value())
      {
        futures.pop_front();
        std::cout << earliestTimeOpt.value() << "\n";
        break;
      }

      futures.pop_front();
    }

    if(earliestTimeOpt.has_value())
    {
      break;
    }
  }

  while(futures.size() > 0)
  {
    futures.front().wait();
    futures.pop_front();
  }

  return EXIT_SUCCESS;
}
