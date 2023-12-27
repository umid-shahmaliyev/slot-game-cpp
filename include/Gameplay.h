//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "Matrix.h"
#include "GainResult.h"
#include "GainsCalculator.h"
#include "Spinner.h"
#include "Command.h"

using namespace std;

class Config;
class Spinner;
class GameplayAction;
class GainsCalculator;
class GainResult;

class Gameplay
{
public:
  explicit Gameplay(unique_ptr<Config>);
  virtual ~Gameplay() = default;

  ///

  size_t nrows() const { return nrows_; }
  size_t ncols() const { return ncols_; }

  const Config& config() const { return *up_config_; }

  ///

  virtual string version() const { return {}; }

  virtual void setActiveReelsGroup(size_t i) { active_reels_group_ = i; }
  virtual size_t activeReelsGroup() const { return active_reels_group_; }

  virtual void setGainResults(const vector<GainResult>& data) { gain_results_ = data; }
  virtual const vector<GainResult>& gainResults() const { return gain_results_; }

  virtual void setRoundGain(size_t gain) { round_gain_ = gain; }
  virtual size_t roundGain() const { return round_gain_; }

  virtual const Matrix<unsigned>& reels() const;
  virtual const Matrix<unsigned>& reels(size_t) const;

  virtual const Matrix<unsigned>& symbols() const { return symbols_; }
  virtual Matrix<unsigned>& symbols() { return symbols_; }

  virtual const Spinner& spinner() const { return *up_spinner_; }
  virtual Spinner& spinner() { return *up_spinner_; }

  virtual const GainsCalculator& gainsCalculator() const { return *up_gains_calculator_; }
  virtual GainsCalculator& gainsCalculator() { return *up_gains_calculator_; }

  ///

  virtual void bind(unsigned, const shared_ptr<GameplayAction>&);
  virtual void run(const Command&);

protected:
  const unique_ptr<Config> up_config_;
  const size_t nrows_;
  const size_t ncols_;

  unique_ptr<Spinner> up_spinner_;
  unique_ptr<GainsCalculator> up_gains_calculator_;
  Matrix<unsigned> symbols_;

  size_t active_reels_group_ = 0;
  size_t round_gain_ = 0;

  vector<GainResult> gain_results_;

protected:
  map<unsigned, vector<shared_ptr<GameplayAction>>> map_actions_;
};
