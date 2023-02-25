#include <iostream>
#include <cstdlib>
#include <ctime>
#include "constants.h"

using namespace std;

void randomBytes(char* bytes, int n) {

	int temp;

	for (int i = 0; i < n; i++)
	{
		temp = rand();
		bytes[i] = (char)(temp & 255);
	}
}

int main() {

	srand(time(NULL));
	char key[KEYBYTES];
	randomBytes(key, KEYBYTES);

	for (int i = 0; i < KEYBYTES; i++){
		cout << i << ": " << key[i] << '\n';
	}
		

	return 0;
}