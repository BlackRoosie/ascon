#include <iostream>
#include <cstdlib>
#include <ctime>
#include "api.hpp"

using namespace std;

void randomBytes(unsigned char* bytes, int n) {

    int temp;
	for (int i = 0; i < n; i++)
	{
		temp = rand();
		bytes[i] = temp & 255;
	}
}

int main() {

	//helping things - setting key, tag, nonce, msg
	srand(time(NULL));
	unsigned char ad[5] = {'A', 'S', 'C', 'O', 'N'};
	const int adlen = sizeof(ad);		//in bytes

	unsigned char plain[5] = {'a', 's', 'c', 'o', 'n'};
	const int msglen = sizeof(plain);

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