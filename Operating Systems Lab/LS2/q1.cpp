#include <iostream>
#include <cstdlib>
#include <ctime>
#include "q1.h"

using namespace std;


//main suroutine
int main()
{
	srand((unsigned)time(0));
	int choice = 0;

	int *dequeueEle;


	Queue readyQueue;		//creating object for Ready Queue
	Queue jobQueue;			//creating object for Job Queue
	Queue runningQueue;		//creating object for Waiting Queue	


	//entry of processes in Job Queue
	cout << "How many processes for Job Queue: " << endl;
	cin >> choice;
	
	while (choice != 0)
	{
		jobQueue.enqueue((rand()%100)+100, (rand()%20), time(0));
		choice--;
	}
		
	//display PIDs of Ready Queue
	cout << "\nJob Queue with details:	";
	jobQueue.queueDisplayDetails();	
	
	cout << "\nJob Queue without details:	";
	jobQueue.queueDisplay();
	
	cout << "\n\n" << endl;
	
	//sorting Job Queue on the basis of Arrival Time
	cout << "\nSorted Job Queue according to Arrival Time:	";
	jobQueue.sortQueue(2);//2. For sorting based on arrival time
	jobQueue.queueDisplay();	
	
	int leastArrivalTime = jobQueue.getArrivalTime();
	int timeElap = leastArrivalTime;
	
	
	while(jobQueue.isEmpty() != 1)
	{		
		for(int i = jobQueue.getArrivalTime(); i <= timeElap;)
		{
			dequeueEle = jobQueue.dequeue();
			readyQueue.enqueue(dequeueEle[0], dequeueEle[1], dequeueEle[2]);		
			i = jobQueue.getArrivalTime();
		}		
		
		// sorting and dequeueing from Ready Queue
		readyQueue.sortQueue(1);// 1. for sorting based on execution time
		dequeueEle = readyQueue.dequeue();
		
		
		//increasing the total elapsed time
		timeElap += dequeueEle[1];
		
		//entry into Running Queue
		runningQueue.enqueue(dequeueEle[0], dequeueEle[1], dequeueEle[2]);
	}
	
	if((jobQueue.isEmpty())  && (!(readyQueue.isEmpty())))
	{
		readyQueue.sortQueue(1);// 1. for sorting based on execution time
		while(!(readyQueue.isEmpty()))
		{
			dequeueEle = readyQueue.dequeue();
			runningQueue.enqueue(dequeueEle[0], dequeueEle[1], dequeueEle[2]);
		}
	}
	
	cout << "Processes arranged according to Shortest Job First (no- preemptive algorithm:\n)" << endl ;
	runningQueue.queueDisplay();		
	return 0;
}






