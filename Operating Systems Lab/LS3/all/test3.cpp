#include <iostream>
#include "Queue.h"
#include	<cstdio>
#include	<cstdlib>
#include	<string>
#include	<fstream>
#include	<ctime>

using namespace std;
void wait ( int seconds )
{
	clock_t endwait;
	endwait = clock () + (seconds * CLOCKS_PER_SEC)/5000 ;
	while (clock() < endwait) {}
}

int main()
{
	srand(time(NULL));
	Queue q[5];
	ifstream myfile("proc.txt");
	//initialize counters
	int count = 5;
	int ct = 0;
	int ctr= 30;
	int i=0;
	int y;
	//read PID and Pname from file
	while(!myfile.eof())
	{
		string x;
		myfile>>x;
		count--;
		if(count==0)
		{
			if(ct==0)
			{		
				y=atoi(x.c_str());
			}	
			ct++;
			if(ct==2)
			{
				int r = (rand()%4+1)+(rand()%4+1);
				q[i].enque(y,x,r,0,0);
				count=1;
				ct=0;
				ctr--;
				if(ctr==0)
				{
					ctr=30;
					i++;
				}
				if(i==1)
				{		
					i=0;
					break;
				}
			}
			else {count=3;}
		}	
	}

	//Display Simulated Job Queue
	cout<<"Job Queue :"<<endl;
	cout<<setw(8)<<"PID"<<setw(20)<<"PROCESS NAME"<<setw(12)<<"BURST TIME"<<setw(14)<<"ARRIVAL TIME"<<setw(12)<<"PRIORITY"<<endl;
	q[0].display(1);
	
	//Display Ready Queue (invoking CPU scheduler)
	node p;
	node curr;
	int procswitch;
	int g;
	int l=1;
	clock_t t;
	clock_t temp;
	int ar[5]={1,2,3,4,5};
	for(int k=5; k>0; k--) 
	{
		p = q[0].deque();
		t = clock()/10000;
		int i= rand()%5;
		l=ar[i];
		while(l==0)
		{	
			i=(i+1)%5;
			l=ar[i];
		}
		ar[i]=0;
		q[1].enque(p.PID,p.Pname,p.burst,t,l);
		g = (rand()%10 + 1) + (rand()%100 + 1) + (rand()%100 + 1)+(rand()%5 + 1);
		wait(g);
	}
	cout<<"Ready queue : "<<endl;
	cout<<setw(8)<<"PID"<<setw(20)<<"PROCESS NAME"<<setw(12)<<"BURST TIME"<<setw(14)<<"ARRIVAL TIME"<<setw(12)<<"PRIORITY"<<endl;
	q[1].display(1);
	
	//Scheduling	
	int b;
	int quant,quant2;
	cout<<"Round Robin (1) Priority (2) MQFS (3)"<<endl;
	cin>>b;
	switch (b)
	{
		case(1): l=0;
					cout<<"Enter time Quantum"<<endl;
					cin>>quant;
					while(!q[1].isEmpty())
					{	
						p=q[1].deque();
						q[3].enque(p.PID, p.Pname,p.burst,p.time,p.priority);
						l++;
						temp=((p.burst)-quant);
						if(temp>0)
						{
							q[1].enque(p.PID,p.Pname,temp,p.time,p.priority);
						}
					}
					q[3].gantt(quant);
					break;	
		case(2):
					while(!q[1].isEmpty())
					{	
						q[1].minque();
						p=q[1].deque();
						q[3].enque(p.PID, p.Pname,p.burst,p.time,p.priority);
					}
					q[3].gantt(0);
					break;
		case(3):
					cout<<"Enter (quantum 1) (quantum 2)"<<endl;
					cin>>quant;
					cin>>quant2;
					//running of processes in q=quant
					while(!q[1].isEmpty())
					{
						p=q[1].deque();
						q[3].enque(p.PID, p.Pname,p.burst,p.time,p.priority);
						temp=((p.burst)-quant);
						if(temp>0)
						{
							q[4].enque(p.PID,p.Pname,temp,p.time,p.priority);
						}
					}
					
					//running of processes in q=quant2
					while(!q[4].isEmpty())
					{
						p=q[4].deque();
						q[3].enque(p.PID, p.Pname,p.burst,p.time,p.priority);
						temp=((p.burst)-quant2);
						if(temp>0)
						{
							q[1].enque(p.PID,p.Pname,temp,p.time,p.priority);
						}
					}
					
					//running of process in q = FCFS
					while(!q[1].isEmpty())
					{
						p=q[1].deque();
						q[3].enque(p.PID, p.Pname,p.burst,p.time,p.priority);
					}
					q[3].ganttMQFS(quant,quant2);
		default : break;
	}
	
	system("pause");
	return 0;
}
	
