//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include "GameplayAction.h"

namespace sgt
{

class DefaultActionCalculateWins : public GameplayAction
{
public:
  void operator()(const Command&, Gameplay&) final;
};

}
