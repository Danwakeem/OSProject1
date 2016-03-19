#ifndef FIFO_H
#define FIFO_H
#include "defines.h"
#include <sys/time.h>

typedef struct ReturnFIFO {
   vector<int> totalWait;
   int totalWaitTimes;
   int totalCycles;
   int totalContextSwitches;
}ReturnFIFO;

void runFifoOnce(vector<Process> set);
void runFifoAsThread(vector<Process> set);
ReturnFIFO runFifo(vector<Process> set);
void printCSV(vector<Process> set, vector<int> totalWait);
void printFifoData(vector<Process> set, int talliedWait, vector<int> processWaitTime, int totalCycles);
void printHistogram(vector<Process> set, int totalCycles);
ReturnFIFO createReturnFIFO(vector<int> tw, int twt, int tc, int tcs);

#endif
