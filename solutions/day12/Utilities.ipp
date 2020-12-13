#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <memory>
#include <type_traits>

namespace util
{
  namespace day12
  {
    enum UTILITIES_EXPORT Action
    {
      Action_North = 0,
      Action_South,
      Action_East,
      Action_West,
      Action_Left,
      Action_Right,
      Action_Forward
    };

    enum UTILITIES_EXPORT Direction : size_t
    {
      Direction_East = 0,
      Direction_South,
      Direction_West,
      Direction_North
    };

    struct UTILITIES_EXPORT NavigationInstruction
    {
      Action action;
      size_t value;
    };

    typedef std::pair<int, int> Coordinate;

    struct NavigationStrategy
    {
      virtual void doNavigationInstruction(NavigationInstruction ni, Coordinate& location,
                                           Direction& heading) = 0;

    protected:
      NavigationStrategy(){};
    };

    template <typename T, typename Enable = void> struct Ship
    {
    };

    template <typename T>
    struct Ship<T, typename std::enable_if<std::is_base_of<NavigationStrategy, T>::value>::type>
    {
      void doNavigationInstruction(NavigationInstruction ni)
      {
        this->instructionsReceived++;
        this->navStrategy->doNavigationInstruction(ni, this->c, this->d);
      }

      size_t getManhattanDistance() const
      {
        return std::abs(this->c.first) + std::abs(this->c.second);
      }

      void dump(std::ostream& os)
      {
        os << "Instruction " << this->instructionsReceived << ":\n";
        os << "\tAbs Location: " << std::abs(this->c.first) << ", " << std::abs(this->c.second)
           << "\n";

        os << "\tHeading: ";
        switch(this->d)
        {
        case Direction::Direction_East:
          os << "East\n";
          break;
        case Direction::Direction_South:
          os << "South\n";
          break;
        case Direction::Direction_West:
          os << "West\n";
          break;
        case Direction::Direction_North:
          os << "North\n";
          break;
        default:
          break;
        }

        os << "\tMD: " << this->getManhattanDistance() << "\n";

        os << "\n";
      }

      // Use indirection to avoid maintaining an instance of an abstract type.
      std::unique_ptr<T> navStrategy{std::make_unique<T>()};

      Direction d{Direction::Direction_East};
      Coordinate c{std::make_pair(0, 0)};
      size_t instructionsReceived{0};
    };

    struct NavigationStrategy_Part1 : public NavigationStrategy
    {
      void doNavigationInstruction(NavigationInstruction ni, Coordinate& location,
                                   Direction& heading) override
      {
        switch(ni.action)
        {
        case Action::Action_North:
          location.second += ni.value;
          break;
        case Action::Action_South:
          location.second -= ni.value;
          break;
        case Action::Action_East:
          location.first += ni.value;
          break;
        case Action::Action_West:
          location.first -= ni.value;
          break;
        case Action::Action_Left:
        case Action::Action_Right:
          this->turnDirection(ni, heading);
          break;
        case Action::Action_Forward:
          switch(heading)
          {
          case Direction::Direction_East:
            location.first += ni.value;
            break;
          case Direction::Direction_South:
            location.second -= ni.value;
            break;
          case Direction::Direction_West:
            location.first -= ni.value;
            break;
          case Direction::Direction_North:
            location.second += ni.value;
            break;
          default:
            std::cerr << "Cannot move in unknown direction\n";
            break;
          }
          break;
        default:
          std::cerr << "Cannot do unknown action\n";
          break;
        }
      }

      void turnDirection(NavigationInstruction ni, Direction& heading)
      {
        assert(ni.value >= 0 && ni.value <= 270);
        assert(ni.value % 90 == 0);

        // There's probably a smarter way to do this. If I always turn right, I can add the
        // number of turns to my direction, rolling over to the beginning if necessary.
        size_t numTurns = ni.value / 90;
        if(ni.action == Action::Action_Left && numTurns != 2)
        {
          numTurns = numTurns == 1 ? 3 : 1;
        }

        heading = static_cast<Direction>((heading + numTurns) % 4);
      }
    };

    struct NavigationStrategy_Part2 : public NavigationStrategy
    {
      NavigationStrategy_Part2() : NavigationStrategy() {}
      explicit NavigationStrategy_Part2(Coordinate waypoint) : waypoint(waypoint) {}

      void doNavigationInstruction(NavigationInstruction ni, Coordinate& location, Direction&)
      {
        switch(ni.action)
        {
        case Action::Action_North:
          this->waypoint.second += ni.value;
          break;
        case Action::Action_South:
          this->waypoint.second -= ni.value;
          break;
        case Action::Action_East:
          this->waypoint.first += ni.value;
          break;
        case Action::Action_West:
          this->waypoint.first -= ni.value;
          break;
        case Action::Action_Left:
        case Action::Action_Right:
          this->rotateWaypoint(ni);
          break;
        case Action::Action_Forward:
          location.first += ni.value * this->waypoint.first;
          location.second += ni.value * this->waypoint.second;
          break;
        default:
          std::cerr << "Cannot do unknown action\n";
          break;
        }
      }

      void rotateWaypoint(NavigationInstruction ni)
      {
        assert(ni.value >= 0 && ni.value <= 270);
        assert(ni.value % 90 == 0);

        const auto oldX = this->waypoint.first;
        const auto oldY = this->waypoint.second;
        if((ni.action == Action::Action_Right && ni.value == 90) ||
           (ni.action == Action::Action_Left && ni.value == 270))
        {
          this->waypoint.first = oldY;
          this->waypoint.second = -oldX;
        }
        else if((ni.action == Action::Action_Right || ni.action == Action::Action_Left) &&
                ni.value == 180)
        {
          this->waypoint.first = -oldX;
          this->waypoint.second = -oldY;
        }
        else if((ni.action == Action::Action_Right && ni.value == 270) ||
                (ni.action == Action::Action_Left && ni.value == 90))
        {
          this->waypoint.first = -oldY;
          this->waypoint.second = oldX;
        }
      }

      Coordinate waypoint{10, 1};
    };

    std::vector<NavigationInstruction> GetNavigationInstructions(const std::vector<std::string>& x)
    {
      std::vector<NavigationInstruction> nis;

      const auto stringToNavigationInstruction = [](const std::string& str) {
        NavigationInstruction ni;

        const auto actionStr = str.substr(0, 1);
        if(actionStr == "N")
        {
          ni.action = Action::Action_North;
        }
        else if(actionStr == "S")
        {
          ni.action = Action::Action_South;
        }
        else if(actionStr == "E")
        {
          ni.action = Action::Action_East;
        }
        else if(actionStr == "W")
        {
          ni.action = Action::Action_West;
        }
        else if(actionStr == "L")
        {
          ni.action = Action::Action_Left;
        }
        else if(actionStr == "R")
        {
          ni.action = Action::Action_Right;
        }
        else if(actionStr == "F")
        {
          ni.action = Action::Action_Forward;
        }
        else
        {
          std::cerr << "Cannot convert string '" << actionStr << "' to action\n";
        }

        const auto valueStr = str.substr(1);
        const auto valueOpt = util::StringTo<size_t>(valueStr);
        if(valueOpt.has_value())
        {
          ni.value = valueOpt.value();
        }
        else
        {
          std::cerr << "Cannot convert value '" << valueStr << "' to value";
        }

        return ni;
      };

      std::transform(x.begin(), x.end(), std::back_inserter(nis), stringToNavigationInstruction);

      return nis;
    }
  } // namespace day12
} // namespace util
