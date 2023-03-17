#include <iostream>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "word.cpp"
#include "state.h"
#include "procedures.cpp"
#include "permutations.h"
#include <bitset>

using namespace std;

void encryption(unsigned char* key, unsigned char* nonce, unsigned char* ad, int adlen, unsigned char* plaintext, int ptlen, unsigned char* ciphertext, unsigned char* tag){
	
	ascon_state S = initialization(key, nonce);
	processing_AD(&S, ad, adlen);
	processing_plaintext(&S, plaintext, ptlen, ciphertext);
	finalization(&S, key, tag);
}

void decryption(unsigned char* key, unsigned char* nonce, unsigned char* ad, int adlen, unsigned char* ciphertext, int ctlen, unsigned char* plaintext, unsigned char* tag, unsigned char* tag_encrypted){
	
	ascon_state S = initialization(key, nonce);
	processing_AD(&S, ad, adlen);
	processing_ciphertext(&S, ciphertext, ctlen, plaintext);
	// processing_plaintext(&S, plaintext, ptlen, ciphertext);
	finalization(&S, key, tag);

	bool tag_equality = true;
	for(int i = 0; i < 16; i++){
		if(tag[i] != tag_encrypted[i]){
			tag_equality = false;
			break;
		}
	}

	if(tag_equality)
		for(int i = 0; i < ctlen; i++)
			cout<<plaintext[i]<<'\t';
	else
		cout<<"Different tags"<<endl;

}

void test(){

	unsigned char key[KEYBYTES];
	unsigned char nonce[16];

	//0xe419dd4a0dae35a8af5387f6ec88dd98
	key[0] = 0xe4;
	key[1] = 0x19;
	key[2] = 0xdd;
	key[3] = 0x4a;
	key[4] = 0x0d;
	key[5] = 0xae;
	key[6] = 0x35;
	key[7] = 0xa8;
	key[8] = 0xaf;
	key[9] = 0x53;
	key[10] = 0x87;
	key[11] = 0xf6;
	key[12] = 0xec;
	key[13] = 0x88;
	key[14] = 0xdd;
	key[15] = 0x98;
	//0x16b48b80e52c721ccf759c25e24f7e55
	nonce[0] = 0x16;
	nonce[1] = 0xb4;
	nonce[2] = 0x8b;
	nonce[3] = 0x80;
	nonce[4] = 0xe5;
	nonce[5] = 0x2c;
	nonce[6] = 0x72;
	nonce[7] = 0x1c;
	nonce[8] = 0xcf;
	nonce[9] = 0x75;
	nonce[10] = 0x9c;
	nonce[11] = 0x25;
	nonce[12] = 0xe2;
	nonce[13] = 0x4f;
	nonce[14] = 0x7e;
	nonce[15] = 0x55;

	unsigned char ad[5] = {'A', 'S', 'C', 'O', 'N'};
	int adlen = sizeof(ad);		//in bytes
	// for(int i = 0; i < 5; i ++)
	// 	cout<<bitset<8>(ad[i])<<endl;

	unsigned char plain[5] = {'a', 's', 'c', 'o', 'n'};
	int ptlen = sizeof(plain);

	unsigned char cipher[ptlen];
	unsigned char plainEncrypted[ptlen];

	cout<<"INITIALIZATION"<<endl;
	ascon_state S = initialization(key, nonce);
	// for(int i = 0; i < 5; i ++)
	// 	cout<<S.x[i]<<endl;
		// cout<<bitset<64>(S.x[i])<<endl;

	cout<<"-----------------------------------------------"<<endl;
	cout<<"PROCESSING AD"<<endl;
	processing_AD(&S, ad, adlen);
	// for(int i = 0; i < 5; i ++)
	// 	cout<<S.x[i]<<endl;
	// 	cout<<bitset<64>(S.x[i])<<endl;

	cout<<"-----------------------------------------------"<<endl;
	cout<<"PROCESSING PLAINTEXT"<<endl;
	processing_plaintext(&S, plain, ptlen, cipher);
	// for(int i = 0; i < ptlen; i ++)
	// 	cout<<S.x[i]<<endl;
	// 	cout<<bitset<8>(cipher[i])<<'\t';

	cout<<"-----------------------------------------------"<<endl;
	cout<<"FINALIZATION"<<endl;
	unsigned char tag[16]; 
	finalization(&S, key, tag);
	cout<<"tag:"<<endl;
	for(int i = 0; i < 16; i++)
		cout<<bitset<8>(tag[i])<<'\t';

	cout<<endl;
	cout<<"----------------DECRYPTION---------------------"<<endl;
	cout<<"INITIALIZATION"<<endl;
	S = initialization(key, nonce);
	// for(int i = 0; i < 5; i ++)
	// 	cout<<S.x[i]<<endl;
		// cout<<bitset<64>(S.x[i])<<endl;

	cout<<endl;
	cout<<"PROCESSING AD"<<endl;
	processing_AD(&S, ad, adlen);
	// for(int i = 0; i < 5; i ++)
	// 	cout<<S.x[i]<<endl;

	cout<<endl;
	cout<<"PROCESSING CIPHERTEXT"<<endl;
	processing_ciphertext(&S, cipher, ptlen, plainEncrypted);
	// for(int i = 0; i < 5; i ++)
	// 	cout<<S.x[i]<<endl;

	cout<<endl;
	cout<<"FINALIZATION"<<endl;
	unsigned char tag_to_decrypt[16];
	finalization(&S, key, tag_to_decrypt);
	// for(int i = 0; i < 5; i ++)
	// 	cout<<S.x[i]<<endl;

	// cout<<endl<<"tag:"<<endl;
	// for(int i = 0; i < 16; i++)
	// 	cout<<bitset<8>(tag_to_decrypt[i])<<'\t';

	cout<<endl;
	bool tag_equality = true;
	for(int i = 0; i < 16; i++){
		if(tag[i] != tag_to_decrypt[i]){
			tag_equality = false;
			break;
		}
	}

	cout<<endl;
	if(tag_equality)
		for(int i = 0; i < ptlen; i++)
			cout<<plainEncrypted[i]<<'\t';
	else
		cout<<"Different tags"<<endl;

}

int main() {
	cout<<endl;

	srand(time(NULL));
	test();

	// unsigned char ad[5] = {'A', 'S', 'C', 'O', 'N'};
	// int adlen = sizeof(ad);		//in bytes

	// unsigned char plain[5] = {'a', 's', 'c', 'o', 'n'};
	// int ptlen = sizeof(plain);

	// unsigned char key[KEYBYTES];
	// unsigned char nonce[16];

	// randomBytes(key, KEYBYTES);
	// randomBytes(nonce, 16);

	// unsigned char cipher[ptlen];
	// unsigned char tag[16];

	// encryption(key, nonce, ad, adlen, plain, ptlen, cipher, tag);

	


	return 0;
}