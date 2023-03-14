#ifndef WORD_H
#define WORD_H

#include <iostream>

using namespace std;

void randomBytes(unsigned char* bytes, int n);

uint64_t loadBytes(unsigned char bytes[], int n);

void storeBytes(unsigned char* bytes, uint64_t word, int n);

#endif