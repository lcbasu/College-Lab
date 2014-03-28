#include <iostream>
#include <vector>
#include <iomanip>

#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Queue.cpp"

class Scheduler
{
    private:
        Queue ReadyQ;

    public:
        void init(Queue);
        void RR_Scheduling(int);
        void Priority_Scheduling();
        void Multilevel_Scheduling();
        void displayChart();
};

#endif


void Scheduler::init(Queue inputQ)
{
    ReadyQ = inputQ;
}

void Scheduler::RR_Scheduling(int quantum)
{
    int time = 0;
    vector<int> gantt_chart;
    vector<int> start_time;
    vector<int> end_time;

    while( !ReadyQ.isEmpty() )
    {
        Node *sch_process = ReadyQ.deQ();
        if( sch_process->return_burst_time() >= quantum )
        {
            gantt_chart.push_back(sch_process->return_PID());
            start_time.push_back(time);
            end_time.push_back(time + quantum);
            //cout<<right<<setw(20)<<"from t = "<<time<<" to t = "<<time + quantum<<endl;

            time += quantum;
            int curr_bt = sch_process->return_burst_time();
            sch_process->set_burst_time(curr_bt - quantum);

            if(sch_process->return_burst_time() != 0)
            {
                sch_process->set_next(NULL);
                ReadyQ.enQ(sch_process);
            }
        }
        else
        {
            gantt_chart.push_back(sch_process->return_PID());
            start_time.push_back(time);
            end_time.push_back(time + sch_process->return_burst_time());
            //cout<<right<<setw(20)<<"from t = "<<time<<" to t = "<<time + sch_process->return_burst_time()<<endl<<endl;
            time += sch_process->return_burst_time();
        }
    }

    //Displaying Gantt Chart
    for(int i=0; i<gantt_chart.size(); i++)
        cout<<"-------------";
    cout<<endl;

    for(int i=0; i<gantt_chart.size(); i++)
        cout<<"PID: "<<gantt_chart[i]<<"  |  ";
    cout<<endl;

    for(int i=0; i<gantt_chart.size(); i++)
        cout<<"-------------";
    cout<<endl;

    for(int i=0; i<gantt_chart.size(); i++)
    {
        cout<<start_time[i]<<"           ";
    }
    cout<<end_time[gantt_chart.size() - 1]<<endl;

    return;
}

void Scheduler::Priority_Scheduling()
{
	int time = 0;
	vector<int> gantt_chart;
    vector<int> start_time;
    vector<int> end_time;

	while( !ReadyQ.isEmpty() )
	{
		Node *sch_process = NULL;

		if(time == 0)
            sch_process = ReadyQ.deQ();
		else
            sch_process = ReadyQ.extract_min_priority(time); //deQ the process with highest priority

		if(sch_process != NULL)
		{
		    gantt_chart.push_back(sch_process->return_PID());
            start_time.push_back(time);
            end_time.push_back(time + 1);
            cout<<"PID : "<<sch_process->return_PID()<<" is scheduled"<<endl;
            cout<<right<<setw(20)<<"from t = "<<time<<" to t = "<<time + 1<<endl;

            int curr_bt = sch_process->return_burst_time();
            sch_process->set_burst_time(curr_bt - 1);

            if(sch_process->return_burst_time() != 0)
            {
                sch_process->set_next(NULL);
                ReadyQ.enQ(sch_process);
            }
		}
		else
		{
		    cout<<"Unexpected Error!"<<endl;
            return;
        }

        time += 1;
    }

return;
}

void Scheduler::Multilevel_Scheduling()
{
    int counter = 0;

    Queue multilevel_Q[3];
    multilevel_Q[0] = ReadyQ;
    int count_process_0 = multilevel_Q[0].count();

    while(counter <count_process_0)
    {
        Node *sch_process = multilevel_Q[0].deQ();
        if(sch_process->return_burst_time() <= 8)
            cout<<"\n"<<sch_process->return_PID()<<"\t"<<sch_process->return_PName()
            <<"Queue 0 execution over."<<endl;
        else
        {
            int current_bt = sch_process->return_burst_time();
            sch_process->set_burst_time(current_bt - 8);
            multilevel_Q[1].enQ(sch_process);
        }
        counter += 1;
    }

    int count_process_1 = multilevel_Q[1].count();
    counter = 0;
    while(counter <count_process_1)
    {
        Node *sch_process = multilevel_Q[1].deQ();
        if(sch_process->return_burst_time() <= 16)
            cout<<"\n"<<sch_process->return_PID()<<"\t"<<sch_process->return_PName()
            <<"Queue 1 execution over."<<endl;
        else
        {
            int current_bt = sch_process->return_burst_time();
            sch_process->set_burst_time(current_bt - 16);
            multilevel_Q[2].enQ(sch_process);
        }
        counter += 1;
    }

    cout<<"\nFCFS in Queue 2.\n"<<endl;
    cout<<"Order in which reamining process execute is : "<< endl << endl;

    multilevel_Q[2].displayQ();

}
