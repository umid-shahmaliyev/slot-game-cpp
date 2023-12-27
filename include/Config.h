//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>
#include <map>

#include "Matrix.h"

using namespace std;

class Config
{
public:
	virtual ~Config() = default;

	virtual const size_t nrows() const { return num_rows; }

	virtual const size_t ncols() const { return num_cols; }

	virtual const vector<Matrix<unsigned>>& reelsGroup() const { return *up_reels_group; }

	virtual const Matrix<unsigned>& reels(size_t i) const { return up_reels_group->at(i); }

	virtual const Matrix<size_t>& winlines() const { return *up_winlines; }

	virtual const size_t numWinlines() const { return up_winlines->nrows(); }

	virtual const map<unsigned, vector<size_t>>& paytable() const { return *up_paytable; }

	virtual const unsigned wildSymbol() const { return sym_wild; }

protected:
	size_t num_rows;
	size_t num_cols;
	std::unique_ptr<vector<Matrix<unsigned>>> up_reels_group;
	std::unique_ptr<Matrix<size_t>> up_winlines;
	std::unique_ptr<map<unsigned, vector<size_t>>> up_paytable;
	unsigned sym_wild;
};
