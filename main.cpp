#include <iostream>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "word.cpp"
#include "state.h"
#include "encryption.cpp"
#include "permutations.h"
#include <bitset>

using namespace std;

int main() {
	cout<<endl;

	srand(time(NULL));

	unsigned char key[KEYBYTES];
	unsigned char nonce[16];

	//0xe419dd4a0dae35a8af5387f6ec88dd98
	// key[0] = 0xe4;
	// key[1] = 0x19;
	// key[2] = 0xdd;
	// key[3] = 0x4a;
	// key[4] = 0x0d;
	// key[5] = 0xae;
	// key[6] = 0x35;
	// key[7] = 0xa8;
	// key[8] = 0xaf;
	// key[9] = 0x53;
	// key[10] = 0x87;
	// key[11] = 0xf6;
	// key[12] = 0xec;
	// key[13] = 0x88;
	// key[14] = 0xdd;
	// key[15] = 0x98;
	// //0x16b48b80e52c721ccf759c25e24f7e55
	// nonce[0] = 0x16;
	// nonce[1] = 0xb4;
	// nonce[2] = 0x8b;
	// nonce[3] = 0x80;
	// nonce[4] = 0xe5;
	// nonce[5] = 0x2c;
	// nonce[6] = 0x72;
	// nonce[7] = 0x1c;
	// nonce[8] = 0xcf;
	// nonce[9] = 0x75;
	// nonce[10] = 0x9c;
	// nonce[11] = 0x25;
	// nonce[12] = 0xe2;
	// nonce[13] = 0x4f;
	// nonce[14] = 0x7e;
	// nonce[15] = 0x55;

	randomBytes(key, KEYBYTES);
	randomBytes(nonce, 16);

	// for(int i = 0; i < 16; i++)
	// 	cout<<bitset<8>(key[i])<<endl;

	ascon_state S = initialization(key, nonce);

	for(int i = 0; i < 5; i ++)
		cout<<bitset<64>(S.x[i])<<endl;

	return 0;
}