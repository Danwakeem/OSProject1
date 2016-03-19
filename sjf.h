#ifndef SJF_H
#define SJF_H
#include "defines.h"

typedef struct Runtime {
   Process p;
   int cycleTimeWhenCreated;
   int waitTime;
}Rumtime;

void runSJF(vector<Process> set);
bool cmpRuntimes(const Runtime &a, const Runtime &b);
Runtime createNewRuntime(Process p, int cycleTime);

#endif
