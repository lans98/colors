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
  RGB() = default;
  RGB(const RGB& rgb): r(rgb.r), g(rgb.g), b(rgb.b) {}

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

  explicit RGB(const HSV& hsv);
  explicit RGB(const HSL& hsl);


  friend std::ostream& operator<<(std::ostream& out, const RGB& c) {
    out << "r: " << static_cast<int>(c.r) << ", "
        << "g: " << static_cast<int>(c.g) << ", "
        << "b: " << static_cast<int>(c.b);

    return out;
  }

  std::string to_string() {
    std::string rgb_str("#");
    rgb_str += int_to_hex(r);
    rgb_str += int_to_hex(g);
    rgb_str += int_to_hex(b);
    return rgb_str;
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
  HSV() = default;
  HSV(const HSV& hsv): hue(hsv.hue), saturation(hsv.saturation), value(hsv.value) {}

  HSV(const double& h, const double& s, const double& v): hue(h), saturation(s), value(v) {}

  explicit HSV(const RGB& rgb);
  explicit HSV(const HSL& hsl);

  friend std::ostream& operator<<(std::ostream& out, const HSV& hsv) {
    out << "h: " << hsv.hue << ", "
        << "s: " << hsv.saturation << ", "
        << "v: " << hsv.value;
    return out;
  }

  double get_h() const { return hue; }
  double get_s() const { return saturation; }
  double get_v() const { return value; }
};

class HSL {
private:
  double hue;
  double saturation;
  double lightness;

public:
  HSL() = default;
  HSL(const HSL& hsl): hue(hsl.hue), saturation(hsl.saturation), lightness(hsl.lightness) {}

  HSL(const double& h, const double& s, const double& l): hue(h), saturation(s), lightness(l) {}

  explicit HSL(const RGB& rgb);
  explicit HSL(const HSV& hsv);

  friend std::ostream& operator<<(std::ostream& out, const HSL& hsl) {
    out << "h: " << hsl.hue << ", "
        << "s: " << hsl.saturation << ", " 
        << "l: " << hsl.lightness;

    return out;
  }

  double get_h() const { return hue; }
  double get_s() const { return saturation; }
  double get_l() const { return lightness; }
};

RGB::RGB(const HSV& hsv) {
  double tr, tg, tb;

  double i = std::floor(hsv.get_h() * 6);
  double f = hsv.get_h() * 6 - i;
  double p = hsv.get_v() * (1 - hsv.get_s());
  double q = hsv.get_v() * (1 - f * hsv.get_s());
  double t = hsv.get_v() * (1 - (1 - f) * hsv.get_s());

  int mod = static_cast<int>(i) % 6;
  switch (mod) {
    case 0: tr = hsv.get_v(); tg = t; tb = p; break;
    case 1: tr = q; tg = hsv.get_v(); tb = p; break;
    case 2: tr = p; tg = hsv.get_v(); tb = t; break;
    case 3: tr = p; tg = q; tb = hsv.get_v(); break;
    case 4: tr = t; tg = p; tb = hsv.get_v(); break;
    case 5: tr = hsv.get_v(); tg = p; tb = q; break;
  }

  tr *= 255; tr = std::round(tr);
  tg *= 255; tg = std::round(tg);
  tb *= 255; tb = std::round(tb);

  r = static_cast<unsigned char>(tr);
  g = static_cast<unsigned char>(tg);
  b = static_cast<unsigned char>(tb);
}

RGB::RGB(const HSL& hsl) {
  double tr, tg, tb;

  if (hsl.get_s() == 0.0) {
    tr = tg = tb = hsl.get_l();
  } else {

    auto hue2rgb = [](double p, double q, double t){
      if (t < 0) t += 1;
      if (t > 1) t -= 1;
      if (t < 1/6.0) return p + (q - p) * 6 * t;
      if (t < 1/2.0) return q;
      if (t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
      return p;
    };

    double q = hsl.get_l() ? hsl.get_l() * (1 + hsl.get_s()) : hsl.get_l() + hsl.get_s() - hsl.get_l() * hsl.get_s();
    double p = 2 * hsl.get_l() * q;

    tr = hue2rgb(p, q, hsl.get_h() + 1/3.0);
    tg = hue2rgb(p, q, hsl.get_h());
    tb = hue2rgb(p, q, hsl.get_h() - 1/3.0);
  }


  tr *= 255; tr = std::round(tr);
  tg *= 255; tg = std::round(tg);
  tb *= 255; tb = std::round(tb);

  r = static_cast<unsigned char>(tr);
  g = static_cast<unsigned char>(tg);
  b = static_cast<unsigned char>(tb);
}

HSV::HSV(const RGB& rgb) {
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

HSV::HSV(const HSL& hsl) {
  RGB temp(hsl);
  HSV frgb(temp);

  hue = frgb.get_h();
  saturation = frgb.get_s();
  value = frgb.get_v();
}

HSL::HSL(const RGB& rgb) {
  double r = rgb.get_r() / 255.0;
  double g = rgb.get_g() / 255.0;
  double b = rgb.get_b() / 255.0;

  double max = std::max(std::max(r, g), b);
  double min = std::min(std::min(r, g), b);

  hue = saturation = lightness = (max + min) / 2;

  if (max == min) {
    // achromatic
    hue = saturation = 0.0;
  } else {
    double delta = max - min;
    saturation = lightness > 0.5 ? delta / (2 - max - min) : delta / (max + min);

    if (max == r) {
      hue = (g - b) / delta + (g < b? 6 : 0);
    } else if (max == g) {
      hue = (b - r) / delta + 2; 
    } else if (max == b) {
      hue = (r - g) / delta + 4;
    }

    hue /= 6.0;
  }
}

HSL::HSL(const HSV& hsv) {
  RGB temp(hsv);
  HSL frgb(temp);

  hue = frgb.get_h();
  saturation = frgb.get_s();
  lightness = frgb.get_l();
}

}

#endif //COLORS_COLOR_HPP
