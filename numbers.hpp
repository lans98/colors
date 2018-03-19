#ifndef COLORS_NUMBERS_HPP
#define COLORS_NUMBERS_HPP

#include <string>
#include <stdexcept>

namespace color {

std::string convert_to_base10(std::string number, long base_number) {
  long inumber = 0;
  long tmpbase = 1;
  char digit   = 0;

  while (!number.empty()) {
    digit = number.back();

    if (digit >= 'A' && digit <= 'F')
      digit -= 55;
    else if (digit >= 'a' && digit <= 'f')
      digit -= 87;
    else if (digit >= '0' && digit <= '9')
      digit -= 48;
    else
      throw std::logic_error("Unrecognized digit");

    if (digit >= base_number)
      throw std::logic_error("Bad number");

    inumber += digit * tmpbase;
    tmpbase *= base_number;

    number.pop_back();
  }

  return std::to_string(inumber);
}

std::string convert_from_base10(std::string number, long base_number) {
  long inumber = std::stol(number);
  long tmpbase = 1;
  long digit   = 0;

  number = "";
  while (inumber != 0) {
    digit    = inumber % base_number;
    inumber /= base_number;

    if (digit >= 10 && digit <= 15)
      digit += 55;
    else if (digit >= 0 && digit <= 9)
      digit += 48;
    else
      throw std::logic_error("Unrecognized digit");

    if (digit >= base_number)
      throw std::logic_error("Bad number");

    number.push_back(static_cast<char>(digit));
  }

  return std::string(number.rbegin(), number.rend());
}

std::string convert_from_to(std::string number, long basef, long baset) {
  if (basef == 1 || baset == 1)
    throw std::logic_error("Error base 1 doesn't exist");

  if (basef == baset)
    return number;

  if (basef == 10)
    return convert_from_base10(number, baset);

  if (baset == 10)
    return convert_to_base10(number, basef);

  std::string cnumber;
  cnumber = convert_to_base10(number, basef);
  cnumber = convert_from_base10(cnumber, baset);

  return cnumber;
}

int hex_to_int(std::string hex) {
  std::string number = convert_from_to(hex, 16, 10);
  return std::stoi(number);
}

std::string int_to_hex(int a) {
  std::string number = convert_from_to(std::to_string(a), 10, 16);
  return number;
}

}

#endif //COLORS_NUMBERS_HPP
