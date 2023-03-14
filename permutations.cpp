#include "permutations.h"
#include "state.h"

#include <iostream>

using namespace std;

uint64_t rotation(uint64_t word, int shift){
    return (word << (64 - shift) | word >> shift);
}

void round(ascon_state* s, uint8_t c){
    ascon_state t;

    //constant addition
    s->x[2] ^= c;

    //substitution
    s->x[0] ^= s->x[4];
    s->x[4] ^= s->x[3];
    s->x[2] ^= s->x[1];

    t.x[0] = (~s->x[0] & s->x[1]);
    t.x[1] = (~s->x[1] & s->x[2]);
    t.x[2] = (~s->x[2] & s->x[3]);
    t.x[3] = (~s->x[3] & s->x[4]);
    t.x[4] = (~s->x[4] & s->x[0]);

    s->x[0] ^= t.x[1];
    s->x[1] ^= t.x[2];
    s->x[2] ^= t.x[3];
    s->x[3] ^= t.x[4];
    s->x[4] ^= t.x[0];

    s->x[1] ^= s->x[0];
    s->x[0] ^= s->x[4];
    s->x[3] ^= s->x[2];
    s->x[2] = ~s->x[2]; 

    //linear diffusion
    s->x[0] ^= rotation(s->x[0], 19) ^ rotation(s->x[0], 28);
    s->x[1] ^= rotation(s->x[1], 61) ^ rotation(s->x[1], 39);
    s->x[2] ^= rotation(s->x[2], 1) ^ rotation(s->x[2], 6);
    s->x[3] ^= rotation(s->x[3], 10) ^ rotation(s->x[3], 17);
    s->x[4] ^= rotation(s->x[4], 7) ^ rotation(s->x[4], 41);
}

void P12(ascon_state* s){
    round(s, 0xf0);
    round(s, 0xe1);
    round(s, 0xd2);
    round(s, 0xc3);
    round(s, 0xb4);
    round(s, 0xa5);
    round(s, 0x96);
    round(s, 0x87);
    round(s, 0x78);
    round(s, 0x69);
    round(s, 0x5a);
    round(s, 0x4b);	
}

void P6(ascon_state* s){
    round(s, 0x96);
    round(s, 0x87);
    round(s, 0x78);
    round(s, 0x69);
    round(s, 0x5a);
    round(s, 0x4b);		
}