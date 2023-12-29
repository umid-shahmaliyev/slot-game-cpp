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

  //  Ali Baba			50 coins	200 coins	1000 coins
  //  Pirate Captain	40 coins	150 coins	 800 coins
  //  Treasure Chest	30 coins	120 coins	 500 coins
  //  Sword				25 coins	100 coins	 400 coins
  //  Magic Lamp		20 coins	 80 coins	 300 coins
  //  Bag of Gold Coins	15 coins	 60 coins	 200 coins
  //  Jeweled Ring		10 coins	 40 coins	 150 coins
  //  Camel				 5 coins	 20 coins	 100 coins
  //  Map				 5 coins	 15 coins	  80 coins
  //  Ship				 3 coins	 10 coins	  50 coins
  //  Wild Symbol			   -	 		-	1500 coins
  //  Scatter/Bonus Symbol	   -		 2xTB	     10xTB

  enum Symbol : unsigned
  {
    // regular symbols
    SYM_1_SHIP 	 = 1U,
    SYM_2_MAP 	 = 2U,
    SYM_3_CAMEL  = 3U,
    SYM_4_RING 	 = 4U,
    SYM_5_BAG 	 = 5U,
    SYM_6_LAMP 	 = 6U,
    SYM_7_SWORD  = 7U,
    SYM_8_CHEST  = 8U,
    SYM_9_PIRATE = 9U,
    SYM_10_ALI 	 = 10U,
    SYM_WILD 	 = 11U,

    // special symbols
    SYM_SCATTER  = 12U,
    SYM_X2 		 = 13U,
    SYM_X3 		 = 14U
  };

  static constexpr int LINES_DIR_LEFT_TO_RIGHT = -1;

  explicit GameConfig(
    const size_t num_rows = 3, const size_t num_cols = 5
    , const unsigned sym_wild = 10)
    : sgt::Config(num_rows, num_cols, sym_wild)
  {
    setupReels({
      sgt::generateRandomReels<unsigned>({
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,88, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,12, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,85, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,15, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,79, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,21, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,75, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,25, SYM_10_ALI,0, SYM_WILD,10}}),
      sgt::generateRandomReels<unsigned>({
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,88, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,12, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,85, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,15, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,79, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,21, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,75, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,25, SYM_10_ALI,0, SYM_WILD,10}}, false),
      sgt::generateRandomReels<unsigned>({
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10},
        {SYM_1_SHIP,80, SYM_2_MAP,0, SYM_3_CAMEL,0, SYM_4_RING,0, SYM_5_BAG,0, SYM_6_LAMP,0, SYM_7_SWORD,0, SYM_8_CHEST,0, SYM_9_PIRATE,20, SYM_10_ALI,0, SYM_WILD,10}}, false)
     }
    );

    setupWinlines({
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
    });

    setupPaytable({
      {SYM_1_SHIP, 	 {0, 0, 0, 0, 0}},
      {SYM_2_MAP, 	 {0, 0, 0, 0, 0}},
      {SYM_3_CAMEL,  {0, 0, 0, 0, 0}},
      {SYM_4_RING, 	 {0, 0, 0, 0, 0}},
      {SYM_5_BAG, 	 {0, 0, 0, 0, 0}},
      {SYM_6_LAMP,   {0, 0, 0, 0, 0}},
      {SYM_7_SWORD,  {0, 0, 0, 0, 0}},
      {SYM_8_CHEST,  {0, 0, 0, 0, 0}},
      {SYM_9_PIRATE, {0, 0,  5, 10, 20}},
      {SYM_10_ALI, 	 {0, 0, 0, 0, 0}},
      {SYM_WILD,   	 {0, 0, 10, 25, 50}}
    });
  }
};
