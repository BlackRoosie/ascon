#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include "constants.h"
#include "state.h"
#include "word.h"
#include "permutations.h"

using namespace std;

ascon_state initialization(unsigned char key[], unsigned char nonce[]) ;

void processing_AD(ascon_state* s, unsigned char* ad, int adlen);

void processing_plaintext(ascon_state* s, unsigned char* plaintext, int ptlen, unsigned char* ciphertext);

#endif