#pragma once

// File auto-generated by StartNewDay

#include <Export.hpp>
#include <Utilities.ipp>

#include <algorithm>
#include <cassert>
#include <iterator>

namespace util
{
  namespace day11
  {
    struct UTILITIES_EXPORT OccupiedSeatAdapter
    {
      virtual bool getIsSeatOccupied(size_t row, size_t col) const
      {
        assert(row >= 0 && row < this->seats.size());
        const auto rowOfSeats = this->seats[row];

        assert(col >= 0 && col < rowOfSeats.size());
        const auto seat = rowOfSeats[col];
        return seat == '#';
      }

      virtual std::optional<bool> checkUp(int row, int col) const
      {
        std::cout << ":(\n";
        return std::nullopt;
      }

      virtual std::optional<bool> checkUpDiagonalLeft(int row, int col) const
      {
        return std::nullopt;
      }

      virtual std::optional<bool> checkUpDiagonalRight(int row, int col) const
      {
        return std::nullopt;
      }

      virtual std::optional<bool> checkLeft(int row, int col) const { return std::nullopt; }

      virtual std::optional<bool> checkRight(int row, int col) const { return std::nullopt; }

      virtual std::optional<bool> checkDown(int row, int col) const { return std::nullopt; }

      virtual std::optional<bool> checkDownDiagonalLeft(int row, int col) const
      {
        return std::nullopt;
      }

      virtual std::optional<bool> checkDownDiagonalRight(int row, int col) const
      {
        return std::nullopt;
      }

      size_t getOccupiedSeats(size_t row, size_t col) const
      {
        size_t occupiedSeats = 0;

        const auto upOpt = this->checkUp(row, col);
        if(upOpt.has_value() && upOpt.value())
        {
          ++occupiedSeats;
        }

        const auto upDLOpt = this->checkUpDiagonalLeft(row, col);
        if(upDLOpt.has_value() && upDLOpt.value())
        {
          ++occupiedSeats;
        }

        const auto upDROpt = this->checkUpDiagonalRight(row, col);
        if(upDROpt.has_value() && upDROpt.value())
        {
          ++occupiedSeats;
        }

        const auto leftOpt = this->checkLeft(row, col);
        if(leftOpt.has_value() && leftOpt.value())
        {
          ++occupiedSeats;
        }

        const auto rightOpt = this->checkRight(row, col);
        if(rightOpt.has_value() && rightOpt.value())
        {
          ++occupiedSeats;
        }

        const auto downOpt = this->checkDown(row, col);
        if(downOpt.has_value() && downOpt.value())
        {
          ++occupiedSeats;
        }

        const auto downDLOpt = this->checkDownDiagonalLeft(row, col);
        if(downDLOpt.has_value() && downDLOpt.value())
        {
          ++occupiedSeats;
        }

        const auto downDROpt = this->checkDownDiagonalRight(row, col);
        if(downDROpt.has_value() && downDROpt.value())
        {
          ++occupiedSeats;
        }

        return occupiedSeats;
      }

      std::vector<std::vector<char>> seats;
    };

    struct UTILITIES_EXPORT WaitingArea
    {
      explicit WaitingArea(const std::vector<std::string>& seats)
      {
        for(const auto& row : seats)
        {
          std::vector<char> rowC;
          std::copy(row.begin(), row.end(), std::back_inserter(rowC));

          this->seats.push_back(rowC);
        }
      }

      void dump(std::ostream& os) const
      {
        os << "Round " << this->rounds << " (" << this->getOccupiedSeats() << "):\n";
        for(const auto& row : this->seats)
        {
          std::copy(row.begin(), row.end(), std::ostream_iterator<char>(os, " "));
          os << "\n";
        }

        // os << "\n";
        // os << "Seats changed this round:\n";
        // for(const auto p : this->changedSeats)
        // {
        //   os << "(" << p.first << ", " << p.second << ")\n";
        // }

        os << "\n";
      }

      void invertSeat(size_t row, size_t col, const OccupiedSeatAdapter& osa)
      {
        if(this->seats[row][col] != '.')
        {
          this->seats[row][col] = osa.getIsSeatOccupied(row, col) ? 'L' : '#';
        }
      }

      virtual bool getShouldSit(int row, int col, const OccupiedSeatAdapter& osa) const
      {
        // If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes
        // occupied.
        return !osa.getIsSeatOccupied(row, col) && osa.getOccupiedSeats(row, col) == 0;
      }

      virtual bool getShouldStand(int row, int col, const OccupiedSeatAdapter& osa) const
      {
        // If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the
        // seat becomes empty.
        return osa.getIsSeatOccupied(row, col) && osa.getOccupiedSeats(row, col) >= 4;
      }

