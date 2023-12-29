//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <map>

#include "Matrix.h"
#include "GainsCalculator.h"

using namespace std;

namespace sgt
{

class LinesGainsCalculator : public GainsCalculator
{
public:
  LinesGainsCalculator(
    size_t, size_t,
    const Matrix<size_t>&,
    const map<unsigned, vector<size_t>>&,
    unsigned,
    int);

  size_t calc(const Matrix<unsigned>&) final;

private:
  size_t calcFromLeft(const Matrix<unsigned>&);

private:
  const int direction_;
};

}
