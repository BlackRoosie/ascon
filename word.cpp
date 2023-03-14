#include <iostream>
#include "word.h"
#include "state.h"

using namespace std;

void randomBytes(unsigned char* bytes, int n) {

    int temp;
	for (int i = 0; i < n; i++)
	{
		temp = rand();
		bytes[i] = temp & 255;
	}
}

//to creating 64bit word
uint64_t loadBytes(unsigned char bytes[], int n){

	uint64_t word = 0;
	for(int i = 0; i < n; i++){
		word <<= 8;
		word |= uint64_t(bytes[i]);			//bytes[i] = 8 bits
	}

	return word;
}

void storeBytes(unsigned char* bytes, uint64_t word, int n){
	
	for(int i = 0; i < n; i++){
		bytes[i] = (uint8_t)(word >> (56 - i*8));
	}

}
