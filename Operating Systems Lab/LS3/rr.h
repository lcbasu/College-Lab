#include <iostream>

using namespace std;


class Node
{
public:
	int info[3];
	Node *next;
	
	Node()
	{
		next = 0;
	}
	
	Node (int pID, int exeTime, Node *ptr = 0)
	{
		info[0] = pID;
		info[1] = exeTime;
		next = ptr;		
	}
};

class Queue
{
public:
	Queue()
	{
		head = tail = 0;
	}
	bool isEmpty()
	{
		return head == 0;
	}
	void enqueue(int pID, int exeTime)
	{
		if (tail != 0)
		{
			tail->next = new Node(pID, exeTime);
			tail = tail->next;
		}
		else
			tail = head = new Node(pID, exeTime);
	}
	int *dequeue()
	{		
		Node *tmp = head;
		int *ptr = new int[2];
		
		ptr[0] = head->info[0];
		ptr[1] = head->info[1];
		
		if (head == tail) //only one node in the Queue						
			head = tail = 0;		
		else
			head = head->next;
		delete tmp;
		return ptr;
		
	}
	
	void queueDisplay()
	{	
		Node *p = head;
		cout << endl;
		while(p != 0)
		{
			cout << "P[" <<p->info[0] << "]" << "	" << p->info[1] << "	" << "\n";
			p = p->next;
		}
		cout << endl;
	}
	
	

private:
	Node *head, *tail;	
};
