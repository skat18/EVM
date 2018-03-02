#include <stdio.h>
#include <stdlib.h>
#include "mySimpleComputer.h"

int sc_memoryInit () {
	for ( int i = 0; i < 100; i++) 
		mass[i] = 0;
        int temp[] = {10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76};
        memcpy(commArr, temp, sizeof(temp));
}

int sc_memorySet (int address,int value) {
	if (address > 100 || address < 0) {
		sc_regSet(F_FENCE, 1);
		return -1;
	}
	mass[address] = value; 
	sc_regSet(F_FENCE, 0)
	return 0;
}

int sc_memoryGet (int address, int* value) {
	if (address > 100 || address < 0) {
	sc_regSet(F_FENCE, 1);
	return -1; }
	
	*value = mass[address];
	sc_regSet(F_FENCE, 0);
	return 0;
}

int sc_memorySave (char *filename) {
	FILE *f;
	f = fopen(filename, "w+b");
	if ( f == NULL ) return -1;
	for (int i = 0; i < 100; i++) 
		fwrite(&mass[i], sizeof(int), 1, f);
		fclose(f);
	return 0;
}

int sc_memoryLoad (char *filename) {
	FILE *f;
	f = fopen(filename, "rb");
	if (f == NULL) return -1;
	for (int i = 0; i < 100; i++)
		fread(mass, sizeof(mass), 1, f);
		fclose(f);
	return 0;
}

int sc_regInit () {
	regf = 0;
	return 0;
}

int sc_regSet (int registered, int value) {
	if (value > 1 || value < 0) return -1;
	if (registered < 0 || registered > 5) return -1; 
	if (value == 1) {
	regf = regf | (1 << (registered –1)); }
	else regf = regf & (~(1 << (registered – 1)));
}

int sc_regGet (int registered, int * value) {
	if (registered < 0 || registered > 5) return -1;

	*value = (regf >> (registered -1)) & 0x1; 
	return 0;
}

int sc_commandEncode (int command, int operand, int * value) {
	for (int i = 0; i < 38; i++) {
		if (command == commArr[i]) {
			*value = command << 8 | (operand & 127);
			sc_regSet(F_BAD, 0);
			return 0;
		}
	}
	sc_regSet(BADFLAG, 1);
	return -1;
}
	
		
int sc_commandDecode (int value, int * command, int * operand) {
	if (value == NULL || command == NULL || operand == NULL) {
		sc_regSet(F_BAD, 1);
		return -1;
	}
	*operand = value & ENCODE;
	*command = value >> 8;

	return 0;
}
}

