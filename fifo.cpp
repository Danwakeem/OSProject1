#include "fifo.h"

void runFifo(vector<Process> set){
  vector<int> waitPenalty;
  vector<int> totalWait;
  int totalWaitTimes = 0;
  int totalCycles = 0;
  int offSet = 0;
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
  }

  float averageWaitTime = totalWaitTimes / set.size();
  cout << "Average wait time was: " << averageWaitTime << " cycles" << endl;

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
