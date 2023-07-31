#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
#include "state.hpp"

ascon_state initialization();

void absorbing(ascon_state* s, unsigned char* msg, int msglen);

void squeezing(ascon_state* s, unsigned char* hash);

void hashing(unsigned char* msg, int msglen, unsigned char* hash);

#endif