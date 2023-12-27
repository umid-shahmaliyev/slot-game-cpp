//
// Created by Umid Shahmaliyev on 2023.
//

#include <iostream>
#include <random>
#include <map>
#include <cassert>
#include <array>

#include "Game.h"
#include "Command.h"
#include "Utils.h"

void printResult(const Game& game, bool verbose = false);

constexpr unsigned CMD_EXIT = 1;
const map<unsigned, Command> MAP_COMMANDS {
  {Game::CMD_SPIN, Command{Game::CMD_SPIN}}
};

int main()
{
  Game game_instance;

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
  std::cout << "# balance: " << 1000000 << std::endl;
  std::cout << "# gain: " << game.roundGain() << std::endl;
  std::cout << "# screen: " << std::endl;
  printMat(game.symbols(), 2);
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

			Matrix<unsigned> mask(game.symbols().nrows(), game.symbols().ncols(), 0);

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
