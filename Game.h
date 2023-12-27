//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <cassert>
#include <array>
#include <memory>

#include "Matrix.h"
#include "GameConfig.h"
#include "Gameplay.h"
#include "DefaultActionSpin.h"
#include "DefaultActionCalculateWins.h"
#include "LinesGainsCalculator.h"
#include "CustomActionCountSpins.h"

class Game : public Gameplay
{
public:
  enum Commands : unsigned
  {
    CMD_SPIN = 8U
  };

  explicit Game(unique_ptr<Config> game_config = std::make_unique<GameConfig>())
    : Gameplay(std::move(game_config))
  {
    up_gains_calculator_ = std::make_unique<LinesGainsCalculator>(
      nrows(), ncols(),
      config().winlines(),
      config().paytable(),
      config().wildSymbol()
    );

    bind(CMD_SPIN, make_shared<DefaultActionSpin>());
    bind(CMD_SPIN, make_shared<DefaultActionCalculateWins>());
	bind(CMD_SPIN, make_shared<CustomActionCountSpins>());
  }

  void bind(unsigned command, const shared_ptr<GameplayAction>& action) final
  {
    Gameplay::bind(command, action);
  }

  string version() const final { return "v1.0"; }

  size_t numSpins() const { return num_spins_; };
  void setNumSpins(size_t num) { num_spins_ = num; };

private:
  size_t num_spins_ = 0;
};