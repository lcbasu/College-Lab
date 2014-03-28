#include <iostream>
#include <cstdlib>
#include "q3.h"

using namespace std;

#define max 100

int main()
{
	int totalProcess;
	cout << "Enter the total no of processes : ";
	cin >> totalProcess;
	cout << endl;

	int framesPerProcess[totalProcess];

	for(int i = 0; i < totalProcess; i++)
	{
		cout << "Enter no of frames for process P-"<< i <<" : ";
		cin >> framesPerProcess[i];
	}

	int inString[max];
	int temp;
	int count = 0;
 	cout << "\nReference String (-1 for end) : \n";
 	cin >> temp;
 	while(temp != -1 && count <= max)
 	{
  		inString[count++]=temp;
  		cin >> temp;
 	}

 	int lg = rand()%2;

 	if(lg == 0)	//local
 	{
 		for(int i = 0; i < totalProcess; i++)
 		{
 			cout << "For process P-" << i << "\n" << endl;
			int n = framesPerProcess[i];
			LRU obj(n);
			int p[n];
			for(int j = 0; j < n; j++)
				p[j] = -1;
	
 			int pageFault = 0;
 			for( int k=0; k< count; k++)
 			{
 				if(obj.isPresent(inString[k],p,n) != -1)
 				{
		 			obj.delNode(inString[k]);
 					obj.addToHead(inString[k]);
 				}
 				else
 				{
 					int lru = obj.lruEl();
 					obj.delTail();
 					obj.addToHead(inString[k]);
 					int lruIndex = obj.isPresent(lru,p,n);
 					p[lruIndex] = inString[k];
 					pageFault++;
 				}
 				obj.displayFrame(p,n);
 			}
 			cout << "\nTotal page faults : " << pageFault << "\n\n" << endl;
 		}
 	}

 	else	//global
 	{
 		for(int i = 0; i < totalProcess; i++)
 		{
 			int globalFrame = rand()%totalProcess;

 			cout << "Process P-" << i << " uses the frame of process P-" << globalFrame <<endl;

			int n = framesPerProcess[globalFrame];
			LRU obj(n);
			int p[n];
			for(int j = 0; j < n; j++)
				p[j] = -1;
	
 			int pageFault = 0;
 			for(int k=0; k< count; k++)
 			{
 				if(obj.isPresent(inString[k],p,n) != -1)
 				{
		 			obj.delNode(inString[k]);
 					obj.addToHead(inString[k]);
 				}
 				else
 				{
 					int lru = obj.lruEl();
 					obj.delTail();
 					obj.addToHead(inString[k]);
 					int lruIndex = obj.isPresent(lru,p,n);
 					p[lruIndex] = inString[k];
 					pageFault++;
 				}
 				obj.displayFrame(p,n);
 			}
 			cout << "\nTotal page faults : " << pageFault << "\n\n" << endl;
 		}
 	}
	return 0;
}