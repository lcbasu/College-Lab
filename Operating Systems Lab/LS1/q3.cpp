#include "q3.h"

//main suroutine
int main()
{
	srand((unsigned)time(0));
	int choice = 0;



	Queue readyQueue;		//creating object for Ready Queue
	Queue jobQueue;			//creating object for Job Queue
	Queue waitQueue;		//creating object for Waiting Queue


	//entry of PIDs for Ready Queue
	cout << "How many elemets for Ready Queue: " << endl;
	cin >> choice;

	while (choice != 0)
	{
		readyQueue.enqueue((rand()%100)+100);
		choice--;
	}


	//entry of PIDs for Job Queue
	cout << "How many elemets for Job Queue: " << endl;
	cin >> choice;

	while (choice != 0)
	{
		jobQueue.enqueue((rand()%100)+100);
		choice--;
	}


	//entry of PIDs for Waiting Queue
	cout << "How many elemets for Waiting Queue: " << endl;
	cin >> choice;

	while (choice != 0)
	{
		waitQueue.enqueue((rand()%100)+100);
		choice--;
	}

	//display PIDs of Ready Queue
	cout << "\nReady Queue with process IDs (PIDs):	";
	readyQueue.queueDisplay();

	//display PIDs of Job Queue
	cout << "\nJob Queue with process IDs (PIDs):	";
	jobQueue.queueDisplay();

	//display PIDs of Waiting Queue
	cout << "\nWaiting Queue with process IDs (PIDs):	";
	waitQueue.queueDisplay();

	cout << "\n\n" << endl;



	return 0;
}
