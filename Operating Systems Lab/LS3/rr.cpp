#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rr.h"

int main()
{
	srand((unsigned)time(0));
	int choice = 0;
	int timeQuantum = 0;
	int *dequeueEle;



	Queue readyQueue;		//creating object for Ready Queue
	Queue runQueue;		//creating object for Running Queue


	//entry of PIDs for Ready Queue
	cout << "How many elemets for Ready Queue: " << endl;
	cin >> choice;
	
	while (choice != 0)
	{
		readyQueue.enqueue((rand()%100)+100, (rand()%20)+20);
		choice--;
	}
	
	//display PIDs of Ready Queue
	cout << "\nReady Queue :	\n";
	readyQueue.queueDisplay();
	
	
	cout << "Enter Time Quantum for Round Robin Scheduling : " << endl;
	cin >> timeQuantum;
	
	while(readyQueue.isEmpty() == 0)
	{
		dequeueEle = readyQueue.dequeue();
		if(dequeueEle[1] <= timeQuantum)
		{
			runQueue.enqueue(dequeueEle[0], dequeueEle[1]);
		}
		else
		{
			runQueue.enqueue(dequeueEle[0], dequeueEle[1]);
			readyQueue.enqueue(dequeueEle[0], (dequeueEle[1]-timeQuantum));
		}
	}
	


	//display PIDs of Ready Queue
	cout << "\nReady Queue with process IDs (PIDs):	";
	runQueue.queueDisplay();
	
	
	
	

	
	cout << "\n\n" << endl;



	system("pause");
    return 0;
}

