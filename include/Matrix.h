//
// Created by Umid Shahmaliyev on 2023.
//

#pragma once

#include <array>
#include <stdexcept>

template<class T>
class Matrix
{
 public:
  Matrix(size_t nrows, size_t ncols, const T& default_value = T())
	: nrows_(nrows), ncols_(ncols)
	, data_(nrows_ * ncols_, default_value)
  {
  }

  Matrix(size_t nrows, size_t ncols, const std::vector<T>& data)
	: nrows_(nrows), ncols_(ncols)
  {
	if (data.size() != nrows * ncols)
	{
	  throw std::runtime_error("Matrix::invalid arguments");
	}

	data_ = data;
  }

  Matrix(const Matrix<T>& other)
	: nrows_(other.nrows_), ncols_(other.ncols_)
	, data_(other.data_)
  {
  }

  size_t nrows() const { return nrows_; }
  size_t ncols() const { return ncols_; }
  size_t index(size_t row, size_t col) const { return row * ncols_ + col;}

  T& operator()(size_t index)
  {
	try { return data_.at(index); }
	catch(...) { throw std::out_of_range("Matrix::(index)"); }
  }

  const T& operator()(size_t index) const
  {
	try { return data_.at(index); }
	catch(...) { throw std::out_of_range("Matrix::(index)"); }
  }

  T& operator()(size_t row, size_t col)
  {
	try { return data_.at(index(row, col)); }
	catch(...) { throw std::out_of_range("Matrix::(row, col)"); }
  }

  const T& operator()(size_t row, size_t col) const
  {
	try { return data_.at(index(row, col)); }
	catch(...) { throw std::out_of_range("Matrix::(row, col)"); }
  }

  const std::vector<T>& data() const { return data_; }
  std::vector<T>& data() { return data_; }

  std::vector<T> row(size_t row) const
  {
	return
		std::vector<T>(
		  data_.begin() + index(row, 0),
		  data_.begin() + index(row, ncols_)
		);
  }

 private:
  const size_t nrows_;
  const size_t ncols_;
  std::vector<T> data_;
};
