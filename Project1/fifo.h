#ifndef FIFO_H
#define FIFO_H
#include "defines.h"
#include <sys/time.h>

void runFifo(vector<Process> set);
void printFifoData(vector<Process> set, int talliedWait, vector<int> processWaitTime, int totalCycles);
void printHistogram(vector<Process> set, int totalCycles);

#endif
