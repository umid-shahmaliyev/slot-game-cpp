//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include "GameplayAction.h"

class CustomActionCountSpins : public sgt::GameplayAction
{
public:
  void operator()(const sgt::Command&, sgt::Gameplay& gameplay) final;
};
