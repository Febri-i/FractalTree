#pragma once
#include <iostream>

template <typename T> class vec2 {
public:
  // constructors
  vec2(T ix, T iy) : x(ix), y(iy) {}
  vec2(T ia) : x(ia), y(ia) {}
  vec2() : x(0), y(0) {}

  // variables
  T x, y;

  // operators
  template <typename Te> vec2<Te> operator+(const vec2<Te> &right) const {
    vec2<Te> temp(*this);
    temp += right;
    return temp;
  }
  template <typename Te> vec2<Te> operator-(const vec2<Te> &right) const {
    vec2<Te> temp(*this);
    temp -= right;
    return temp;
  }
  template <typename Te> vec2<Te> operator*(const vec2<Te> &right) const {
    vec2<Te> temp(*this);
    temp *= right;
    return temp;
  }
  template <typename Te> vec2<Te> operator/(const vec2<Te> &right) const {
    vec2<Te> temp(*this);
    temp /= right;
    return temp;
  }
  template <typename Te> vec2<Te> &operator+=(const vec2<Te> &right) {
    x += right.x;
    y += right.y;
    return *this;
  }
  template <typename Te> vec2<Te> &operator-=(const vec2<Te> &right) {
    x -= right.x;
    y -= right.y;
    return *this;
  }
  template <typename Te> vec2<Te> &operator*=(const vec2<Te> &right) {
    x *= right.x;
    y *= right.y;
    return *this;
  }
  template <typename Te> vec2<Te> &operator/=(const vec2<Te> &right) {
    if (right.x != 0 && right.y != 0) {
      x /= right.x;
      y /= right.y;
    }
    return *this;
  }

  template <typename Te> Te normalize() {
    if (x != 0 || y != 0) {
      T lenght = sqrt(pow(x, 2) + pow(y, 2));
      x /= lenght;
      y /= lenght;
    }
  }
  template <typename Te> void rotate(Te rotation) {
    T x_1 = x;
    x = (x * cos(rotation)) - (y * sin(rotation));
    y = (x_1 * sin(rotation)) + (y * cos(rotation));
  }
  template <typename Te> vec2<Te> rotated(Te rotation) const {
    return vec2((x * cos(rotation)) - (y * sin(rotation)),
                (x * sin(rotation)) + (y * cos(rotation)));
  }
  template <typename Te> vec2<Te> normalized() const {
    if (x != 0 || y != 0) {
      T lenght = sqrt(pow(x, 2) + pow(y, 2));
      return vec2<Te>(x / lenght, y / lenght);
    } else {
      return vec2<Te>(0, 0);
    }
  }
  template <typename Te> T absolute() const {
    return sqrt(pow(x, 2) + pow(y, 2));
  }
  template <typename Te>
  T dotProduct(const vec2<Te> &left, const vec2<Te> &right) {
    return left.x * right.x + left.y * right.y;
  }
};

// compile the following classes and function using the templates

// template <typename T>
// Compile for double
// template class vec2<double>;
// template std::ostream &operator<<(std::ostream &os, const vec2<double>
// &vec2); Compile for float template class vec2<float>; template std::ostream
// &operator<<(std::ostream &os, const vec2<float> &vec2);
