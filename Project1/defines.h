#ifndef DEFINES_H
#define DEFINES_H

#include<iostream>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<iomanip>
#include <sys/types.h>
#include <signal.h>
#include <algorithm>
#include <map>
#include<math.h>


#define MEANCYCLES 6000
#define MEANMEM 20
#define NUMPROCESSES 7
//#define NUMPROCESSES 50
#define CONTEXTSWITCH 0
//#define CONTEXTSWITCH 10
#define NEWPROCESSCYCLES 5
//#define NEWPROCESSCYCLES 50

using namespace std;

//Structure for my processe information
typedef struct Process {
   int pid;
   float cycles;
   float mem;
}Process;

//Structure for my random number I will be generating
typedef struct RandomNumbers {
   int cycles;
   int mem;
}RandomNumbers;

#endif
