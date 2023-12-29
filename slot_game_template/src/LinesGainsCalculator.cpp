//
// Created by Umid Shahmaliyev on 2023.
//
#include <exception>

#include "LinesGainsCalculator.h"

namespace sgt
{

LinesGainsCalculator::LinesGainsCalculator(
  size_t nrows, size_t ncols,
  const Matrix<size_t>& winlines,
  const map<unsigned, vector<size_t>>& paytable,
  unsigned wild_symbol,
  int direction)
  : GainsCalculator(nrows, ncols, winlines, paytable, wild_symbol)
  , direction_(direction)
{
}

size_t LinesGainsCalculator::calc(const Matrix<unsigned>& symbols)
{
  switch (direction_)
  {
    case -1: return calcFromLeft(symbols);
    default: throw std::runtime_error("not supported");
  }
}

size_t LinesGainsCalculator::calcFromLeft(const Matrix<unsigned>& symbols)
{
  if (symbols.ncols() != ncols_ || symbols.nrows() != nrows_)
    throw std::logic_error("invalid arguments");

  gain_ = 0;
  gain_results_.clear();

  for (unsigned row_wl = 0; row_wl < winlines_.nrows(); ++row_wl)
  {
    const auto winline = winlines_.row(row_wl);

    size_t c = 0;
    size_t num_w = 0;

    auto sym = symbols(winline.at(c), 0);

    if (sym == sym_wild_)
      ++num_w;

    while (++c < ncols_ && sym == sym_wild_)
    {
      sym = symbols(winline.at(c), c);

      if (sym == sym_wild_)
        ++num_w;
    }

    for (; c < ncols_; ++c)
    {
      const auto sym_c = symbols(winline.at(c), c);

      if (sym_c != sym && sym_c != sym_wild_)
        break;
    }

    const auto gain_s = getGainPaytable(sym, c);
    const auto gain_w = getGainPaytable(sym_wild_, num_w);
    const auto is_wild = gain_w > gain_s;

    sym = is_wild ? sym_wild_ : sym;

    const auto sym_count = is_wild ? num_w : c;
    const auto sym_gain = is_wild ? gain_w : gain_s;

    if (sym_gain > 0)
    {
      gain_ += sym_gain;
      gain_results_.emplace_back(sym, sym_count, sym_gain, row_wl);
    }
  }

  return gain_;
}

}
