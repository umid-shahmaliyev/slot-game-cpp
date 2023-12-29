//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <any>

using namespace std;

namespace sgt
{

class Command {
  using args_type = map<string, string>;

public:
  explicit Command(int id, std::initializer_list<string> args = {})
    : id_(id)
  {
    for (const auto& arg : args)
    {
      if (arg.empty())
        throw std::runtime_error("invalid arguments");

      args_.emplace(pair<string, string>{arg, {}});
    }
  }
  ~Command() = default;

  int id() const { return id_; }

  const args_type::const_iterator argsBegin() const { return args_.cbegin(); }
  args_type::iterator argsBegin() { return args_.begin(); }

  const args_type::const_iterator argsEnd() const { return args_.cend(); }
  args_type::iterator argsEnd() { return args_.end(); }

  const string& arg(const string& name) const { return args_.at(name); }
  string& arg(const string& name) { return args_.at(name); }

private:
  int id_;
  args_type args_;
};

}
