#include "sjf.h"

void runSJFOnce(vector<Process> set){
   ReturnSJF r = runSJF(set);
   vector<Runtime> finalQueue = r.q;
   int totalContextSwitches = r.totalContextSwitches;
   int totalCycleTime = r.totalCycleTime;

   int totalWaitTime = 0;
   for(int i = 0; i < finalQueue.size(); i++){
      totalWaitTime += finalQueue[i].waitTime;
      //cout << finalQueue[i].p.pid << " " << finalQueue[i].waitTime << endl;
   }
   cout << "Average wait time for SJF is: " << totalWaitTime / set.size() << endl;
   cout << "There were " << totalContextSwitches - 1 << " context switches for SJF with a penalty of " << (totalContextSwitches-1)*CONTEXTSWITCH << " cycles" << endl;

   cout << endl;
   printCSV(finalQueue,totalCycleTime);
}

void runAsThread(vector<Process> set){
   //Here we might be able to split the set into 4 and run the run function 4 times
   //instead of creating threads
}

ReturnSJF runSJF(vector<Process> set){
   vector<Runtime> queue;
   vector<Runtime> finalQueue;
   int totalCycleTime = 0;
   int totalContextSwitches = 0;
   int index = 0;   
   int fqIndex = 0;
   int removed = 0;

   queue.push_back(createNewRuntime(set[index++],totalCycleTime));

   while(finalQueue.size() != set.size()){
      //Save wait time for process
      queue[0].waitTime = totalCycleTime - queue[0].cycleTimeWhenCreated;

      int cycles = totalCycleTime;
      //Add new processes to the queue
      if(index < set.size()){
         int newProcessCount = queue[0].p.cycles / NEWPROCESSCYCLES; 
         for(int i = 0; i < newProcessCount; i++){
            cycles += NEWPROCESSCYCLES;
            queue.push_back(createNewRuntime(set[index++],cycles));
            if(index >= set.size()) break;
         }
      }

      totalCycleTime += queue[0].p.cycles + CONTEXTSWITCH;
      //Move current process to the finalQueue
      finalQueue.push_back(queue[0]);
      queue.erase(queue.begin()); //Remove from queue
      totalContextSwitches++;
      //Sort queue from least cycles to most cycles
      sort(queue.begin(),queue.end(),cmpRuntimes); 
   } 


   return createReturnSJF(finalQueue,totalCycleTime,totalContextSwitches);

}

void printHistogram(vector<Runtime> final, int totalCycleTime){
   cout << "         Graphical histogram for SJF process cycles" << endl;
   cout << "           * = 0.1% of cycles    v. total cycles" << endl;
   cout << "           # = 0.1% of wait time v .total cycles" << endl;
   cout << "    -------------------------------------------------------" << endl;
   for(int i = 0; i < final.size(); i++){
      float percent = final[i].p.cycles / totalCycleTime * 100;
      percent = floor(percent * 10.00 + 0.5) / 10.00;
      cout << setw(2) << final[i].p.pid << " | ";
      do {
         cout << "*";
         percent -= 0.1;
      }while(percent >=0);
      cout << endl << "   | ";
      percent = final[i].waitTime / totalCycleTime * 100;
      percent = floor(percent * 10.0 + 0.5) / 10.0;
      do{
         cout << "#";
         percent -= 0.1;
      }while(percent >= 0);
      cout << endl;
   }
}

void printCSV(vector<Runtime>final, int totalCycleTime){
   sort(final.begin(),final.end(),cmpPid);
   for(int i = 0; i < final.size(); i++){
      cout << final[i].p.pid << "," << final[i].waitTime << "," << final[i].p.cycles << endl;
   }
}

bool cmpPid(const Runtime &a, const Runtime &b){
   return a.p.pid < b.p.pid;
}

//Sort by shortest cycles
bool cmpRuntimes(const Runtime &a, const Runtime &b) {
   return a.p.cycles < b.p.cycles;
}

ReturnSJF createReturnSJF(vector<Runtime> q, int totalCycleTime, int totalContextSwitches){
   ReturnSJF r;
   r.q = q;
   r.totalCycleTime = totalCycleTime;
   r.totalContextSwitches = totalContextSwitches;
   return r;
}

Runtime createNewRuntime(Process p, int cycleTime){
   Runtime r;
   r.p = p;
   r.cycleTimeWhenCreated = cycleTime;
   r.waitTime = 0;
   return r;
}
