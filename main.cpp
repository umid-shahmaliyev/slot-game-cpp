//
// Created by Umid Shahmaliyev on 2023.
//

#include <iostream>
#include <random>
#include <map>
#include <cassert>
#include <array>

#include "Command.h"
#include "Utils.h"

#include "game_alis_pirate_plunder/Game.h"


void printResult(const Game& game, bool verbose = false);

constexpr unsigned CMD_EXIT = 1;
const map<unsigned, sgt::Command> MAP_COMMANDS {
  {Game::CMD_SPIN, sgt::Command{Game::CMD_SPIN}}
};

int main()
{
  Game game_instance;
  game_instance.setActiveReelsGroup(2);

  unsigned input = 0;
  while (cin >> input && input != CMD_EXIT)
  {
    try
    {
      auto cmd{MAP_COMMANDS.at(input)};

      for (auto it = cmd.argsBegin(); it != cmd.argsEnd(); ++it)
      {
        cin >> it->second;
      }

      game_instance.run(cmd);
      printResult(game_instance, true);
    }
    catch (...)
    {
      break;
    }
  }

  exit(input == CMD_EXIT ? 0 : 132);
}

void printResult(const Game& game, bool verbose)
{
  std::cout << "####################" << std::endl;
  std::cout << "# round: " << game.numSpins() << std::endl;
  std::cout << "# balance: " << 1000000 << std::endl;
  std::cout << "# gain: " << game.roundGain() << std::endl;

  sgt::Matrix<std::string> mat_print_symbols(game.symbols().nrows(), game.symbols().ncols());
  for (size_t i = 0; i < game.symbols().data().size(); ++i)
  {
    const auto sym = game.symbols()(i);
    auto& print_sym = mat_print_symbols(i);
    switch (sym)
    {
    case GameConfig::SYM_WILD:
      print_sym = "W"; break;
    case GameConfig::SYM_SCATTER:
      print_sym = "S"; break;
    case GameConfig::SYM_X2:
      print_sym = "2X"; break;
    case GameConfig::SYM_X3:
      print_sym = "3X"; break;
    default:
      print_sym = to_string(sym);
    }
  }

  std::cout << "# screen: " << std::endl;
  printMat(mat_print_symbols, 2);
  std::cout << std::endl;

  if (verbose && game.roundGain())
  {
    std::cout << "### ROUND DETAILS ###" << std::endl;
    std::cout << std::endl;

    const auto& winlines = game.config().winlines();
    const auto& gain_results = game.gainResults();
    for (const auto& gain_result : gain_results)
    {
      std::cout << "# symbol: S" << gain_result.symbol << std::endl;
      std::cout << "# count: " << gain_result.count << std::endl;
      std::cout << "# gain: " << gain_result.gain << std::endl;

      sgt::Matrix<unsigned> mask(game.symbols().nrows(), game.symbols().ncols(), 0);

      for (size_t col = 0; col < gain_result.count; ++col)
      {
        const auto row = winlines(gain_result.winline, col);
        mask(row, col) = 1;
      }

      std::cout << "# mask: " << std::endl;
      printMat(mask);
      std::cout << std::endl;
    }
  }
  std::cout << "####################" << std::endl;
}
