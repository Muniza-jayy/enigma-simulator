#include "../include/reflector.h"
#include <cctype>
using namespace std;

int Reflector::mod26(int x) {
  x %= 26;
  if (x < 0)
    x += 26;
  return x;
}
int Reflector::c2i(char c) {
  return toupper(static_cast<unsigned char>(c)) - 'A';
}

Reflector::Reflector(const string &wiringStr) {
  for (int i = 0; i < 26; ++i) {
    map_[i] = c2i(wiringStr[i]);
  }
}

int Reflector::apply(int x) const { return map_[mod26(x)]; }
