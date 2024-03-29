#ifndef WORD_HPP
#define WORD_HPP

#include <iostream>

using namespace std;

void randomBytes(unsigned char* bytes, int n);

uint64_t loadBytes(unsigned char bytes[], int n);

void storeBytes(unsigned char* bytes, uint64_t word, int n);

uint64_t createPadding(int len);

#endif