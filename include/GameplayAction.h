//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

class Gameplay;
class Command;

class GameplayAction
{
 public:
  virtual ~GameplayAction() = default;
  virtual void operator()(const Command&, Gameplay&) = 0;
};

