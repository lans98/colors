#include <iostream>

#include "color.hpp"
#include "gradient.hpp"

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

  color::RGB color6(color5);
  std::cout << color6 << std::endl;


  // Testing gradient
  color::RGB colora_rgb("#4100e5");
  color::RGB colorb_rgb("#0300bf");
  color::HSV colora_hsv(colora_rgb);
  color::HSV colorb_hsv(colorb_rgb);
  color::HSL colora_hsl(colora_rgb);
  color::HSL colorb_hsl(colorb_rgb);

  std::cout << "RGB Testing gradient: \n";
  std::cout << colora_rgb << '\n';
  std::cout << colorb_rgb << '\n';

  std::cout << "HSV Testing gradient: \n";
  std::cout << colora_hsv << '\n';
  std::cout << colorb_hsv << '\n';

  std::cout << "HSL Testing gradient: \n";
  std::cout << colora_hsl << '\n';
  std::cout << colorb_hsl << '\n';

  auto gradient_rgb = color::gradient(colora_rgb, colorb_rgb);
  std::cout << "gradient rgb: " << gradient_rgb << std::endl;
  auto gradient_hsv = color::gradient(colora_hsv, colorb_hsv);
  std::cout << "gradient hsv: " << gradient_hsv << std::endl;
  auto gradient_hsl = color::gradient(colora_hsl, colorb_hsl);
  std::cout << "gradient hsl: " << gradient_hsl << std::endl;

  // Testing gradient steps
  auto steps_rgb = color::gradient_steps(colora_rgb, colorb_rgb);
  std::cout << "Gradient steps with RGB: \n";
  for (auto& x : steps_rgb)
    std::cout << x << '\n';

  auto steps_hsv = color::gradient_steps(colora_hsv, colorb_hsv);
  std::cout << "Gradient steps with HSV: \n";
  for (auto& x : steps_hsv)
    std::cout << x << '\n';

  auto steps_hsl = color::gradient_steps(colora_hsl, colorb_hsl);
  std::cout << "Gradient steps with HSL: \n";
  for (auto& x : steps_hsl)
    std::cout << x << '\n';

  return 0;
}
