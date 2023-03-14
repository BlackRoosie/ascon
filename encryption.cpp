#include <iostream>
#include "encryption.h"
#include "constants.h"
#include "state.h"
#include "word.h"
#include "permutations.cpp"

#include <bitset>

using namespace std;

ascon_state initialization(unsigned char key[], unsigned char nonce[]) {
	ascon_state S;

	const uint64_t K0 = loadBytes(key, 8);
	const uint64_t K1 = loadBytes(key + 8, 8);

	S.x[0] = IV;
	S.x[1] = K0;
	S.x[2] = K1;
	S.x[3] = loadBytes(nonce, 8);
	S.x[4] = loadBytes(nonce + 8, 8);

	P12(&S);

	S.x[3] ^= K0;
	S.x[4] ^= K1;

	return S;
}

void processing_AD(ascon_state* s, unsigned char* ad, int adlen){
	
	int i = 0;
	uint64_t ai;

	if(adlen > 0){
		while(adlen >= RATE){

			ai = loadBytes(ad + i*8, 8);
			// cout<<"ai: "<<bitset<64>(ai)<<endl;
			s->x[0] ^= ai;
			P6(s);	
			adlen -= RATE;
			i += 1;
		}

		//checking after while if there is still bits to create last block
		if(adlen > 0){
			ai = ((loadBytes(ad + i*8, adlen) << 1) | 1 ) << ((RATE - adlen)*8 - 1);
			// cout<<"ai: "<<bitset<64>(ai)<<endl;
			s->x[0] ^= ai;
			P6(s);
		}
	}

	s->x[4] ^= 1;

}

void processing_plaintext(ascon_state* s, unsigned char* plaintext, int ptlen, unsigned char* ciphertext){

	int i = 0;
	uint64_t pi;
	uint64_t ci;
	
	while(ptlen > RATE){

		pi = loadBytes(plaintext + i*8, 8);
		cout<<"pi: "<<bitset<64>(pi)<<endl;
		s->x[0] ^= pi;
		ci = s->x[0];
		storeBytes(ciphertext + i*8, ci, ptlen);
		P6(s);	

		ptlen -= RATE;
		i += 1;
	}

	if(ptlen < RATE){
		pi = ((loadBytes(plaintext + i*8, ptlen) << 1) | 1 ) << ((RATE - ptlen)*8 - 1);
	} else {
		pi = loadBytes(plaintext + i*8, 8);
	}

	s->x[0] ^= pi;
	ci = s->x[0];
	storeBytes(ciphertext + i*8, ci, ptlen);

}

//something wrong
void finalization(ascon_state* s, unsigned char* key, unsigned char* tag){

	const uint64_t K0 = loadBytes(key, 8);
	const uint64_t K1 = loadBytes(key + 8, 8);

	s->x[1] ^= K0;
	s->x[2] ^= K1;
	P12(s);
	s->x[3] ^= K0;
	s->x[4] ^= K1;

	storeBytes(tag, s->x[3], 8);
	storeBytes(tag + 8, s->x[4], 8);
}