      template <typename T> void startNewRound(T osa)
      {
        osa.seats = this->seats;

        this->changedSeats.clear();
        this->seatsChanged = false;
        this->rounds++;

        for(size_t i = 0; i < this->seats.size(); ++i)
        {
          for(size_t j = 0; j < this->seats[i].size(); ++j)
          {
            // Skip empty spots.
            if(this->seats[i][j] == '.')
            {
              continue;
            }

            if(this->getShouldSit(i, j, osa) || this->getShouldStand(i, j, osa))
            {
              this->invertSeat(i, j, osa);
              this->seatsChanged = true;

              this->changedSeats.push_back(std::make_pair(i, j));
            }
          }
        }
      }

      size_t getOccupiedSeats() const
      {
        size_t occupiedSeats = 0;

        for(const auto& row : this->seats)
        {
          occupiedSeats += std::count(row.begin(), row.end(), '#');
        }

        return occupiedSeats;
      }

      bool getSeatsChanged() const { return this->seatsChanged; }

      size_t getRounds() const { return this->rounds; }

      std::vector<std::vector<char>> seats;
      std::vector<std::pair<size_t, size_t>> changedSeats;
      bool seatsChanged{false};
      size_t rounds{0};
    };

    // struct UTILITIES_EXPORT WaitingArea_part2 : public WaitingArea
    // {
    //   explicit WaitingArea_part2(const std::vector<std::string>& x) : WaitingArea(x) {}

    //   size_t getOccupiedDirectionalSeats(int row, int col) const
    //   {
    //     size_t occupiedSeats = 0;

    //     // The prompt says the waiting room is a perfect square but we'll check the requested
    //     row's
    //     // length just to be safe.
    //     assert(row < this->previousSeats.size() && col < this->previousSeats[row].size());

    //     // North row
    //     if(row - 1 >= 0)
    //     {
    //       // Straight up
    //       for(int i = row - 1; i >= 0; --i)
    //       {
    //         if(this->getIsSeatOccupied(i, col))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }

    //       // Diagonal left
    //       for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
    //       {
    //         if(this->getIsSeatOccupied(i, j))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }

    //       // Diagonal right
    //       for(int i = row - 1, j = col + 1; i >= 0 && j < this->previousSeats[i].size(); --i,
    //       ++j)
    //       {
    //         if(this->getIsSeatOccupied(i, j))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }
    //     }

    //     // Middle row
    //     if(row >= 0)
    //     {
    //       // Left
    //       for(int i = col - 1; i >= 0; --i)
    //       {
    //         if(this->getIsSeatOccupied(row, i))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }

    //       // Right
    //       for(int i = col + 1; i < this->previousSeats[i].size(); ++i)
    //       {
    //         if(this->getIsSeatOccupied(row, i))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }
    //     }

    //     // South row
    //     if(row + 1 < this->previousSeats.size())
    //     {
    //       // Straight down
    //       for(int i = row + 1; i < this->previousSeats.size(); ++i)
    //       {
    //         if(this->getIsSeatOccupied(i, col))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }

    //       // Diagonal left
    //       for(int i = row + 1, j = col - 1; i < this->previousSeats.size() && j >= 0; ++i, --j)
    //       {
    //         if(this->getIsSeatOccupied(i, j))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }

    //       // Diagonal right
    //       for(int i = row + 1, j = col + 1;
    //           i < this->previousSeats.size() && j < this->previousSeats[i].size(); ++i, ++j)
    //       {
    //         if(this->getIsSeatOccupied(i, j))
    //         {
    //           ++occupiedSeats;
    //           break;
    //         }
    //       }
    //     }

    //     return occupiedSeats;
    //   }

    //   bool getShouldSit(int row, int col) const override
    //   {
    //     // If a seat is empty (L) and there are no occupied seats adjacent to it, the seat
    //     becomes
    //     // occupied.
    //     return !this->getIsSeatOccupied(row, col) &&
    //            this->getOccupiedDirectionalSeats(row, col) == 0;
    //   }

    //   bool getShouldStand(int row, int col) const override
    //   {
    //     // Also, people seem to be more tolerant than you expected: it now takes five or more
    //     // visible occupied seats for an occupied seat to become empty (rather than four or more
    //     // from the previous rules).
    //     return this->getIsSeatOccupied(row, col) &&
    //            this->getOccupiedDirectionalSeats(row, col) >= 5;
    //   }
    // };

  } // namespace day11
} // namespace util
