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

uint64_t loadBytes(unsigned char* bytes, int n){

	uint64_t word = 0;
	for(int i = 0; i < n; i++){
		word <<= 8;
		word |= uint64_t(bytes[i]);
	}

	return word;
}
