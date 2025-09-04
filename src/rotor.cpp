#include "../include/rotor.h"
#include <cctype>

using namespace std;

int Rotor::mod26(int x) {
  x %= 26;
  if (x < 0)
    x += 26;
  return x;
}
int Rotor::c2i(char c) {
  return std::toupper(static_cast<unsigned char>(c)) - 'A';
}

Rotor::Rotor(const string &wiringStr, char notchChar, char posChar) {
  // 1) Build forward wiring as indices 0..25
  for (int i = 0; i < 26; ++i)
    wiring_[i] = c2i(wiringStr[i]);

  // 2) Build inverse wiring (so backward path can “undo” forward)
  for (int i = 0; i < 26; ++i)
    inverse_[wiring_[i]] = i;

  // 3) Save notch and starting position as indices
  notch_ = c2i(notchChar);
  setPosition(posChar);
}

// state ops
void Rotor::setPosition(char posChar) { position_ = c2i(posChar); }
void Rotor::step() { position_ = mod26(position_ + 1); }
bool Rotor::atNotch() const { return position_ == notch_; }

// ---------- mapping ----------
int Rotor::forward(int x) const {

  // 1) shift in by position
  int y = mod26(x + position_);
  // 2) apply fixed wiring
  int z = wiring_[y];
  // 3) shift out back by position
  return mod26(z - position_);
}

int Rotor::backward(int x) const {
  // x enters on left side (coming back from reflector)
  // 1) shift in by position
  int y = mod26(x + position_);
  // 2) apply inverse wiring
  int z = inverse_[y];
  // 3) shift out back by position
  return mod26(z - position_);
}
