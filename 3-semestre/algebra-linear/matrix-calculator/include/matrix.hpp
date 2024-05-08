#pragma once

#include <array>
#include <cassert>
#include <cstdint>

namespace matx {

template <std::uint8_t R, std::uint8_t C, typename T>
using mat_arr = std::array<std::array<T, C>, R>;

template <std::uint8_t R, std::uint8_t C, typename T>
class Matrix {
public:
    Matrix() = default;
    Matrix(const mat_arr<R, C, T> &arr);
    Matrix(mat_arr<R, C, T> &&arr);

    mat_arr<R, C, T> arr() const;

private:
    mat_arr<R, C, T> _arr;
};

template <std::uint8_t R, std::uint8_t C, typename T>
Matrix<R, C, T>::Matrix(const mat_arr<R, C, T> &__arr) :
  _arr{__arr} {
    static_assert(_arr.size() == R * C);
    assert(_arr.size() == R * C);
}

template <std::uint8_t R, std::uint8_t C, typename T>
Matrix<R, C, T>::Matrix(mat_arr<R, C, T> &&__arr) :
  _arr{std::move(__arr)} {
    static_assert(_arr.size() == R * C);
    assert(_arr.size() == R * C);
}

template <std::uint8_t R, std::uint8_t C, typename T>
mat_arr<R, C, T> Matrix<R, C, T>::arr() const {
    return _arr;
}

} // namespace matx
