#include <iostream>
#include "word.hpp"
#include "state.hpp"
#include "constants.hpp"

using namespace std;

//to creating 64bit word
uint64_t loadBytes(unsigned char bytes[], int n){

	uint64_t word = 0;
	for(int i = 0; i < n; i++){
		word <<= 8;
		word |= uint64_t(bytes[i]);			//bytes[i] = 8 bits
	}

	return word;
}

//creating whole msg from a 64bit word
void storeBytes(unsigned char* bytes, uint64_t word, int n){
	
	for(int i = 0; i < n; i++)
		bytes[i] = (uint8_t)(word >> (56 - i*8));

}

uint64_t createPadding(int len){

	uint64_t padding = 0;
	for(int i = 0; i < len; i++){
		padding ^= 0xff;
		padding = padding << 8;
	}
	padding = padding << ((RATE-len-1) * 8);

	return padding;
}
