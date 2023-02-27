#include <iostream>
#include "constants.h"
#include "state.h"
#include "word.h"
#include "permutations.h"
#include "encryption.h"

using namespace std;

ascon_state initialization(unsigned char* key, unsigned char* nonce) {
	ascon_state S;

	S.x[0] = IV;
	S.x[1] = loadBytes(key, 8);
	S.x[2] = loadBytes(key + 8, 8);
	S.x[3] = loadBytes(nonce, 8);
	S.x[4] = loadBytes(nonce + 8, 8);

	//here smth wrong, need to check
	P12(&S);

	return S;
}