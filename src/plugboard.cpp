#include "../include/plugboard.h"
#include "../include/alphabet.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Plugboard::Plugboard() { resetIdentity(); }

void Plugboard::resetIdentity() {
  for (int i = 0; i < 26; ++i)
    maps[i] = i; // A->A, B->B
}

void Plugboard::configure(const vector<pair<char, char>> &pairs) {
  resetIdentity();

  bool used[26] = {false}; // to ensure each letter appears in at most one pair

  for (auto pr : pairs) {
    char a = Alphabet::toAZ(pr.first);
    char b = Alphabet::toAZ(pr.second);

    if (!Alphabet::isAZ(a) || !Alphabet::isAZ(b)) {
      throw runtime_error("Plugboard letters must be A–Z.");
    }

    int ai = Alphabet::c2i(a);
    int bi = Alphabet::c2i(b);

    if (ai == bi) {
      throw runtime_error(
          "Plugboard cannot pair a letter with itself (e.g., AA).");
    }
    if (used[ai] || used[bi]) {
      throw runtime_error("A letter appears in more than one plugboard pair.");
    }

    // Set symmetric mapping: A<->B, C<->D, etc.
    maps[ai] = bi;
    maps[bi] = ai;
    used[ai] = used[bi] = true;
  }
}

int Plugboard::applyIndex(int x) const {
  // x expected in 0..25
  return maps[x];
}

char Plugboard::applyChar(char c) const {
  if (!Alphabet::isAZ(c))
    return c;               // leave non-letters alone
  int x = Alphabet::c2i(c); // char -> index
  int y = applyIndex(x);    // swap via array
  return Alphabet::i2c(y);  // index -> uppercase char
}

void Plugboard::printMapping() const {
  for (int i = 0; i < 26; ++i) {
    cout << Alphabet::i2c(i) << "->" << Alphabet::i2c(maps[i])
         << (i == 25 ? '\n' : ' ');
  }
}
