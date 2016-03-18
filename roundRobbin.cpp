#include "roundRobbin.h"

void runRoundRobbin(vector<Process> set){
   vector<Robbin> queue; //Round robbin queue
   int index = 0; //This keeps track of index in original set
   int vIndex = 0; //I tired using an iterator but accessing elements in the vector from an index is easier because the vector address space is reset when you add elements
   int quantum = ROBBINQUANTUM; //Quantum variable because it can be increase if a process doesnt use all of its quantam
   int cycleCount = 0; //Count of total cycles
   int removed = 0; //Keep track of how many proccess have been removed from the round robbin queue

   queue.push_back(createNewRobbin(set[index++],cycleCount));
   vector<Robbin>::iterator it = queue.begin();
    

   while(removed < set.size() - 1){
      Robbin *r = &queue[vIndex];
      r->cyclesRemaining -= quantum; //Subtract time quantum from cycles remaining
      r->totalWaitTime += cycleCount - r->lastCycleCount; //Get the number of cycles waited
      cycleCount += ROBBINQUANTUM; //Update the cycle count total
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
   }

   //Sum all of the wait times calculate the wait time
   int sumOfWaitTimes = 0;
   for(int i = 0; i < queue.size(); i++){
      Robbin r = queue[i];
      sumOfWaitTimes += r.totalWaitTime;
   }
   cout << "Average wait time for round robbin is: " << sumOfWaitTimes / set.size() << endl;

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
