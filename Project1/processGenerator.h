#ifndef PROCESSGEN_H
#define PROCESSGEN_H
#include "defines.h"

float getAsFloat(int a, int randCycleSum, int sumCycles);
bool cmpMem(const Process &a, const Process &b);
bool cmpCyc(const Process &a, const Process &b);
void printHisto(vector<Process> set, string type);
void printValues(vector<Process>set);
void generateRandomNumbers(vector<RandomNumbers> *rNums, int p, int *c, int *m);
void generateSet(vector<Process>*set,vector<RandomNumbers>*rNums,int rc, int sc, int rm, int sm);
void createProcessSet(vector<Process> *set);

#endif
