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

	//
	key[0] = 0x54;
	key[1] = 0x71;
	key[2] = 0x25;
	key[3] = 0x22;
	key[4] = 0xdc;
	key[5] = 0x61;
	key[6] = 0xe8;
	key[7] = 0xcf;
	key[8] = 0xd7;
	key[9] = 0x02;
	key[10] = 0x93;
	key[11] = 0xec;
	key[12] = 0xd8;
	key[13] = 0x3d;
	key[14] = 0x03;
	key[15] = 0x6e;
//c3acc0f491f7
	nonce[0] = 0xb3;
	nonce[1] = 0xea;
	nonce[2] = 0x26;
	nonce[3] = 0x78;
	nonce[4] = 0xfa;
	nonce[5] = 0x66;
	nonce[6] = 0x72;
	nonce[7] = 0xe6;
	nonce[8] = 0xaa;
	nonce[9] = 0xf7;
	nonce[10] = 0xc3;
	nonce[11] = 0xac;
	nonce[12] = 0xc0;
	nonce[13] = 0xf4;
	nonce[14] = 0x91;
	nonce[15] = 0xf7;

	// randomBytes(key, KEYBYTES);
	// randomBytes(nonce, 16);

	// for(int i = 0; i < 16; i++)
	// 	cout<<bitset<8>(key[i])<<endl;

	// ascon_state S = initialization(key, nonce);

	// for(int i = 0; i < 5; i ++)
	// 	cout<<bitset<64>(S.x[i])<<endl;

	return 0;
}