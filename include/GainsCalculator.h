//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>

#include "Matrix.h"
#include "GainResult.h"

using namespace std;

class GainsCalculator
{
 public:
  GainsCalculator(
	  size_t nrows, size_t ncols,
	  const Matrix<size_t>& winlines,
	  const map<unsigned, vector<size_t>>& paytable,
	  unsigned wild_symbol)
	  : nrows_(nrows), ncols_(ncols)
	  , winlines_(winlines)
	  , paytable_(paytable)
	  , sym_wild_(wild_symbol)
  {}

  virtual ~GainsCalculator() = default;

  const Matrix<size_t>& winlines() const { return winlines_; }

  const map<unsigned, vector<size_t>>& paytable() const { return paytable_; }

  const unsigned wildSymbol() const { return sym_wild_; }

  virtual const vector<GainResult>& gainResults() const { return gain_results_; }

  virtual unsigned gain() const { return gain_; }

  virtual size_t calc(const Matrix<unsigned>&) { return 0; };

  virtual size_t getGainPaytable(unsigned sym, size_t count) const
  {
	try { return 0 == count ? 0 : paytable_.at(sym).at(count - 1); }
	catch (...) { return 0; }
  }

 protected:
  const size_t nrows_;
  const size_t ncols_;
  const Matrix<size_t>& winlines_;
  const map<unsigned, vector<size_t>>& paytable_;
  const unsigned sym_wild_;

  size_t gain_ = 0;
  vector<GainResult> gain_results_;
};

