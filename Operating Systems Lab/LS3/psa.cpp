#include <cstdlib>
#include <ctime>
#include "psa.h"

int main()
{
	srand((unsigned)time(0));
	int choice = 0;
	int *dequeueEle;



	Queue readyQueue;	//creating object for Ready Queue
	Queue runQueue;		//creating object for Running Queue
	Queue waitQueue;	//creating object for Running Queue


	//entry of PIDs for Ready Queue
	cout << "How many elemets for Ready Queue: " << endl;
	cin >> choice;
	int toatlPriority = choice;
	
	while (choice != 0)
	{
		readyQueue.enqueue((rand()%100)+100, (rand()%20)+20, (rand()%(toatlPriority))+1);
		choice--;
	}
	
	//display PIDs of Ready Queue
	cout << "\nReady Queue :	\n";
	readyQueue.queueDisplay();
	
	readyQueue.sortQueue();
	
	runQueue = readyQueue;
	
	cout << "Processes after Priority Scheduling Algorithm : \n" << endl;
	runQueue.queueDisplay();
	
	
	
	
	
	

	
	cout << "\n\n" << endl;



	system("pause");
    return 0;
}

