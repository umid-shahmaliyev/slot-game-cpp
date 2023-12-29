//
// Created by Umid Shahmaliyev on 2023.
//

#include "CustomActionCountSpins.h"

#include "Game.h"

void CustomActionCountSpins::operator()(const sgt::Command&, sgt::Gameplay& gameplay)
{
  auto& game = dynamic_cast<Game&>(gameplay);
  game.setNumSpins(game.numSpins() + 1);
}
