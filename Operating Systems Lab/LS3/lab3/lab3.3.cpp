#include <iostream>
#include <string>
#include <sstream>
#include "kbhit.h"
#include "Queue.cpp"

#define RR1Quanta 10
#define RR2Quanta 30

using namespace std;

class ReadyQueue
{
public:
	void insert(Node * tmp){
		switch(tmp->priority){
			case 1:
			RR1.enQueue(tmp); break;

			case 2:
			RR2.enQueue(tmp); break;

			case 3:
			FCFS.enQueue(tmp); break;
		}
	}
	
	Queue RR1, RR2, FCFS;
};

int main()
{
	// data declarations
    int ch = 0; char choice;
    ReadyQueue ready;
    string idle = "idle";
    int time = 0 ;
    stringstream gchart1, gchart2, gchart3;
    Node * exec_process = 0;
    int RR1Count = 0, RR2Count = 0, executing = 0;


    //Entering processes in ready Queueu before starting scheduler
    cout <<"Ready Queue Empy. Do you want to enter some proces initially.\nPress 'n' for no and ' any other key ' for yes"<< endl;
    cin >> choice;
    while(choice != 'n'){
    	system("clear");
        cout << "Enter PID , Burst Time, Priority. (Priority represents in which queue the proces will go, Press 1 for RR(10), 2 for RR(30), 3 for FCFS." << endl;
        Node * tmp = new Node();
        cin >> tmp->PID >> tmp->burst_time>> tmp->priority;
        if(tmp->priority <1 || tmp->priority >3){
        	cout << "Priority can't be" << tmp->priority << endl;
        	cout << "Try Agrain!" << endl;
        	sleep(1);
        	continue;
        }
        tmp->arr_time = 0;
        ready.insert(tmp);
        cout << "Do you want to enter more processes before starting Priority scheduler. \nPress 'y' for yes and any other key for no" << endl;
        cin >> choice;
    }

    system("clear");
    cout << "###########################################################################" << endl;
    cout << "Multileve Queue Scheduler started..." << endl;
    if(!ready.RR1.isEmpty()){
    	exec_process = ready.RR1.deQueue();
    	executing = 1;
    	gchart1 << "\t"<< time << " - " ;
    }
    else if(!ready.RR2.isEmpty()){
    	exec_process = ready.RR2.deQueue();
    	executing = 2;
    	gchart2 << "\t"<< time << " - " ;
    }
    else if(!ready.FCFS.isEmpty()){
    	exec_process = ready.FCFS.deQueue();
    	executing = 3;
    	gchart3 << "\t"<< time << " - " ;
    }
    cout << "Press 'q' to stop Scheduler and show Grannt Charts.\nPress 'e' to enter a process.\n0.5s is taken as 1 unit time"<< endl;
    init_keyboard();
    do {
        
        if(kbhit()) {
            ch = readch();
    
            if(ch == 'e'){
                system("clear");
                close_keyboard();

                cout << "\nEnter PID, Burst_time and Priority.(Priority represents in which queue the proces will go, Press 1 for RR(10), 2 for RR(30), 3 for FCFS." << endl;
                cout<<"(Assumption : Entering Data does not take time.)" << endl;
                Node * tmp = new Node();
                cin >> tmp->PID >> tmp->burst_time >> tmp->priority;
                tmp->arr_time =  time;
                if(tmp->priority <1 || tmp->priority >3){
        			cout << "Priority can't be" << tmp->priority << endl;
        			cout << "Try Agrain!" << endl;
        			continue;
      		    }

      		    ready.insert(tmp);
;
                init_keyboard();
                ch = 0;
                continue;
            }

            if(ch == 'q'){
                break;
            }
        }
        
        else {
            cout << "executing.....\n";
            usleep(500000);
            time++;

            if(executing == 1){
            	if(exec_process == 0) {
                gchart1 << time << "\t\t" << "idle" << endl;//<< time << " - ";
                continue;
           		}
           		RR1Count++;
            	exec_process->burst_time -= 1; 
            	if((RR1Count == RR1Quanta) || ( exec_process->burst_time == 0)){
                	RR1Count = 0;
                	gchart1 << time << "\t\t" <<exec_process->PID << endl; //<< time << " - ";
                	if(!(exec_process->burst_time == 0))
                    	ready.insert(exec_process);
                    else delete exec_process;

                    if(!ready.RR1.isEmpty()){
    					exec_process = ready.RR1.deQueue();
    					executing = 1;
    					gchart1 << "\t"<< time << " - " ;
    				}
   					else if(!ready.RR2.isEmpty()){
    					exec_process = ready.RR2.deQueue();
    					executing = 2;
    					gchart2 << "\t"<< time << " - " ;
   					}
    				else if(!ready.FCFS.isEmpty()){
    					exec_process = ready.FCFS.deQueue();
    					executing = 3;
    					gchart3 << "\t"<< time << " - " ;
    				}



                   	}
            }
            else if(executing == 2){
            	if(exec_process == 0) {
                gchart2 << time << "\t\t" << "idle" << endl; // << time << " - ";
                continue;
           		}
            	exec_process->burst_time -= 1; 
            	if((RR2Count == RR2Quanta) || ( exec_process->burst_time == 0)){
                	RR2Count = 0;
                	gchart2 << time << "\t\t" <<exec_process->PID << endl; //<< time << " - ";
                	if(!(exec_process->burst_time == 0))
                    	ready.insert(exec_process);
                    else delete exec_process;

                    if(!ready.RR1.isEmpty()){
    					exec_process = ready.RR1.deQueue();
    					executing = 1;
    					gchart1 << "\t"<< time << " - " ;
    				}
   					else if(!ready.RR2.isEmpty()){
    					exec_process = ready.RR2.deQueue();
    					executing = 2;
    					gchart2 << "\t"<< time << " - " ;
   					}
    				else if(!ready.FCFS.isEmpty()){
    					exec_process = ready.FCFS.deQueue();
    					executing = 3;
    					gchart3 << "\t"<< time << " - " ;
    				}
            	}
            }

            else if(executing == 3){
            	if(exec_process == 0) {
                gchart3 << time << "\t\t" << "idle" << endl; // << time << " - ";
                continue;
           		}
            	exec_process->burst_time -= 1; 
            	if(exec_process->burst_time == 0) {
                	gchart3 << time << "\t\t" <<exec_process->PID << endl; //<< time << " - ";
                	if(!(exec_process->burst_time == 0))
                    	ready.insert(exec_process);
                    else delete exec_process;

                     if(!ready.RR1.isEmpty()){
    					exec_process = ready.RR1.deQueue();
    					executing = 1;
    					gchart1 << "\t"<< time << " - " ;
    				}
   					else if(!ready.RR2.isEmpty()){
    					exec_process = ready.RR2.deQueue();
    					executing = 2;
    					gchart2 << "\t"<< time << " - " ;
   					}
    				else if(!ready.FCFS.isEmpty()){
    					exec_process = ready.FCFS.deQueue();
    					executing = 3;
    					gchart3 << "\t"<< time << " - " ;
    				}
            	}
            }

        }

        
    }while(1);
    close_keyboard();
    system("clear");
    cout << "grantt chart for RR with quanta 10 is " <<endl;
    cout << "******************************************************************" << endl;
    cout << "\n\tTime \t\tProcess PID\n" << endl;
	cout << gchart1.str();
    cout << "******************************************************************" << endl;

    cout << "\n\n";
    cout << "grantt chart for RR with quanta 30 is " <<endl;
    cout << "******************************************************************" << endl;
    cout << "\n\tTime \t\tProcess PID\n" << endl;
    cout << gchart2.str();
    cout << "******************************************************************" << endl;

    cout << "\n\n";
    cout << "grantt chart for FCFS is  " <<endl;
    cout << "******************************************************************" << endl;
    cout << "\n\tTime \t\tProcess PID\n" << endl;
    cout << gchart3.str();
    cout << "******************************************************************" << endl;
    cout << "\n\n";



    return (0);
}