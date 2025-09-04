#include "../include/enigmaMachine.h"
#include <cctype>

using namespace std;

bool EnigmaMachine::isAZ(char c) {
  return std::isalpha(static_cast<unsigned char>(c));
}
int EnigmaMachine::c2i(char c) {
  return std::toupper(static_cast<unsigned char>(c)) - 'A';
}
int EnigmaMachine::mod26(int x) {
  x %= 26;
  if (x < 0)
    x += 26;
  return x;
}
char EnigmaMachine::i2c(int i) { return static_cast<char>('A' + mod26(i)); }

EnigmaMachine::EnigmaMachine(Rotor left, Rotor middle, Rotor right,
                             Reflector reflector, Plugboard plugboard)
    : L(left), M(middle), R(right), Refl(reflector), PB(plugboard) {}

void EnigmaMachine::stepRotorsAfterKey() {

  //  double-stepping behavior
  bool middleWill = (R.atNotch() || M.atNotch());
  bool leftWill = (M.atNotch());

  R.step(); // right always
  if (middleWill)
    M.step();
  if (leftWill)
    L.step();
}

char EnigmaMachine::encryptChar(char c) {
  if (!isAZ(c))
    return c; // leave spaces/punct unchanged

  int x = c2i(c);

  // 1) Plugboard IN
  x = PB.applyIndex(x);

  // 2) Forward through rotors: R -> M -> L
  x = R.forward(x);
  x = M.forward(x);
  x = L.forward(x);

  // 3) Reflector
  x = Refl.apply(x);

  // 4) Backward through rotors: L -> M -> R
  x = L.backward(x);
  x = M.backward(x);
  x = R.backward(x);

  // 5) Plugboard OUT
  x = PB.applyIndex(x);

  // 6) STEP AFTER encrypting this char (matches your requirement text)
  stepRotorsAfterKey();

  return i2c(x);
}

std::string EnigmaMachine::encryptText(const std::string &msg) {
  std::string out;
  out.reserve(msg.size());
  for (char ch : msg) {
    if (isAZ(ch))
      out.push_back(encryptChar(std::toupper(static_cast<unsigned char>(ch))));
    else
      out.push_back(ch);
  }
  return out;
}
