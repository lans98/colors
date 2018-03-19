#include <iostream>

#include "color.hpp"

int main() {
  color::RGB color1("#231d2f");
  std::cout << color1 << std::endl;

  color::RGB color2 { 21, 255, 12 };
  std::cout << color2 << std::endl;

  color::RGB color3("#a3b");
  std::cout << color3 << std::endl;

  color::RGB color4(12, 23, 255);
  std::cout << color4 << std::endl;

  color::HSV color5(color1);
  std::cout << color5 << std::endl;

  return 0;
}
