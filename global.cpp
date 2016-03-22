#include "defines.h"

vector< vector<Process> > breakIntoSubSet(vector<Process> set){

   vector< vector<Process> > sets(NUMCPU);
   for(int i = 0; i < set.size(); i++){
      sets[i % NUMCPU].push_back(set[i]);
   }

   return sets;
}

void printContextSwitchInfo(int totalSwitches, int totalCycles){
   cout << "Context Switches," << totalSwitches << endl;
   cout << "Other Cycles," << totalCycles - totalSwitches << endl << endl;
}
