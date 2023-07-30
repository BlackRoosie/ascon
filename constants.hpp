#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <stdint.h>

const int KEYBYTES = 16;
const int RATE = 8;     //block size in bytes
const int ROUNDS_PA = 12;
const int ROUNDS_PB = 6;

#define IV (((uint64_t)(KEYBYTES * 8) << 56) | ((uint64_t)(RATE * 8) << 48) | ((uint64_t)(ROUNDS_PA) << 40) | ((uint64_t)(ROUNDS_PB) << 32))

#endif // !CONSTANT_HPP