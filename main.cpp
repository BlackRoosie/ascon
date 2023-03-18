#include <iostream>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "word.cpp"
#include "state.h"
#include "procedures.cpp"
#include "permutations.h"

using namespace std;

void encryption(unsigned char* key, unsigned char* nonce, unsigned char* ad, int adlen, unsigned char* plaintext, int ptlen, unsigned char* ciphertext, unsigned char* tag){
	
	ascon_state S = initialization(key, nonce);
	processing_AD(&S, ad, adlen);
	processing_plaintext(&S, plaintext, ptlen, ciphertext);
	finalization(&S, key, tag);
}

void decryption(unsigned char* key, unsigned char* nonce, unsigned char* ad, int adlen, unsigned char* ciphertext, int ctlen, unsigned char* plaintextDecrypted, unsigned char* tagEncryption, unsigned char* tagDecryption){
	
	ascon_state S = initialization(key, nonce);
	processing_AD(&S, ad, adlen);
	processing_ciphertext(&S, ciphertext, ctlen, plaintextDecrypted);
	finalization(&S, key, tagDecryption);

	bool tag_equality = true;
	for(int i = 0; i < 16; i++){
		if(tagEncryption[i] != tagDecryption[i]){
			tag_equality = false;
			break;
		}
	}

	if(tag_equality)
		for(int i = 0; i < ctlen; i++)
			cout<<plaintextDecrypted[i]<<'\t';
	else
		cout<<"Different tags"<<endl;

}

int main() {
	srand(time(NULL));
	unsigned char ad[5] = {'A', 'S', 'C', 'O', 'N'};
	int adlen = sizeof(ad);		//in bytes

	unsigned char plain[5] = {'a', 's', 'c', 'o', 'n'};
	int msglen = sizeof(plain);

	unsigned char key[KEYBYTES];
	unsigned char nonce[16];

	randomBytes(key, KEYBYTES);
	randomBytes(nonce, 16);

	unsigned char cipher[msglen];
	unsigned char plaintextDecryted[msglen];
	unsigned char tagEncryption[16];
	unsigned char tagDecryption[16];


	encryption(key, nonce, ad, adlen, plain, msglen, cipher, tagEncryption);
	decryption(key, nonce, ad, adlen, cipher, msglen, plaintextDecryted, tagEncryption, tagDecryption);

	return 0;
}