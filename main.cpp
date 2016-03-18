#include "defines.h"
#include "processGenerator.h"
#include "fifo.h"

int main(){
   vector<Process> set;
   createProcessSet(&set);

   /*
   vector<Process> testSet;
   Process p1; p1.cycles = 10;
   Process p2; p2.cycles = 20;
   Process p3; p3.cycles = 10;
   Process p4; p4.cycles = 5;
   Process p5; p5.cycles = 10;
   Process p6; p6.cycles = 15;
   Process p7; p7.cycles = 5;
   testSet.push_back(p1); 
   testSet.push_back(p2); 
   testSet.push_back(p3); 
   testSet.push_back(p4); 
   testSet.push_back(p5); 
   testSet.push_back(p6); 
   testSet.push_back(p7); 
   */
   runFifo(set);

   return 0;
}
