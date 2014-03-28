/*

	CopyRight : Bhisham Pratap Singh
				10114012 CSE(III)

*/

#include <iostream>
using namespace std;


class Node{
public :
	int PID, burst_time, arr_time, priority;
	Node *next;
};

class Queue
{
public :
	Queue(){ head = 0; tail = 0;}
	void enQueue(Node * tmp);
    Node * deQueue();
	void display();
    bool isEmpty();
    int countNodes();

protected :
	Node * head;
	Node * tail;
};

bool Queue::isEmpty()
{
	if( head == 0) return true;
	return false;
}

void Queue::enQueue(Node * tmp)
{
	if(isEmpty()) //list is empty
		head = tail = tmp;
	else
	{
		tail->next = tmp;
		tail = tail->next;
	}
}
Node *Queue::deQueue()
{
	if(isEmpty()) {
		return new Node();
	}
	Node *tmp = head;
	if(head == tail)  // only one node
		head = tail = 0;
	else 
		head = head->next;
	return tmp;
}

void Queue::display()
{
	if(head==0)
		cout<<"Queue Empty!"<<endl;
	else
		{Node * tmp = head;
	int i = 1;
	while(tmp!=0)
	{
		cout << "Process "<< i << "has PID: " << tmp->PID<<endl;
		tmp = tmp->next;
	}
	}
}

int Queue::countNodes()
{ 
	int count = 0;
	Node * tmp = head;
	while(tmp!=0)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
}