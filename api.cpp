#include <iostream>
#include <cstdlib>
#include <ctime>
#include "api.hpp"
#include "constants.hpp"
#include "word.hpp"
#include "state.hpp"
#include "procedures.hpp"
#include "permutations.hpp"

using namespace std;

void encryption(unsigned char* key, unsigned char* nonce, unsigned char* ad, int adlen, unsigned char* plaintext, int ptlen, unsigned char* ciphertext, unsigned char* tag) {

	ascon_state S = initialization(key, nonce);
	processing_AD(&S, ad, adlen);
	processing_plaintext(&S, plaintext, ptlen, ciphertext);
	finalization(&S, key, tag);
}

void decryption(unsigned char* key, unsigned char* nonce, unsigned char* ad, int adlen, unsigned char* ciphertext, int ctlen, unsigned char* plaintextDecrypted, unsigned char* tagEncryption, unsigned char* tagDecryption) {

	ascon_state S = initialization(key, nonce);
	processing_AD(&S, ad, adlen);
	processing_ciphertext(&S, ciphertext, ctlen, plaintextDecrypted);
	finalization(&S, key, tagDecryption);

	bool tag_equality = true;
	for (int i = 0; i < 16; i++) {
		if (tagEncryption[i] != tagDecryption[i]) {
			tag_equality = false;
			break;
		}
	}

	if (tag_equality)
		for (int i = 0; i < ctlen; i++)
			cout << plaintextDecrypted[i] << '\t';
	else
		cout << "Different tags" << endl;

}

