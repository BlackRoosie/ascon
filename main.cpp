#include <iostream>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "word.cpp"
#include <bitset>

using namespace std;

int main() {
	cout<<endl;

	srand(time(NULL));

	unsigned char key[KEYBYTES];
	unsigned char nonce[16];

	randomBytes(key, KEYBYTES);
	randomBytes(nonce, 16);

	// for(int i = 0; i < 16; i++)
	// 	cout<<bitset<8>(key[i])<<endl;



	return 0;
}