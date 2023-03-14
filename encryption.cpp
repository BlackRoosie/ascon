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
			cout<<"ai: "<<bitset<64>(ai)<<endl;
			s->x[0] ^= ai;
			P6(s);	
			adlen -= RATE;
			i += 1;
		}

		//checking after while if there is still bits to create last block
		if(adlen > 0){
			ai = ((loadBytes(ad + i*8, adlen) << 1) | 1 ) << ((RATE - adlen)*8 - 1);
			cout<<"ai: "<<bitset<64>(ai)<<endl;
			s->x[0] ^= ai;
			P6(s);
		}
	}

	s->x[4] ^= 1;

}

//to będzie zwracało ciphertext
void processing_plaintext(ascon_state* s, unsigned char* plaintext, unsigned char* ciphertext){
	int ptlen = sizeof(plaintext)/sizeof(char);
	int i = 0;
	uint64_t pi;
	
	while(ptlen >= RATE){
		pi = loadBytes(plaintext + i*1, 1);
		//xor ai with first r bits Sr of S
		s->x[0] ^= (pi << 56);


		// P6(s);	
		ptlen -= RATE;
		i += 1;
	}

	pi = loadBytes(plaintext + i*8, 1);
	pi = ((pi << 1) | 1) << (RATE-ptlen-1);		// P||1||{0}*(r-1-(|P| mod r))
	s->x[0] ^= (pi << 56);
	P6(s);

}
