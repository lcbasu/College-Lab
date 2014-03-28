#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Node
{
public:
	int info;
	Node *next;
	Node (int el, Node *ptr = 0)
	{
		info = el;
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
	int isEmpty()
	{
		return head == 0;
	}
	void enqueue(int el)
	{
		if (tail != 0)
		{
			tail->next = new Node(el);
			tail = tail->next;
		}
		else
			tail = head = new Node(el);
	}
	int dequeue()
	{
		int el = head->info;
		Node *tmp = head;
		if (head == tail) //only one node in the Queue
			head = tail = 0;
		else
			head = head->next;
		delete tmp;
		return el;
	}
	void queueDisplay()
	{
		Node *p = head;
		while(p != 0)
		{
			cout << p->info << "	";
			p = p->next;
		}
	}
private:
	Node *head, *tail;
};
