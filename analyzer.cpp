//
// Created by Umid Shahmaliyev on 2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <cassert>
#include <array>
#include <memory>
#include <chrono>

#include "Matrix.h"
#include "Utils.h"

#include "game_alis_pirate_plunder/Game.h"

using namespace chrono;

int main()
{
  const size_t NUM_SIMS = 10000000;
  const sgt::Command CMD_SPIN(Game::CMD_SPIN, {"bet"});

  Game game_instance;

  map<unsigned, size_t> map_sym_gains;
  map<unsigned, size_t> map_sym_counts;
  map<std::pair<unsigned, size_t>, size_t> map_lines_oak_cnt;

  size_t total_gain = 0;
  size_t total_win_counts = 0;

  time_point<system_clock> start_time = system_clock::now();
  std::time_t tt = system_clock::to_time_t(start_time);

  std::cout <<  "# simulation start: " <<  ctime(&tt);
  std::cout <<  "# total simulations: " << NUM_SIMS << std::endl;
  for (size_t s = 0; s < NUM_SIMS; ++s)
  {
    game_instance.run(CMD_SPIN);

    total_gain += game_instance.roundGain();

    const auto& gain_results = game_instance.gainResults();

    total_win_counts += gain_results.size();

    for (const auto& line_result : gain_results)
    {
      map_sym_gains[line_result.symbol] += line_result.gain;
      ++map_sym_counts[line_result.symbol];
      ++map_lines_oak_cnt[{line_result.symbol, line_result.count}];
    }

    // show progress
    static unsigned progress = 0;
    if (!(s % (NUM_SIMS / 100)))
    {
      if (!(++progress % 20)) { std::cout <<  ": " << progress << "%" << std::endl; }
      else { std::cout <<  "."; }
    }
  }

  auto diff_t = system_clock::now() - start_time;
  auto h = duration_cast<hours>(diff_t);
  auto m = duration_cast<minutes>(diff_t) % 60;
  auto s = duration_cast<seconds>(diff_t) % 60;

  std::cout
      << "# simulation end: " << setfill('0')
      << std::setw(2) << h.count() << ':'
      << std::setw(2) << m.count() << ':'
      << std::setw(2) << s.count() <<  endl;

  std::cout <<  "# total gain " << total_gain << std::endl;


  for (const auto& pair : map_sym_gains)
  {
    const auto sym = pair.first;
    const auto gains = pair.second;
    std::cout << "sym " << sym << ", gains "<< gains << " (" << gains * 100.0 / total_gain << "%)" << std::endl;
  }

  for (const auto& pair : map_sym_counts)
  {
    const auto sym = pair.first;
    const auto count = pair.second;
    std::cout << "sym " << sym << ", count "<< count << " (" << count * 100.0 / total_win_counts << "%)" << std::endl;
  }

  for (const auto& pair : map_lines_oak_cnt)
  {
    const auto symbol = pair.first.first ;
    const auto oak = pair.first.second;

    const auto count = pair.second;
    std::cout << "symbol " << symbol << ", oak " << oak << " - " << count << " ("<< count * 100.0 / (NUM_SIMS * 20.0) << "%)" << std::endl;
  }

  return 0;
}
