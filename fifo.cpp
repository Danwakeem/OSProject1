#include "fifo.h"

void runFifoOnce(vector<Process> set){
   ReturnFIFO r = runFifo(set);
   int totalWaitTimes = r. totalWaitTimes;
   vector<int> totalWait= r.totalWait;
   int totalCycles = r.totalCycles;
   int totalContextSwitches = r.totalContextSwitches;
 
   float averageWaitTime = totalWaitTimes / set.size();
   cout << "Average wait time for FIFO was: " << averageWaitTime << " cycles" << endl;
   cout << "There were " << totalContextSwitches - 1 << " context switches for FIFO with a penalty of " << (totalContextSwitches-1)*CONTEXTSWITCH << " cycles " << endl;
   cout << endl;
   printCSV(set,totalWait);
   cout << endl;
}

void runFifoAsThread(vector<Process> set){
   //Here we might be able to split the set into 4 and run the run function 4 times
   //instead of creating threads
   vector< vector<Process> > sets = breakIntoSubSet(set);

   int averageWaitTimeSum = 0; //Store total wait time
   int totalContextSwitches = 0; //Store total context switches

   //Run FIFO for 4 different CPUs on a sub set of the total sets
   for(int i = 0; i < NUMCPU; i++){
      ReturnFIFO r = runFifo(sets[i]);
      averageWaitTimeSum += r.totalWaitTimes / sets[i].size();
      totalContextSwitches += r.totalContextSwitches;
   }

   //Print averages
   cout << "Average wait time for threaded FIFO was " << averageWaitTimeSum / NUMCPU << endl;
   cout << "Average context switches for threaded FIFO was " << totalContextSwitches / NUMCPU << endl << endl;
}

ReturnFIFO runFifo(vector<Process> set){
  vector<int> waitPenalty;
  vector<int> totalWait;
  int totalWaitTimes = 0;
  int totalCycles = 0;
  int offSet = 0;
  int totalContextSwitches = 0;

  for(int i = 0; i < set.size(); i++){
     Process p = set[i];
     if(i == 0){
        totalCycles += p.cycles;
        totalWait.push_back(0);
     } else {
        int wait = totalCycles - waitPenalty[offSet++];
        totalCycles += p.cycles + CONTEXTSWITCH;
        totalWait.push_back(wait);
        totalWaitTimes += wait;
     }
     if(waitPenalty.size() < NUMPROCESSES) {
        int penalties = (p.cycles / NEWPROCESSCYCLES);
        for(int j = 0; j < penalties; j++){
           if(waitPenalty.size() != 0 && offSet != waitPenalty.size()){
              int pen = waitPenalty[waitPenalty.size()-1] + NEWPROCESSCYCLES;
              waitPenalty.push_back(pen);
           } else {
              waitPenalty.push_back((j+1)*NEWPROCESSCYCLES);
           }
        }
     }
     totalContextSwitches++;
  }

  return createReturnFIFO(totalWait,totalWaitTimes,totalCycles,totalContextSwitches);
}

void printCSV(vector<Process> set,vector<int> totalWait){
   for(int i = 0; i < set.size(); i++){
      cout << set[i].pid << "," << totalWait[i] << "," << set[i].cycles << endl;
   }
}

void printFifoData(vector<Process> set, int talliedWait, vector<int> processWaitTime,int totalCycles){
   //Print Graph
   cout << "PID   waitTime    %" << endl;
   for(int i = 0; i < processWaitTime.size(); i++){
      int time = processWaitTime[i];
      int timeScale = time / 1000;
      cout << setw(3) << i + 1 << " " << setw(10) << processWaitTime[i] << " " << setw(5) << set[i].cycles / totalCycles << endl;
   }
   cout << "Average wait time was " << talliedWait / set.size() << " cycles" << endl;
}

void printHistogram(vector<Process> set, int totalCycles){
   cout << "          Graphical histogram for fifo process cycles" << endl;
   cout << "                  * = 0.1% of total cycles" << endl;
   cout << "    -------------------------------------------------------" << endl;
   for(int i = 0; i < set.size(); i++){
      float percent = set[i].cycles / totalCycles * 100;
      percent = floor(percent * 10.00 + 0.5) / 10.00;
      cout << setw(2) << set[i].pid << " | ";
      do{
         cout << "*";
         percent -= 0.1;
      }while(percent >= 0); 
      cout << endl;
   }
   cout << "    -------------------------------------------------------" << endl;
}

ReturnFIFO createReturnFIFO(vector<int> tw, int twt, int tc, int tcs){
   ReturnFIFO r;
   r.totalWait = tw;
   r.totalWaitTimes = twt;
   r.totalCycles = tc;
   r.totalContextSwitches = tcs;
   return r;
}
