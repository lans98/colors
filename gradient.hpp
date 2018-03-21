#ifndef COLORS_GRADIENT_HPP
#define COLORS_GRADIENT_HPP 

#include <cmath>
#include <vector>

#include "color.hpp"


namespace color {

double linear_interpolation(double a, double b, double step) {
  return (1 - step) * a + step * b;
}

RGB gradient(const RGB& p, const RGB& q, double step = 0.5) {
  double r, g, b;

  r = linear_interpolation(p.get_r(), q.get_r(), step);
  g = linear_interpolation(p.get_g(), q.get_g(), step);
  b = linear_interpolation(p.get_b(), q.get_b(), step);

  r = std::round(r);
  g = std::round(g);
  b = std::round(b);

  return RGB(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b));
}

std::vector<RGB> gradient_steps(const RGB& a, const RGB& b, int steps = 10) {
  if (steps <= 0) throw std::logic_error("Incorrect number of steps: " + std::to_string(steps));

  double weight = 1.0 / steps;
  double incweight = weight;
  std::vector<RGB> arr(steps);

  for (int ii = 0; ii != steps; ++ii) {
    arr[ii] = gradient(a, b, incweight);
    incweight += weight;
  }

  return arr;
}

HSV gradient(const HSV& a, const HSV& b, double step = 0.5) {
  double h, s, v;

  h = linear_interpolation(a.get_h(), b.get_h(), step);
  s = linear_interpolation(a.get_s(), b.get_s(), step);
  v = linear_interpolation(a.get_v(), b.get_v(), step);

  return HSV(h, s, v);
}

std::vector<HSV> gradient_steps(const HSV& a, const HSV& b, int steps = 10) {
  if (steps <= 0) throw std::logic_error("Incorrect number of steps: " + std::to_string(steps));

  double weight = 1.0 / steps;
  double incweight = weight;
  std::vector<HSV> arr(steps);

  for (int ii = 0; ii != steps; ++ii) {
    arr[ii] = gradient(a, b, incweight);
    incweight += weight;
  }

  return arr;
}

HSL gradient(const HSL& a, const HSL& b, double step = 0.5) {
  double h, s, l;

  h = linear_interpolation(a.get_h(), b.get_h(), step);
  s = linear_interpolation(a.get_s(), b.get_s(), step);
  l = linear_interpolation(a.get_l(), b.get_l(), step);

  return HSL(h, s, l);
}

std::vector<HSL> gradient_steps(const HSL& a, const HSL& b, int steps = 10) {
  if (steps <= 0) throw std::logic_error("Incorrect number of steps: " + std::to_string(steps));

  double weight = 1.0 / steps;
  double incweight = weight;
  std::vector<HSL> arr(steps);

  for (int ii = 0; ii != steps; ++ii) {
    arr[ii] = gradient(a, b, incweight);
    incweight += weight;
  }

  return arr;

}




}

#endif //COLORS_GRADIENT_HPP
