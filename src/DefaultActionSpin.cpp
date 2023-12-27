//
// Created by Umid Shahmaliyev on 2023.
//

#include "DefaultActionSpin.h"

#include "Gameplay.h"

void DefaultActionSpin::operator()(const Command&, Gameplay& gameplay)
{
  gameplay.spinner().spin(gameplay.reels(), gameplay.symbols());
}
