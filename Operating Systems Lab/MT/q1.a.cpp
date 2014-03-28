#include "queue.h"

int main()
{
	Queue newQueue;
	Queue readyQueue;
	Queue runQueue;

	int choice = 1;
	cout << "Enter the process details (all in integer).\n\n";
	do
	{
		int pid, at, pt, pr;
		cout << "Process ID\tArrival Time\tProcessing Time\tPriority\n";
		cin >> pid >> at >> pt >> pr;
		newQueue.enqueue(pid, at, pt, pr);
		cout << endl;
		cout << "Enter any negative number to stop or positive number to continue...";
		cin >> choice;
		cout << endl;

	}while(choice > 0);

	// FCFS
	cout << "FCFS : \n";
	newQueue.queueDisplay();
	cout << endl;

	//	SJF

	int count = 0;
	while(!newQueue.isEmpty())
	{
		Node* temp;
		if(newQueue.isPresent(count))
		{
			temp = newQueue.dequeue();
			readyQueue.enqueue(temp->pID, temp->aT, temp->pT, temp->pR);
		}
		count++;
		readyQueue.sort();
		if(runQueue.isEmpty())
		{
			temp = readyQueue.dequeue();
			runQueue.enqueue(temp->pID, temp->aT, temp->pT, temp->pR);
			runQueue.decreaseProcessingTime();
			cout << runQueue.displayPID();
			if(readyQueue.isFinished())
			{
				temp = runQueue.dequeue();
				delete temp;
			}
		}
	}


}