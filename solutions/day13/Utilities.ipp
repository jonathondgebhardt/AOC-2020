#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>

#include <algorithm>

namespace util
{
  namespace day13
  {
    typedef uint64_t Time;

    struct UTILITIES_EXPORT Bus
    {
      bool operator<(Bus& other) { return this->departureTime < other.departureTime; }

      void dump(std::ostream& os)
      {
        os << "Bus Id: " << this->busId << ", closest time: " << this->departureTime
           << ", offset: " << this->departureOffset << "\n";
      }

      size_t busId;
      Time departureTime;
      Time departureOffset;
    };

    Time UTILITIES_EXPORT GetEarliestTimeToDepart(const std::vector<std::string>& x)
    {
      if(!x.empty())
      {
        const auto first = x.front();
        const auto opt = util::StringTo<Time>(first);
        if(opt.has_value())
        {
          return opt.value();
        }
      }

      return 0;
    }

    std::vector<Bus> GetBuses(const std::vector<std::string>& x, Time departureTime)
    {
      std::vector<Bus> buses;

      if(x.size() > 1)
      {
        const auto tokens = util::Split(x[1], ',');
        for(size_t i = 0; i < tokens.size(); ++i)
        {
          const auto busIdOpt = util::StringTo<Time>(tokens[i]);
          if(busIdOpt.has_value() && busIdOpt.value() != 0)
          {
            const auto time = busIdOpt.value();

            Bus b;
            b.busId = time;

            auto earliestTime = (departureTime / time) * time + time;
            b.departureTime = earliestTime;

            b.departureOffset = i;

            buses.push_back(b);
          }
        }
      }

      return buses;
    }

    Time GetLowestTimeToWait(std::vector<Bus> buses, Time departureTime)
    {
      std::sort(buses.begin(), buses.end());
      const auto firstBus = buses.front();

      return firstBus.busId * (firstBus.departureTime - departureTime);
    }
  } // namespace day13
} // namespace util
