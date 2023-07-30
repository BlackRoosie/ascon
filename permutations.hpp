#ifndef PERMUTATIONS_HPP
#define PERMUTATIONS_HPP

#include "state.hpp"

using namespace std;

uint64_t rotation(uint64_t* word, int shift);

void round(ascon_state* s, uint8_t c);

void P12(ascon_state* s);

void P6(ascon_state* s);

#endif