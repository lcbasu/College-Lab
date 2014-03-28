  #include<iostream>

  using namespace std;

  struct process{
      int pId ;
      int burstTime ;
  };

  int main(){
      int numberOfProcesses;

      //number of process
      cout << "\nNUMBER OF PROCESS: ";
      cin >> numberOfProcesses;

      struct process p[numberOfProcesses];
      struct process temp;
      int i;
      int j;
      int waitingTime = 0;
      float totalWaitingTime = 0;

      //burst time
      for(i=0; i<numberOfProcesses; i++){
          p[i].pId = i+1 ;
          cout << "================================\n";
          cout << "PROCESS " << i+1 << "\n";
          cout << "\tBURST TIME: ";
          cin >> p[i].burstTime;
          totalWaitingTime += p[i].burstTime;
      }

      //using Insertion sort
      for(i=0; i<numberOfProcesses; i++){
          for(j=0; j<numberOfProcesses; j++){
              if(p[j].burstTime>p[i].burstTime){
                  temp = p[i];
                  p[i] = p[j] ;
                  p[j] = temp;
              }
         }
      }

      //display
      cout << "\n========================================================\n";
      cout << "     PROCESS\t    BURST TIME\t   WAITING TIME\n\n";
      for(i=0;i<numberOfProcesses;i++){
          cout <<"\tP" << p[i].pId << "\t\t" << p[i].burstTime;
          cout << "\t\t" << waitingTime << "\n";
          waitingTime = waitingTime + p[i].burstTime ;
      }
     cout << "========================================================\n";

      //average waiting time
      cout << "AVERAGE WAITING TIME = ";
      cout << totalWaitingTime/numberOfProcesses << "\n\n" ;
      return 0;
  }
