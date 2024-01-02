//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>
#include <map>

#include "Matrix.h"

using namespace std;

namespace sgt
{

class Config
{
public:
  Config(
    size_t num_rows, size_t num_cols
    , unsigned sym_wild = 0)
      : num_rows_(num_rows)
      , num_cols_(num_cols)
      , sym_wild_(sym_wild)
  {}

  const size_t nrows() const { return num_rows_; }

  const size_t ncols() const { return num_cols_; }

  const unsigned wildSymbol() const { return sym_wild_; }

  const vector<Matrix<unsigned>>& reelsGroups() const { return *up_reels_groups_; }

  const Matrix<unsigned>& reels(size_t i) const { return up_reels_groups_->at(i); }

  const Matrix<size_t>& winlines() const { return *up_winlines_; }

  const size_t numWinlines() const { return up_winlines_->nrows(); }

  const map<unsigned, vector<size_t>>& paytable() const { return *up_paytable_; }

protected:
  void setupReels(vector<sgt::Matrix<unsigned>>&& reels_groups)
  {
    up_reels_groups_ = make_unique<vector<sgt::Matrix<unsigned>>>(reels_groups);
  }

  void setupWinlines(vector<size_t>&& winlines)
  {
    if (winlines.empty()
        || (winlines.size() % num_cols_)
        || count_if(winlines.begin(), winlines.end(), [=](size_t row){ return row >= num_rows_; }))
    {
      throw runtime_error("invalid argument");
    }

    up_winlines_ = make_unique<sgt::Matrix<size_t>>(winlines.size() / num_cols_, num_cols_, winlines);
  }

  void setupPaytable(map<unsigned, vector<size_t>>&& paytable)
  {
    up_paytable_ = make_unique<map<unsigned, vector<size_t>>>(paytable);
  }

protected:
  const size_t num_rows_;
  const size_t num_cols_;
  const unsigned sym_wild_;

  unique_ptr<vector<Matrix<unsigned>>> up_reels_groups_;
  unique_ptr<Matrix<size_t>> up_winlines_;
  unique_ptr<map<unsigned, vector<size_t>>> up_paytable_;
};

}
