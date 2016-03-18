/*
 * NAME : Dan Jarvis
 * CLASS: CSCE 4600
 * DATE : 02/16/15
 */
#include "defines.h"
#include "processGenerator.h"

//Return float value for my adjusted mean calculations
float getAsFloat(int a, int randCycleSum, int sumCycles){
   float x = (float) a / randCycleSum;
   return x * sumCycles;
}

//Call backfunction to sort by memory in the sort function
bool cmpMem(const Process &a, const Process &b){
   return a.mem < b.mem;
}

//Call backfunction to sort by cycles in the sort function
bool cmpCyc(const Process &a, const Process &b){
   return a.cycles < b.cycles;
}

//Print a histogram of the results
void printHisto(vector<Process> set,string type){
   if(type == "mem"){
      cout << endl << "MEMORY HISTOGRAM" << endl;
      sort(set.begin(),set.end(),cmpMem);
      int j = 0;
      for(int i=0; i < 10; i++){
         int a = i*10;
         int b = a + 10;
         cout << setw(3) << a << " - " << setw(3) << b;
         while(set[j].mem >= a && set[j].mem < b && j < set.size()){
            cout << "*";
            j++;
         }
         cout << endl;
      }
      cout << endl << endl;
   } else {
      cout << endl << "CYCLES HISTOGRAM" << endl;
      sort(set.begin(),set.end(),cmpCyc);
      int j = 0;
      for(int i=0; i < 6; i++){
         int a = i*1000 + 1000;
         int b = a * 2;
         cout << setw(5) << a << " - " << setw(5) << b;
         while(set[j].cycles >= a && set[j].cycles < b && j < set.size()){
            cout << "*";
            j++;
         }
         cout << endl;
      }
      cout << endl << endl;
   }
}

//Print the set of process to the screen with a histogram
void printValues(vector<Process> set){
   printHisto(set,"cyc");
   printHisto(set,"mem");
   
   int sumCyc = 0;
   int sumMem = 0;
   cout << endl << "id   cycles   mem" << endl;
   for(int i=0; i < set.size(); i++){
      Process p = set[i];
      cout << setw(2) << p.pid << " " << setw(8) << p.cycles << " " << setw(5) << p.mem << endl;
      sumCyc += p.cycles;
      sumMem += p.mem;
   }
   cout << "MEAN CYCLES: " << sumCyc/set.size() << endl;
   cout << "MEAN MEMROY: " << sumMem/set.size() << endl;

}

//Generate random numbers. The mean of these numbers will not be correct after this function
//but I will adjust it to the proper numbers for memeory and cycles when I put it in the final set
void generateRandomNumbers(vector<RandomNumbers> *rNums, int p, int *c, int *m){
   for(int j=0; j < p; j++){
      RandomNumbers rn;
      int r = int((rand() + 1000) % 11000);
      int t = int((rand() + 1) % 100);
      *c += r;
      *m += t;
      rn.cycles = r;
      rn.mem = t;
      rNums->push_back(rn);
   }

}

//This function generates the set of processes with the appropriate mean for both the cycles
//and the memory. I save an "excess" variable to ensure not numbers are less than or greater
//than the required minimum and maximum for both memeory and cycles
void generateSet(vector<Process> *set, vector<RandomNumbers> *rNums,int rc,int sc,int rm, int sm){
   int excessCycles = 0; int excessMem = 0;
   for(int i=0; i < rNums->size(); i++){
     Process p;
     p.pid = i + 1;

     if(excessCycles != 0){
        p.cycles = int(getAsFloat((*rNums)[i].cycles,rc,sc) + 0.5);
        p.cycles += excessCycles; 
        excessCycles = 0;
     } else {
        p.cycles = int(getAsFloat((*rNums)[i].cycles,rc,sc) + 0.5);
     }
     if(p.cycles < 1000){
        excessCycles = 1000 - p.cycles;
        p.cycles += excessCycles;
        excessCycles *= -1;
     } else if(p.cycles > 11000){
        excessCycles = p.cycles - 11000;
        p.cycles += excessCycles * - 1;
     }

     if(excessMem != 0){
        p.mem = int(getAsFloat((*rNums)[i].mem,rm,sm) + 0.5);
        p.mem += excessMem;
        excessMem = 0;
     } else {
        p.mem = int(getAsFloat((*rNums)[i].mem,rm,sm) + 0.5);
     }
     if(p.mem < 1){
        excessMem = 1 - p.mem;
        p.mem += excessMem;
        excessMem *= -1; 
     } else if (p.mem > 100){
        excessMem = p.mem - 100;
        p.mem += excessMem * -1;
     }
     set->push_back(p);  
   }

   //This is here just incase the excessCycles or memeory run over from the very
   //last process created
   int i = 0;
   while(i < set->size() && excessCycles !=0){
      (*set)[i].cycles += excessCycles;
      excessCycles = 0;
      if((*set)[i].cycles > 11000){
        excessCycles = (*set)[i].cycles - 11000;
        (*set)[i].cycles += excessCycles * -1;
      }
      i++;
   }
   i = 0;
   while(i < set->size() && excessMem !=0) {
      (*set)[i].mem += excessMem;
      excessMem = 0;
      if((*set)[i].mem > 100) {
        excessMem = (*set)[i].mem - 100;
        (*set)[i].mem += excessMem * -1;
      }
      i++;
   }
}

void createProcessSet(vector<Process> *set){
   int numProcesses = NUMPROCESSES;
   srand(time(NULL)); //Seed rand

   //This is just moving values in the equation mean = sum / n to get this
   //formula mean * n = sum. That way later on I can assign random numbers based on that sum
   int sumCycles = numProcesses * MEANCYCLES;
   int sumMem = numProcesses * MEANMEM;

   //Generate my random set of number to be used for my process values
   int randCycleSum = 0;
   int randMemSum = 0;
   vector<RandomNumbers> rNums;
   generateRandomNumbers(&rNums,numProcesses,&randCycleSum,&randMemSum);

   //Generate the set of processes with the appropriate mean value for memeory and cycle number
   generateSet(set,&rNums,randCycleSum,sumCycles,randMemSum,sumMem);

}
