#include "../include/alphabet.h"
#include <cctype> // for isalpha(), toupper()
using namespace std;

int Alphabet::c2i(char c) { return toupper(c) - 'A'; }

char Alphabet::i2c(int i) {
  i = i % 26; // wrap into 0to25
  if (i < 0)
    i += 26; // handle negatives
  return 'A' + i;
}

bool Alphabet::isAZ(char c) {
  return isalpha(c); // true if A-Z or a-z
}

char Alphabet::toAZ(char c) {
  return toupper(c); // return uppercase
}

string Alphabet::sanitize(const string &s) {
  string out;
  for (char ch : s) {
    if (isAZ(ch))
      out.push_back(toAZ(ch)); // keep letters
    else if (ch == ' ')
      out.push_back(' '); // keep spaces
                          // ignore digits, punctuation
  }
  return out;
}
