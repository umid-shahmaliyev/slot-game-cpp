//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>
#include <algorithm>

#include "Matrix.h"

using namespace std;

class Spinner
{
public:
  Spinner() = default;
  virtual ~Spinner() = default;

  virtual void spin(const Matrix<unsigned>&, Matrix<unsigned>&);
};
