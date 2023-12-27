//
// Created by Umid Shahmaliyev on 2023.
//

#include <memory>

#include "Gameplay.h"
#include "Config.h"
#include "Spinner.h"
#include "GameplayAction.h"
#include "GainsCalculator.h"

Gameplay::Gameplay(unique_ptr<Config> config)
  : up_config_(std::move(config))
  , nrows_(up_config_->nrows()), ncols_(up_config_->ncols())
  , symbols_(nrows_, ncols_)
  , up_spinner_(new Spinner())
  , up_gains_calculator_(new GainsCalculator(
	  nrows_, ncols_,
	  up_config_->winlines(),
	  up_config_->paytable(),
	  up_config_->wildSymbol()))
{
}

void Gameplay::bind(unsigned command, const shared_ptr<GameplayAction>& action)
{
  map_actions_[command].emplace_back(action);
}

void Gameplay::run(const Command& command)
{
  const auto& actions = map_actions_.at(command.id());

  for (auto& action : actions)
  {
	(*action)(command, *this);
  }
}

const Matrix<unsigned>& Gameplay::reels(size_t i) const
{
  return up_config_->reels(i);
}

const Matrix<unsigned>& Gameplay::reels() const
{
  return up_config_->reels(active_reels_group_);
}
