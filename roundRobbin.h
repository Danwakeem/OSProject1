#ifndef ROUNDROBBIN_H
#define ROUNDROBBIN_H
#include "defines.h"

typedef struct Robbin {
   Process p;
   int cyclesRemaining;
   int lastCycleCount;
   int totalWaitTime;
}Robbin;

void runRoundRobbin(vector<Process> set);
Robbin createNewRobbin(Process p, int cycleCount);

#endif
