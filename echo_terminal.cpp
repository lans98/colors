#include "color.hpp"
#include "gradient.hpp"

#include <iostream>
#include <cstring>
#include <getopt.h>

static int verbose = 0;
static int printsteps = 0;

enum MODEL {
  RGB = 0x01,
  HSV = 0x02,
  HSL = 0x04
};

static option long_options[] = {
  {"model" , required_argument , 0           , 'm'},
  {"steps" , required_argument , 0           , 's'},
  {"begin" , required_argument , 0           , 'b'},
  {"end"   , required_argument , 0           , 'e'},
  {"print" , no_argument       , &printsteps , 1},
  {0       , 0                 , 0           , 0}
};

int main(int argc, char **argv) {
  char c;
  int option_index;
  int model_flag = RGB;
  int no_steps = 10;
  std::string colora, colorb;

  while ((c = getopt_long(argc, argv, "m:s:b:e:p" ,long_options, &option_index)) != -1)
    switch (c) {
      case 'm':
        model_flag &= 0;
        if (std::strcmp("RGB", optarg) == 0) 
          model_flag |= RGB;
        else if (std::strcmp("HSV", optarg) == 0)
          model_flag |= HSV;
        else if (std::strcmp("HSL", optarg) == 0)
          model_flag |= HSL;
        else 
          return 1;
        break;
      case 's':
        no_steps = std::stoi(optarg);
        if (no_steps <= 0) {
          std::cerr << "Incorrect number of steps\n";
          return 1;
        }
        break;
      case 'b':
        colora = optarg;
        break;
      case 'e':
        colorb = optarg;
        break;
      case 'p':
        printsteps = 1;
        break;
      default:
        break;
    }

  switch (model_flag) {
    case RGB:
      try {
        color::RGB a(colora);
        color::RGB b(colorb);
        auto stepsrgb = color::gradient_steps(a, b, no_steps);
        for (auto& x : stepsrgb)
          std::cout << "\x1b[38;2;"
                    << static_cast<int>(x.get_r()) << ";"
                    << static_cast<int>(x.get_g()) << ";"
                    << static_cast<int>(x.get_b()) << "m" 
                    << "█";

        std::cout<< "\n\x1b[m";
        if (!printsteps) return 0;
        for (auto& x : stepsrgb)
          std::cout << x.to_string() << '\n';
      } catch (std::exception e) {
        std::cerr << e.what() << '\n';
        return 1;
      }
      break;
    case HSV:
      try {
        color::HSV a((color::RGB(colora)));
        color::HSV b((color::RGB(colorb)));
        color::RGB tmp;
        auto stepshsv = color::gradient_steps(a, b, no_steps);
        for (auto& x : stepshsv) {
          tmp = static_cast<color::RGB>(x);
          std::cout << "\x1b[38;2;"
                    << static_cast<int>(tmp.get_r()) << ";"
                    << static_cast<int>(tmp.get_g()) << ";"
                    << static_cast<int>(tmp.get_b()) << "m" 
                    << "█";
        }

        std::cout<< "\n\x1b[m";
        if (!printsteps) return 0;
        for (auto& x : stepshsv) {
          tmp = static_cast<color::RGB>(x);
          std::cout << tmp.to_string() << '\n';
        }
      } catch (std::exception e) {
        std::cerr << e.what() << '\n';
        return 1;
      }
      break;
    case HSL:
      try {
        color::HSL a((color::RGB(colora)));
        color::HSL b((color::RGB(colorb)));
        color::RGB tmp;
        auto stepshsl = color::gradient_steps(a, b, no_steps);
        for (auto& x : stepshsl) {
          tmp = static_cast<color::RGB>(x);
          std::cout << "\x1b[38;2;"
                    << static_cast<int>(tmp.get_r()) << ";"
                    << static_cast<int>(tmp.get_g()) << ";"
                    << static_cast<int>(tmp.get_b()) << "m" 
                    << "█";
        }

        std::cout<< "\n\x1b[m";
        if (!printsteps) return 0;
        for (auto& x : stepshsl) {
          tmp = static_cast<color::RGB>(x);
          std::cout << tmp.to_string() << '\n';
        }
      } catch (std::exception e) {
        std::cerr << e.what() << '\n';
        return 1;
      }
      break;
  }

  return 0;
}
