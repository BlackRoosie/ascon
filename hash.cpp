#pragma once
#include <iostream>
#include "constants.hpp"
#include "state.hpp"
#include "permutations.hpp"
#include "word.hpp"
#include "hash.hpp"

using namespace std;

ascon_state initialization() {

	ascon_state S;

	S.x[0] = HASH_IV;
	S.x[1] = 0x00;
	S.x[2] = 0x00;
	S.x[3] = 0x00;
	S.x[4] = 0x00;

	P12(&S);

	return S;
}

void absorbing(ascon_state* s, unsigned char* msg, int msglen) {

	int i = 0;
	uint64_t mi;

	while (msglen >= HASH_RATE) {

		mi = loadBytes(msg + i * 8, 8);
		s->x[0] ^= mi;
		P12(s);

		msglen -= RATE;
		i += 1;
	}

	if (msglen > 0) {
		mi = ((loadBytes(msg + i * 8, msglen) << 1) | 1) << ((RATE - msglen) * 8 - 1);
	}
	else {
		mi = ((uint64_t)(1) << (RATE * 8 - 1));
	}

	s->x[0] ^= mi;
}

void squeezing(ascon_state* s, unsigned char* hash) {

	int i = 0;
	P12(s);

	while (i < HASH_H) {

		storeBytes(hash + i, s->x[0], 8);
		i += 8;
		P12(s);
	}

}

void hashing(unsigned char* msg, int msglen, unsigned char* hash) {

	ascon_state s = initialization();
	absorbing(&s, msg, msglen);
	squeezing(&s, hash);
}