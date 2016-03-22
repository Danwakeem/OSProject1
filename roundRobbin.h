#ifndef ROUNDROBBIN_H
#define ROUNDROBBIN_H
#include "defines.h"

typedef struct Robbin {
   Process p;
   int cyclesRemaining;
   int lastCycleCount;
   int totalWaitTime;
}Robbin;

typedef struct ReturnRR{
   vector<Robbin> q;
   int totalCycles;
   int totalContextSwitches;
}ReturnRR;

void runRoundRobbinOnce(vector<Process> set);
void runRoundRobbinAsThread(vector<Process> set);
ReturnRR runRoundRobbin(vector<Process> set);
void printCSV(vector<Robbin>queue);
bool cmpPid(const Robbin &a, const Robbin &b);
Robbin createNewRobbin(Process p, int cycleCount);
ReturnRR createReturnRR(vector<Robbin> q, int totalCycles, int totalContextSwitches);

#endif
