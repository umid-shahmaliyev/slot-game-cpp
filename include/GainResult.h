//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>

using namespace std;

class GainResult
{
public:
  GainResult(
    unsigned sym,
    size_t cnt,
    size_t gain,
    size_t wl)
    : symbol(sym)
    , count(cnt)
    , gain(gain)
    , winline(wl)
  {}

  unsigned symbol;
  size_t count;
  size_t gain;
  size_t winline;
};
