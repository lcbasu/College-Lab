#include<iostream>
#include<fstream>
#include<cstdlib>
#include "Scheduler.cpp"

using namespace std;

int main()
{
    int pid = 0, b_time = 0, a_time = 0, priority = 0;
    int choice, quantum;
    int counter = 0;
    cout<<"Menu : (0:Round-Robin, 1:Priority, 2:Multilevel Feedback Queue, 3:Exit): ";
    cin>>choice;
    while(choice != 3)
    {
        switch(choice)
        {
            case 0:
            {
            Queue JobQ; Scheduler S;
            ifstream fin_1("process_RR.txt", ios::in);
            if( !fin_1.is_open() )
                {
                    cout<<"The processes could not be read!!"<<endl;
                    return 0;
                }
                else
                {
                    string word;
                    while(fin_1>>word)
                    {
                        if(counter == 0)
                            pid = atoi(word.c_str());
                        else if(counter == 2)
                            a_time = atoi(word.c_str());
                        else if(counter == 3)
                            b_time = atoi(word.c_str());
                        else if(counter == 4)
                            priority = atoi(word.c_str());
                        counter = counter + 1;
                        if( (counter % 5 == 0) && (counter != 0) )
                        {
                            Node *newNode = new Node;
                            newNode->set_PID(pid);
                            newNode->set_PName("default");
                            newNode->set_arrival_time(a_time);
                            newNode->set_burst_time(b_time);
                            newNode->set_priority(priority);
                            newNode->set_next(NULL);
                            JobQ.enQ(newNode);
                            counter = 0;
                        }
                    }
                }
                fin_1.close();

                cout<<"\n\nThe contents of the Job Queue are: "<<endl;
                JobQ.displayQ();
                cout<<"\nEnter the time quantum of the RR scheduler: ";
                cin>>quantum;
                S.init(JobQ);
                S.RR_Scheduling(quantum);
                break;
            }

            case 1:
            {
            Queue JobQ; Scheduler S;
            ifstream fin_2("process_priority.txt", ios::in);
            if( !fin_2.is_open() )
                {
                    cout<<"The processes could not be read!!"<<endl;
                    return 0;
                }
                else
                {
                    string word;
                    while(fin_2>>word)
                    {
                        if(counter == 0)
                            pid = atoi(word.c_str());
                        else if(counter == 2)
                            a_time = atoi(word.c_str());
                        else if(counter == 3)
                            b_time = atoi(word.c_str());
                        else if(counter == 4)
                            priority = atoi(word.c_str());
                        counter = counter + 1;
                        if(counter % 5 == 0)
                        {
                            Node *newNode = new Node;
                            newNode->set_PID(pid);
                            newNode->set_PName("default");
                            newNode->set_arrival_time(a_time);
                            newNode->set_burst_time(b_time);
                            newNode->set_priority(priority);
                            newNode->set_next(NULL);
                            JobQ.enQ(newNode);
                            counter = 0;
                        }
                    }
                }
                fin_2.close();

                cout<<"\n\nThe contents of the Job Queue are: "<<endl;
                JobQ.displayQ();
                S.init(JobQ);
                S.Priority_Scheduling();
                break;
            }

            case 2:
            {
            Queue JobQ; Scheduler S;
            ifstream fin_3("process_multilevel.txt", ios::in);
            if( !fin_3.is_open() )
                {
                    cout<<"The processes could not be read!!"<<endl;
                    return 0;
                }
                else
                {
                    string word;
                    while(fin_3>>word)
                    {
                        if(counter == 0)
                            pid = atoi(word.c_str());
                        else if(counter == 2)
                            a_time = atoi(word.c_str());
                        else if(counter == 3)
                            b_time = atoi(word.c_str());
                        else if(counter == 4)
                            priority = atoi(word.c_str());
                        counter = counter + 1;
                        if(counter % 5 == 0)
                        {
                            Node *newNode = new Node;
                            newNode->set_PID(pid);
                            newNode->set_PName("default");
                            newNode->set_arrival_time(a_time);
                            newNode->set_burst_time(b_time);
                            newNode->set_priority(priority);
                            newNode->set_next(NULL);
                            JobQ.enQ(newNode);
                            counter = 0;
                        }
                    }
                }
                fin_3.close();

                cout<<"\n\nThe contents of the Job Queue are: "<<endl;
                JobQ.displayQ();
                S.init(JobQ);
                S.Multilevel_Scheduling();
                break;
            }

            default:
                cout<<"Wrong choice...Please enter a number between 0 - 3"<<endl;
                break;
        }

        cout<<endl<<endl;
        cout<<"Enter your choice of scheduler: (0:Round-Robin, 1:Priority, 2:Multilevel Feedback Queue, 3:Exit): ";
        cin>>choice;
    }

    cin.get();
    cin.ignore();
    return 0;
}
