#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H

#define F_FENCE 1
#define F_BAD 2
#define FLAG3 3
#define FLAG4 4
#define FLAG5 5

int mass[100];
int commArr[38];
int regf;


int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
int sc_regInit(void);
int sc_regSet(int, int);
int sc_regGet(int, int);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);

#endif
