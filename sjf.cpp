#include "sjf.h"

void runSJF(vector<Process> set){
   vector<Runtime> queue;
   vector<Runtime> finalQueue;
   int totalCycleTime = 0;
   int index = 0;   
   int fqIndex = 0;
   int removed = 0;

   queue.push_back(createNewRuntime(set[index++],totalCycleTime));

   while(finalQueue.size() != set.size()){
      //Save wait time for process
      queue[0].waitTime = totalCycleTime - queue[0].cycleTimeWhenCreated;

      //Add new processes to the queue
      if(index < set.size()){
         int newProcessCount = queue[0].p.cycles / NEWPROCESSCYCLES; 
         for(int i = 0; i < newProcessCount; i++){
            totalCycleTime += NEWPROCESSCYCLES;
            queue.push_back(createNewRuntime(set[index++],totalCycleTime));
            if(index >= set.size()) break;
         }
      }

      //Move current process to the finalQueue
      finalQueue.push_back(queue[0]);
      queue.erase(queue.begin()); //Remove from queue
      totalCycleTime += CONTEXTSWITCH;
      //Sort queue from least cycles to most cycles
      sort(queue.begin(),queue.end(),cmpRuntimes); 
   } 

   for(int i = 0; i < finalQueue.size(); i++){
      cout << finalQueue[i].p.pid << " " << finalQueue[i].waitTime << endl;
   }

}

//Sort by shortest cycles
bool cmpRuntimes(const Runtime &a, const Runtime &b) {
   return a.p.cycles < b.p.cycles;
}

Runtime createNewRuntime(Process p, int cycleTime){
   Runtime r;
   r.p = p;
   r.cycleTimeWhenCreated = cycleTime;
   r.waitTime = 0;
   return r;
}
