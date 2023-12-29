//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <stdexcept>
#include <memory>
#include <vector>
#include <map>

#include "Config.h"
#include "Matrix.h"
#include "Utils.h"

class GameConfig : public sgt::Config
{
public:
  enum Symbol : unsigned
  {
    SYM_1 = 1U,
    SYM_2 = 2U,
    SYM_3 = 3U,
    SYM_4 = 4U,
    SYM_5 = 5U,
    SYM_6 = 6U,
    SYM_7 = 7U,
    SYM_8 = 8U,
    SYM_9 = 9U,
    SYM_WILD = 10U
  };

  static constexpr int LINES_DIR_LEFT_TO_RIGHT = -1;

  GameConfig()
  {
    num_rows = 3;
    num_cols = 5;

    sym_wild = 10;

    constexpr auto num_winlines = 20;
    up_winlines = std::make_unique<sgt::Matrix<size_t>>(
      num_winlines, num_cols,
      std::vector<size_t>{
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,
        2, 2, 2, 2, 2,
        0, 1, 2, 1, 0,
        2, 1, 0, 1, 2,
        0, 0, 1, 0, 0,
        2, 2, 1, 2, 2,
        1, 2, 2, 2, 1,
        1, 0, 0, 0, 1,
        1, 0, 1, 0, 1,
        1, 2, 1, 2, 1,
        0, 1, 0, 1, 0,
        2, 1, 2, 1, 2,
        1, 1, 0, 1, 1,
        1, 1, 2, 1, 1,
        0, 2, 0, 2, 0,
        2, 0, 2, 0, 2,
        0, 1, 1, 1, 0,
        2, 1, 1, 1, 2,
        0, 2, 2, 2, 0
      }
    );

    up_reels_group = std::make_unique<vector<sgt::Matrix<unsigned>>>(
      vector<sgt::Matrix<unsigned>>{
        sgt::generateRandomReels<unsigned>({
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10},
          {SYM_1, 88, SYM_9, 12, SYM_WILD, 10},
          {SYM_1, 85, SYM_9, 15, SYM_WILD, 10},
          {SYM_1, 79, SYM_9, 21, SYM_WILD, 10},
          {SYM_1, 75, SYM_9, 25, SYM_WILD, 10}}),
        sgt::generateRandomReels<unsigned>({
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10},
          {SYM_1, 88, SYM_9, 12, SYM_WILD, 10},
          {SYM_1, 85, SYM_9, 15, SYM_WILD, 10},
          {SYM_1, 79, SYM_9, 21, SYM_WILD, 10},
          {SYM_1, 75, SYM_9, 25, SYM_WILD, 10}}, false),
        sgt::generateRandomReels<unsigned>({
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10},
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10},
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10},
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10},
          {SYM_1, 80, SYM_9, 20, SYM_WILD, 10}}, false)
      }
    );

    up_paytable = std::make_unique<map<unsigned, vector<size_t>>>(
      map<unsigned, vector<size_t>>{
        {   SYM_1, {0, 0,  0,  0,  0}},
        {   SYM_2, {0, 0,  0,  0,  0}},
        {   SYM_3, {0, 0,  0,  0,  0}},
        {   SYM_4, {0, 0,  0,  0,  0}},
        {   SYM_5, {0, 0,  0,  0,  0}},
        {   SYM_6, {0, 0,  0,  0,  0}},
        {   SYM_7, {0, 0,  0,  0,  0}},
        {   SYM_8, {0, 0,  0,  0,  0}},
        {   SYM_9, {0, 0,  5, 10, 20}},
        {SYM_WILD, {0, 0, 10, 25, 50}}
      }
    );
  }
};