#include "roundRobbin.h"

void runRoundRobbinOnce(vector<Process> set){
   cout << "****** Round-Robin DATA SET ******" << endl;
   ReturnRR r = runRoundRobbin(set);
   vector<Robbin> queue = r.q;
   int penaltyCount = r.totalContextSwitches; 
   int totalCycles = r.totalCycles; 

   //Sum all of the wait times calculate the wait time
   int sumOfWaitTimes = 0;
   for(int i = 0; i < queue.size(); i++){
      Robbin r = queue[i];
      sumOfWaitTimes += r.totalWaitTime;
   }
   cout << "Average wait time for round robbin was: " << sumOfWaitTimes / set.size() << endl;
   cout << "There were: " << penaltyCount << " context switches for round robbin with a penalty of: " << penaltyCount * CONTEXTSWITCH << " cycles" << endl;
   cout << endl;
   printCSV(queue);

   printContextSwitchInfo(penaltyCount,totalCycles);

}

void runRoundRobbinAsThread(vector<Process> set){
   //Here we might be able to split the set into 4 and run the run function 4 times
   //instead of creating threads
   vector< vector<Process> > sets = breakIntoSubSet(set);
   vector<Robbin> combinedRobbins;

   //Run SJF for 4 different CPUs on a sub set of the total sets
   int averageWaitTimeSum = 0;
   int totalContextSwitches = 0;
   int totalCycles = 0;

   for(int i = 0; i < NUMCPU; i++){
      ReturnRR r = runRoundRobbin(sets[i]);

      //Calculate average wait time for each CPU Round Robbin
      int totalWaitTimes = 0;
      for(int j = 0; j < r.q.size(); j++){
         combinedRobbins.push_back(r.q[j]);
         totalWaitTimes += r.q[j].totalWaitTime;
      }
      averageWaitTimeSum += totalWaitTimes/r.q.size();
      totalContextSwitches += r.totalContextSwitches;
      totalCycles = r.totalCycles;
   }

   cout << "Average wait time for threaded Round Robbin was " << averageWaitTimeSum / NUMCPU << endl;
   cout << "Average context switches for threaded Round Robbin was " << totalContextSwitches / NUMCPU << endl;

   sort(combinedRobbins.begin(),combinedRobbins.end(),cmpPid);
   cout << endl << "Multi CPU wait times" << endl;
   printCSV(combinedRobbins);

   printContextSwitchInfo(totalContextSwitches*CONTEXTSWITCH,totalCycles);
}

bool cmpPid(const Robbin &a, const Robbin &b){
   return a.p.pid < b.p.pid;
}

ReturnRR runRoundRobbin(vector<Process> set){
   vector<Robbin> queue; //Round robbin queue
   int index = 0; //This keeps track of index in original set
   int vIndex = 0; //I tired using an iterator but accessing elements in the vector from an index is easier because the vector address space is reset when you add elements
   int quantum = ROBBINQUANTUM; //Quantum variable because it can be increase if a process doesnt use all of its quantam
   int cycleCount = 0; //Count of total cycles
   int removed = 0; //Keep track of how many proccess have been removed from the round robbin queue
   int penaltyCount = 0;

   queue.push_back(createNewRobbin(set[index++],cycleCount));
   vector<Robbin>::iterator it = queue.begin();
    

   while(removed < set.size() - 1){
      Robbin *r = &queue[vIndex];
      r->cyclesRemaining -= quantum; //Subtract time quantum from cycles remaining
      r->totalWaitTime += cycleCount - r->lastCycleCount; //Get the number of cycles waited
      cycleCount += ROBBINQUANTUM + CONTEXTSWITCH; //Update the cycle count total
      r->lastCycleCount = cycleCount; //set last cycle count for the process
      quantum = ROBBINQUANTUM; //Reset the time quantum

      //Add new process to the round robbin queue
      if(index < set.size()){
         queue.push_back(createNewRobbin(set[index++],cycleCount));
      }

      //Add the aditional cycles to next proccesses quantum time
      if(queue[vIndex].cyclesRemaining <= 0){ 
         removed++;
         quantum += queue[vIndex].cyclesRemaining * -1;
      }     

      //Move to next active process in the queue
      int count = 0;
      do{
         if(vIndex == queue.size() - 1)
            vIndex = -1;
         vIndex++; count++;
      }while(queue[vIndex].cyclesRemaining <= 0 && count < queue.size());
      penaltyCount++; 
   }

   return createReturnRR(queue,cycleCount,penaltyCount);

}

void printCSV(vector<Robbin>queue){
   for(int i = 0; i < queue.size(); i++){
      cout << queue[i].p.pid << "," << queue[i].totalWaitTime << "," << queue[i].p.cycles << endl;
   }
}

//Function to make it easier to create a new robbin process for the vector
Robbin createNewRobbin(Process p, int cycleCount){
   Robbin r;
   r.p = p;
   r.cyclesRemaining = p.cycles;
   r.lastCycleCount = cycleCount;
   r.totalWaitTime = 0;
   return r;
}

ReturnRR createReturnRR(vector<Robbin> q, int totalCycles, int totalContextSwitches){
   ReturnRR r;
   r.q = q;
   r.totalCycles = totalCycles;
   r.totalContextSwitches = totalContextSwitches;
   return r;
}
