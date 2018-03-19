#ifndef COLORS_COLOR_HPP
#define COLORS_COLOR_HPP

#include <initializer_list>
#include <stdexcept>
#include <regex>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

#include "numbers.hpp"

namespace color {

// Prototypes
class RGB;
class HSV;
class HSL;

class RGB {
private:
  unsigned char r;
  unsigned char g;
  unsigned char b;

public:

  RGB(const unsigned char& r, const unsigned char& g, const unsigned char& b):
    r(r), g(g), b(b) {}

  RGB(const std::initializer_list<unsigned char>& list) {
    if (list.size() != 3)
      throw std::logic_error("More than 3 channels");

    auto it = list.begin();
    r = *(it++);
    g = *(it++);
    b = *it;
  }

  RGB(const std::string& str) {
    // Including '#' character
    if (str.length() != 4 && str.length() != 7)
      throw std::logic_error("Malformed string");

    bool compact = false;
    if (str.length() == 4)
      compact = true;

    std::string r_comp = str.substr(1, compact? 1 : 2);
    std::string g_comp = str.substr(compact? 2 : 3, compact? 1 : 2);
    std::string b_comp = str.substr(compact? 3 : 5, compact? 1 : 2);

    if (compact) {
      r_comp += r_comp;
      g_comp += g_comp;
      b_comp += b_comp;
    }

    r = static_cast<unsigned char>(hex_to_int(r_comp));
    g = static_cast<unsigned char>(hex_to_int(g_comp));
    b = static_cast<unsigned char>(hex_to_int(b_comp));
  }

  explicit RGB(const HSV& hsv) {

  }

  friend std::ostream& operator<<(std::ostream& out, const RGB& c) {
    out << "r: " << static_cast<int>(c.r) << ", "
        << "g: " << static_cast<int>(c.g) << ", "
        << "b: " << static_cast<int>(c.b);

    return out;
  }

  unsigned char get_r() const { return r;  }
  unsigned char get_g() const { return g;  }
  unsigned char get_b() const { return b;  }

};

class HSV {
private:
  double hue;
  double saturation;
  double value;

public:

  HSV(const double& h, const double& s, const double& v): hue(h), saturation(s), value(v) {}

  explicit HSV(const RGB& rgb) {
    double r = rgb.get_r() / 255.0;
    double g = rgb.get_g() / 255.0;
    double b = rgb.get_b() / 255.0;

    double max = std::max(std::max(r, g), b);
    double min = std::min(std::min(r, g), b);
    double delta = max - min;

    hue = saturation = value = max;
  
    saturation = (max == 0.0 ? 0.0 : delta / max);
    if (max == min) {
      // achromatic
      hue = 0.0;
    } else {
      if (max == r) {
        hue = (g - b) / delta + (g < b ? 6.0 : 0.0);
      } else if (max == g) {
        hue = (b - r) / delta + 2.0;
      } else if (max == b) {
        hue = (r - g) / delta + 4.0;
      }

      hue /= 6.0;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const HSV& hsv) {
    out << "h: " << hsv.hue << ", "
        << "s: " << hsv.saturation << ", "
        << "v: " << hsv.value;
    return out;
  }

};




}

#endif //COLORS_COLOR_HPP
