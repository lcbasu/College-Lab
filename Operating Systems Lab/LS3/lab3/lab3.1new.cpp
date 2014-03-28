#include <iostream>
#include <string>
#include <sstream>
#include "kbhit.h"
#include "Queue.cpp"
#define quanta 3

using namespace std;
int main()
{
    int ch = 0; char choice;
    Queue ready;
    string idle = "idle";
    int time = 0, counter = 0;
    stringstream gchart;
    Node * exec_process = 0;
    cout <<"Ready Queue Empy. Do you want to enter some proces initially.\nPress 'n' for no and ' any other key ' for yes"<< endl;
    cin >> choice;
    while(choice != 'n'){
        cout << "Enter PID and Burst Time" << endl;
        Node * tmp = new Node();
        cin >> tmp->PID >> tmp->burst_time;
        tmp->arr_time = 0;
        ready.enQueue(tmp);
        cout << "Do you want to enter more processes before starting RR scheduler. \nPress 'y' for yes and any other key for no" << endl;
        cin >> choice;
    }

    system("clear");
    cout << "###########################################################################" << endl;
    cout << "Round Robin Scheduler started..." << endl;
    if(!ready.isEmpty())exec_process = ready.deQueue();
    gchart << "\t"<< time << " - " ;
    cout << "Press 'q' to stop Scheduler and show Grannt Chart.\nPress 'e' to enter a process.\n0.5s is taken as 1 unit time"<< endl;
    init_keyboard();
    do {
        
        if(kbhit()) {
            ch = readch();
    
            if(ch == 'e'){
                system("clear");
                close_keyboard();
                cout << "\nEnter PID and burst_time.(Assumption : Entering Data does not take time.)" << endl;
                Node * tmp = new Node();
                cin >> tmp->PID >> tmp->burst_time;
                tmp->arr_time =  time;
                ready.enQueue(tmp);
                init_keyboard();
                ch = 0;
                continue;
            }

            if(ch == 'q'){
                if(exec_process->PID == 0) gchart << "\t\t" << "idle\n" ;
                else gchart << time << "\t\t" <<exec_process->PID <<"\n";

                break;
            }
        }
        
        else {
            cout << "executing.....\n";
            usleep(500000);
            counter++;
            time++;
            if(exec_process == 0) {
                gchart << time << "\t\t" << "idle" << "\n\t" << time << " - ";
                continue;
            }
            exec_process->burst_time -= 1; 
            if((counter == quanta) || ( exec_process->burst_time == 0)){
                counter = 0;
                gchart << time << "\t\t" <<exec_process->PID << "\n\t" << time << " - ";
                if(!(exec_process->burst_time == 0))
                    ready.enQueue(exec_process);
                exec_process = ready.deQueue();
            }

        }

        
    }while(1);
    close_keyboard();
    system("clear");
    cout << "grantt chart for input process is " <<endl;
    cout << "******************************************************************" << endl;
    cout << "\n\tTime \t\tProcess PID\n" << endl;
    cout << gchart.str();


    system("pause");
    return 0;
    exit(0);
}

