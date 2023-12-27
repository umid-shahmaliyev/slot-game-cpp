//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <stdexcept>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string_view>
#include <ranges>

namespace
{
std::random_device rd;
std::mt19937 rg_mt19937(rd());
}

template<class T>
T getRandom(const T min, const T max)
{
  return static_cast<T>(min + rg_mt19937.operator()() % (max - min));
}

template<class T>
void shuffle(T& v)
{
  std::shuffle(v.begin(), v.end(), rg_mt19937);
}

template<class T>
std::vector<T> generateSequence(std::vector<T> initializer_list)
{
  if (empty(initializer_list) || initializer_list.size() % 2 != 0)
    throw std::runtime_error("invalid arguments");

  std::vector<T> result;

  for (auto it = initializer_list.begin(); it < initializer_list.end();)
  {
    const auto sym = *(it++);
    const auto count = *(it++);
    result.insert(result.end(), count, sym);
  }

  return result;
}

template<class T>
Matrix<T> generateRandomReels(
  const std::vector<std::vector<T>>& sym_dist_by_reel,
  bool randomize = true)
{
  const auto num_reels = sym_dist_by_reel.size();

  if (!num_reels)
    throw std::runtime_error("invalid arguments");

  std::vector<std::vector<T>> reels_arr;

  for (size_t i = 0; i < num_reels; ++i)
  {
    auto reel_data = generateSequence<T>(sym_dist_by_reel.at(i));

    if(randomize)
      shuffle(reel_data);

    reels_arr.emplace_back(reel_data);

    if (i > 0 && (reels_arr.at(i).size() != reels_arr.at(i - 1).size()))
      throw std::runtime_error("invalid arguments");
  }

  const auto reels_length = reels_arr.at(0).size();

  Matrix<T> mat_reels(reels_length, num_reels);

  for (unsigned c = 0; c < num_reels; ++c)
  {
    const auto& reel_data = reels_arr.at(c);
    for (unsigned r = 0; r < reels_length; ++r)
    {
      const auto sym = reel_data.at(r);
      mat_reels(r, c) = sym;
    }
  }

  return mat_reels;
}

template<class T>
T stringToNumber(const std::string& str)
{
  static_assert(std::is_integral<T>::value, "integral type required");

  T ret;
  std::stringstream ss(str);
  ss >> ret;

  if ( std::to_string(ret) != str)
    throw std::invalid_argument("can't convert " + str);

  return ret;
}

template<class T = std::string>
std::vector<T> stringSplit(const std::string& str, const std::string& delimiter)
{
  auto split = str |
    std::ranges::views::split(delimiter) |
    std::ranges::views::transform([](auto&& str) {
      return std::string_view(&*str.begin(), std::ranges::distance(str));
    });

  std::vector<T> tokens;

  for (auto&& s : split)
  {
    // todo: convert s to type T
    tokens.emplace_back(s);
  }

  return tokens;
}

template <class T>
void printMat(const Matrix<T>& mat, std::streamsize w = 1)
{
  for (unsigned r = 0; r < mat.nrows(); ++r)
  {
    for (unsigned c = 0; c < mat.ncols(); ++c)
    {
      std::cout << std::setw(w) << mat(r, c) << " ";
    }
    std::cout << std::endl;
  }
}