#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <stdint.h>

const int KEYBYTES = 16;
const int RATE = 8;     //block size in bytes
const int ROUNDS_PA = 12;
const int ROUNDS_PB = 6;

const int HASH_RATE = 8;
const int HASH_ROUNDS_PA = 12;
const int HASH_ROUNDS_PB = 12;
const int HASH_H = 32;		//hash length in bytes

#define IV (((uint64_t)(KEYBYTES * 8) << 56) | ((uint64_t)(RATE * 8) << 48) | ((uint64_t)(ROUNDS_PA) << 40) | ((uint64_t)(ROUNDS_PB) << 32))
#define HASH_IV (((uint64_t)(RATE*8) << 48) | ((uint64_t)(HASH_ROUNDS_PA) << 40) | ((uint64_t)(HASH_ROUNDS_PA - HASH_ROUNDS_PB) << 32) | (uint64_t)(HASH_H * 8) << 0)
#endif // !CONSTANT_HPP
