#include "q3.h"
using namespace std;

#define max 100

int main()
{
	int n;
	cout << "Enter page frame for process : ";
	cin >> n;
	cout << endl;

	LRU obj(n);
	int p[n];
	int i;
	for(i = 0; i < n; i++)
		p[i] = -1;
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

 	int pageFault = 0;
 	for(i=0; i< count; i++)
 	{
 		if(obj.isPresent(inString[i],p,n) != -1)
 		{
 			obj.delNode(inString[i]);
 			obj.addToHead(inString[i]);
 		}
 		else
 		{
 			int lru = obj.lruEl();
 			obj.delTail();
 			obj.addToHead(inString[i]);
 			int lruIndex = obj.isPresent(lru,p,n);
 			p[lruIndex] = inString[i];
 			pageFault++;
 		}
 		obj.displayFrame(p,n);
 	}
 	cout << "\nTotal page faults : " << pageFault << endl;
	return 0;
}