#ifndef COLORS_GRADIENT_HPP
#define COLORS_GRADIENT_HPP 

#include <cmath>

#include "color.hpp"


namespace color {

double linear_interpolation(double a, double b, double step) {
  return (1 - step) * a + step * b;
}

RGB gradient(const RGB& p, const RGB& q) {
  double r, g, b;

  r = linear_interpolation(p.get_r(), q.get_r(), 0.5);
  g = linear_interpolation(p.get_g(), q.get_g(), 0.5);
  b = linear_interpolation(p.get_b(), q.get_b(), 0.5);

  r = std::round(r);
  g = std::round(g);
  b = std::round(b);

  return RGB(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b));
}

HSV gradient(const HSV& a, const HSV& b) {
  double h, s, v;

  h = linear_interpolation(a.get_h(), b.get_h(), 0.5);
  s = linear_interpolation(a.get_s(), b.get_s(), 0.5);
  v = linear_interpolation(a.get_v(), b.get_v(), 0.5);

  return HSV(h, s, v);
}

HSL gradient(const HSL& a, const HSL& b) {
  double h, s, l;

  h = linear_interpolation(a.get_h(), b.get_h(), 0.5);
  s = linear_interpolation(a.get_s(), b.get_s(), 0.5);
  l = linear_interpolation(a.get_l(), b.get_l(), 0.5);

  return HSL(h, s, l);
}


}

#endif //COLORS_GRADIENT_HPP
