#include "color.hpp"
#include "gradient.hpp"

#include <iostream>

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cout << "Need 2 colors in RGB and the number of steps\n";
    return 1;
  }

  std::string frgb(argv[1]);
  std::string srgb(argv[2]);

  try {
    color::RGB argb(frgb);
    color::RGB brgb(srgb);

    int steps = std::stoi(argv[3]);
    if (steps <= 0) return 1;

    auto stepsrgb = color::gradient_steps(argb, brgb, steps);
    for (auto& x : stepsrgb)
      std::cout << "\x1b[38;2;"
                << static_cast<int>(x.get_r()) << ";"
                << static_cast<int>(x.get_g()) << ";"
                << static_cast<int>(x.get_b()) << "m" 
                << "█";

    std::cout<< "\n\x1b[m";
    for (auto& x : stepsrgb)
      std::cout << x.to_string() << '\n';

  } catch (std::exception e) {
    std::cout << e.what() << '\n';
    return 1;
  }


  return 0;
}
