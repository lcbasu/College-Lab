#include <iostream>
#include <string>
#include <sstream>
#include "kbhit.h"
#include "Queue.cpp"


class PriorityQueue: public Queue
{
public:
    PriorityQueue(){ head = 0, tail = 0; }
    void insert(Node * tmp){
        if(isEmpty())
            head = tail = tmp;
        else if(head == tail) {
            if(head->priority > tmp->priority){
                tail = tmp->next  = head;
                head = tmp;
            }
            else tail = head->next = tmp;
        }
        else
        {
            Node * t= head;
            if((tmp->priority) < (head->priority)){
                tmp->next = head;
                head = tmp;
            }
            else{
                while( t->next!= 0){ 
                    if((tmp->priority) > (t->next->priority)) { t = t->next;}
                    else{
                        tmp->next = t->next;
                        t->next = tmp; 
                        break; 
                    }
                }
            }
    
          if(t->next ==0){
            t->next = tmp;
            tail = tmp;
          }
        }

        tail->next = 0;
    }
};

using namespace std;
int main()
{
    int ch = 0; char choice;
    PriorityQueue ready;
    string idle = "idle";
    int time = 0 ;
    stringstream gchart;
    Node * exec_process = 0;
    cout <<"Ready Queue Empy. Do you want to enter some proces initially.\nPress 'n' for no and ' any other key ' for yes"<< endl;
    cin >> choice;
    while(choice != 'n'){
        cout << "Enter PID , Burst Time, Priority." << endl;
        Node * tmp = new Node();
        cin >> tmp->PID >> tmp->burst_time>> tmp->priority;
        tmp->arr_time = 0;
        ready.insert(tmp);
        cout << "Do you want to enter more processes before starting Priority scheduler. \nPress 'y' for yes and any other key for no" << endl;
        cin >> choice;
    }

    system("clear");
    cout << "###########################################################################" << endl;
    cout << "Priority Scheduler started..." << endl;
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

                cout << "\nEnter PID, Burst_time and Priority.(Assumption : Entering Data does not take time.)" << endl;
                Node * tmp = new Node();
                cin >> tmp->PID >> tmp->burst_time >> tmp->priority;
                tmp->arr_time =  time;

                if(tmp->burst_time > exec_process->burst_time)
                    exec_process = tmp;
                else 
                    ready.insert(tmp);
;
                init_keyboard();
                ch = 0;
                continue;
            }

            if(ch == 'q'){
                time++;
                if(exec_process->PID == 0) gchart << "\t\t" << "idle\n" ;
                else gchart << time << "\t\t" << exec_process->PID <<"\n";
                break;
            }
        }
        
        else {
            cout << "executing.....\n";
            usleep(500000);
            time++;
            if(exec_process == 0) {
                gchart << time << "\t\t" << "idle" << "\n\t" << time << " - ";
                continue;
            }

            else if((--(exec_process->burst_time)) == 0){
                gchart << time << "\t\t" <<exec_process->PID << "\n\t" << time << " - ";
                delete exec_process;
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


    return (0);
}