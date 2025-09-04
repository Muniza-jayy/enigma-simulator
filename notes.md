# Enigma Assignment – My Working Notes

## Alphabet

- c2i(char c) returns the index of a letter in the alphabet
- i2c(int i) returns the letter at index i
- isAZ(char c) returns true if c is an A-Z letter
- toAZ(char c) returns the uppercase version of c
- sanitize(const string& s) returns a copy of s with only A-Z letters

## Plugboard

I used an array `map_[26]`.

- At start: `map_[i] = i` (A->A, B->B, ...).
- In `configure()`:
  1. Reset identity.
  2. For each pair (A,B):
     - Make uppercase.
     - Convert to indices (A=0, B=1).
     - Check valid (not AA, not reused).
     - Set both directions: `map_[0]=1`, `map_[1]=0`.
  3. Mark letters as used.

## Reflector

I used an array 'wiring*[26]' inverse*[26] notch* position*.

- wiring\_ is the forward wiring (A->B, C->D, ...)
- inverse\_ is the inverse wiring (B->A, D->C, ...)
- notch\_ is the index of the notch (Q)
- position\_ is the current position (A..Z)
- apply(int x) returns the index of the letter at position x
  - x is in 0..25
  - apply(x) is in 0..25
    -forward(int x) does forward mapping
- x is in 0..25
- x is added to position\_
- position* is mapped to the wiring*
- the result is subtracted from position\_
  -inverse(int x) does inverse mapping
  -setPosition(char posChar) sets the position
  -step() advances the position
  -atNotch() returns true if the position is the notch

## Enigma Machine

- Encrypt exactly one character (letters only; others returned unchanged)
- Convenience: process a whole string (keeps spaces/punct)
- Encryption is done in three steps:
- 1. Plugboard IN
- 2. Forward through rotors: R -> M -> L
- 3. Reflector
- 4. Backward through rotors: L -> M -> R
- 5. Plugboard OUT
- 6. STEP AFTER encrypting this char (matches your requirement text)

## Main

- Parse "AB CD ZF" -> { {'A','B'}, {'C','D'}, {'Z','F'} }
- Build machine
- Encrypt (same function decrypts if you reset positions to the same start)
