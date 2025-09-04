#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../include/enigmaMachine.h"
#include "../include/plugboard.h"
#include "../include/reflector.h"
#include "../include/rotor.h"

using namespace std;

// Parse "AB CD ZF" -> { {'A','B'}, {'C','D'}, {'Z','F'} }
static vector<pair<char, char>> parsePairs(const string &line) {
  vector<pair<char, char>> pairs;
  istringstream iss(line);
  string token;
  while (iss >> token) {
    string letters;
    for (char ch : token) {
      if (isalpha(static_cast<unsigned char>(ch)))
        letters.push_back(toupper(static_cast<unsigned char>(ch)));
    }
    if (letters.empty())
      continue;
    if (letters.size() != 2)
      throw runtime_error("Bad pair: " + token + " (use like AB)");
    pairs.emplace_back(letters[0], letters[1]);
  }
  return pairs;
}

int main() {
  try {
    cout << "=== Enigma (Plugboard + Rotors I/II/III + Reflector B) ===\n\n";

    // 1) Plugboard pairs
    cout << "Plugboard pairs (e.g., AB CD EF) or blank:\n> ";
    string pbLine;
    getline(cin, pbLine);
    vector<pair<char, char>> pbPairs =
        pbLine.empty() ? vector<pair<char, char>>{} : parsePairs(pbLine);
    Plugboard plug;
    plug.configure(pbPairs);

    // 2) Fixed rotors: I, II, III (historical wiring + notch)
    string WI = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char NI = 'Q';
    string WII = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char NII = 'E';
    string WIII = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char NIII = 'V';

    cout << "\nEnter starting positions L M R (e.g., Q E V or QEV):\n> ";
    string pos;
    getline(cin, pos);
    string letters;
    for (char ch : pos)
      if (isalpha(static_cast<unsigned char>(ch)))
        letters.push_back(toupper(static_cast<unsigned char>(ch)));
    if (letters.size() != 3)
      throw runtime_error("Provide exactly 3 letters for positions (L M R).");

    Rotor L(WI, NI, letters[0]);     // Left  = Rotor I
    Rotor M(WII, NII, letters[1]);   // Middle= Rotor II
    Rotor R(WIII, NIII, letters[2]); // Right = Rotor III

    // 3) Reflector B (fixed)
    string ReflB = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    Reflector reflector(ReflB);

    // 4) Build machine
    EnigmaMachine machine(L, M, R, reflector, plug);

    // 5) Message
    cout << "\nEnter message:\n> ";
    string msg;
    getline(cin, msg);

    // 6) Encrypt (same function decrypts if you reset positions to the same
    // start)
    string out = machine.encryptText(msg);
    cout << "\nCiphertext:\n" << out << "\n";

    cout << "\nTip: To decrypt, run again with the SAME rotor order and "
            "starting positions.\n";
    return 0;
  } catch (const exception &ex) {
    cerr << "Error: " << ex.what() << "\n";
    return 1;
  }
}
