//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include "GameplayAction.h"

class DefaultActionSpin : public GameplayAction
{
public:
  void operator()(const Command&, Gameplay&) final;
};
