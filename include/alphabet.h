#ifndef ALPHABET_H
#define ALPHABET_H

#include <string>

class Alphabet {
public:
  static int c2i(char c);
  static char i2c(int i);
  static bool isAZ(char c);
  static char toAZ(char c);
  static std::string sanitize(const std::string &s);
};

#endif
