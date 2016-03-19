#ifndef SJF_H
#define SJF_H
#include "defines.h"

typedef struct Runtime {
   Process p;
   int cycleTimeWhenCreated;
   int waitTime;
}Rumtime;

typedef struct ReturnSJF{
   vector<Runtime> q;
   int totalCycleTime;
   int totalContextSwitches;
}ReturnSJF;

void runSJFOnce(vector<Process> set);
void runSJFAsThread(vector<Process> set);
ReturnSJF runSJF(vector<Process> set);
void printHistogram(vector<Runtime> final, int totalCycleTime);
void printCSV(vector<Runtime>final, int totalCycleTime);
bool cmpPid(const Runtime &a, const Runtime &b);
bool cmpRuntimes(const Runtime &a, const Runtime &b);
Runtime createNewRuntime(Process p, int cycleTime);
ReturnSJF createReturnSJF(vector<Runtime> q, int totalCycleTime, int totalContextSwitches);

#endif
