//
// Created by Umid Shahmaliyev on 2023.
//

#include "Spinner.h"

#include "Utils.h"

void Spinner::spin(const Matrix<unsigned>& reels, Matrix<unsigned>& symbols)
{
  if (symbols.nrows() > reels.nrows() ||
      symbols.ncols() > reels.ncols())
  {
    throw std::runtime_error("invalid arguments");
  }

  for (unsigned c = 0; c < symbols.ncols(); ++c)
  {
    const auto rr = getRandom<size_t>(0, reels.nrows());

    for (unsigned r = 0; r < symbols.nrows(); ++r)
    {
      const auto row = (rr + r) % reels.nrows();
      const auto sym = reels(row, c);

      symbols(r, c) = sym;
    }
  }
}
