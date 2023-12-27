//
// Created by Umid Shahmaliyev on 2023.
//

#include "DefaultActionCalculateWins.h"

#include "Gameplay.h"

void DefaultActionCalculateWins::operator()(const Command&, Gameplay& gameplay)
{
  auto& calculator = gameplay.gainsCalculator();

  calculator.calc(gameplay.symbols());

  gameplay.setRoundGain(calculator.gain());
  gameplay.setGainResults(calculator.gainResults());
}
