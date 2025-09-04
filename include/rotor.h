#ifndef ROTOR_H
#define ROTOR_H

#include <array>
#include <string>

class Rotor {
public:
  // wiringStr: 26 letters permutation (e.g., "EKMFLGDQVZNTOWYHXUSPAIBRCJ")
  // notchChar: turnover letter (e.g., 'Q' for Rotor I)
  // posChar:   starting position letter (e.g., 'A'..'Z')
  Rotor(const std::string &wiringStr, char notchChar, char posChar);

  // Set/advance/read state
  void setPosition(char posChar); // window letter
  void step();                    // position = (position + 1) % 26
  bool atNotch() const;           // true if position equals notch

  // Core mapping (indices 0..25). Forward = right->left; Backward = left->right
  int forward(int x) const;  // (x + pos) -> wiring -> (.. - pos)
  int backward(int x) const; // (x + pos) -> inverse -> (.. - pos)

private:
  std::array<int, 26> wiring_{};  // forward permutation
  std::array<int, 26> inverse_{}; // inverse permutation
  int position_ = 0;              // current rotation 0..25
  int notch_ = 0;                 // notch index 0..25

  // local helpers (kept here so Rotor works independently)
  static int c2i(char c); // 'A'..'Z' -> 0..25
  static int mod26(int x);
};

#endif // ROTOR_H
