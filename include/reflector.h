#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <array>
#include <string>

class Reflector {
public:
  // wiringStr: 26-letter string, must be self-inverse (like
  // "YRUHQSLDPXNGOKMIEBFZCWVJAT")
  Reflector(const std::string &wiringStr);

  int apply(int x) const;

private:
  std::array<int, 26> map_{};

  static int c2i(char c);
  static int mod26(int x);
};

#endif
