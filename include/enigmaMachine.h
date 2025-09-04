#ifndef ENIGMA_MACHINE_H
#define ENIGMA_MACHINE_H

#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include <string>
using namespace std;

class EnigmaMachine {
public:
  EnigmaMachine(Rotor left, Rotor middle, Rotor right, Reflector reflector,
                Plugboard plugboard);

  // Encrypt exactly one character (letters only; others returned unchanged)
  char encryptChar(char c);

  //  process a whole string (keeps spaces/punct)
  string encryptText(const std::string &msg);

private:
  Rotor L, M, R;  // Left, Middle, Right rotors
  Reflector Refl; // Reflector
  Plugboard PB;   // Plugboard

  //  STEP AFTER encrypting each character
  void stepRotorsAfterKey();

  // small helpers
  static bool isAZ(char c);
  static int c2i(char c);
  static int mod26(int x);
  static char i2c(int i);
};

#endif
