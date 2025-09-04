#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <utility>
#include <vector>

class Plugboard {
public:
  Plugboard();

  // Configure from pairs like { {'A','B'}, {'C','D'} }.
  // Validates: A–Z only, no self-pair, and no letter used twice.
  void configure(const std::vector<std::pair<char, char>> &pairs);

  // Apply to a letter index 0..25 (fast O(1))
  int applyIndex(int x) const;

  // Letters are returned UPPERCASE.
  char applyChar(char c) const;

  void printMapping() const;

private:
  int maps[26];

  void resetIdentity();
};

#endif
