#ifndef PROCEDURES_HPP
#define PROCEDURES_HPP

#include <iostream>
#include "constants.hpp"
#include "state.hpp"
#include "permutations.hpp"

using namespace std;

ascon_state initialization(unsigned char key[], unsigned char nonce[]) ;

void processing_AD(ascon_state* s, unsigned char* ad, int adlen);

void processing_plaintext(ascon_state* s, unsigned char* plaintext, int ptlen, unsigned char* ciphertext);

void processing_ciphertext(ascon_state* s, unsigned char* ciphertext, int ctlen, unsigned char* plaintextDecrypted);

void finalization(ascon_state* s, unsigned char* key, unsigned char* tag);

#endif