#include <iostream>

using namespace std;


class Node
{
public:
	int pID, aT, pT, pR;
	Node *next, *prev;
	Node (int pid, int at, int pt, int pr, Node *n = 0, Node *p = 0)
	{
		pID = pid;
		aT = at;
		pT = pt;
		pR = pr;
		next = n;
		prev = p;
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
	void enqueue(int pid, int at, int pt, int pr)
	{
		if (tail != 0)
		{
			tail->next = new Node(pid,at,pt,pr);
			tail->next->prev = tail;
			tail = tail->next;
		}
		else
			tail = head = new Node(pid,at,pt,pr);
	}
	Node* dequeue()
	{
		Node *tmp = head;
		if (head == tail) //only one node in the Queue
			head = tail = 0;
		else
			head = head->next;
		return tmp;
	}
	void queueDisplay()
	{
		Node *p = head;
		while(p != 0)
		{
			cout << p->pID << "	";
			p = p->next;
		}
	}

	bool isPresent(int at)
	{
		return head->aT == at;
	}
	void decreaseProcessingTime()
	{
		head->pT = (head->pT - 1);
	}
	int displayPID()
	{
		return head->pID;
	}

	bool isFinished()
	{
		return head->pT == 0;
	}

	void sort()
    {
        Node *current, *cur;

        for(current = head; current->next != NULL; current = current->next)
        {
            Node *minimum = current;
            for(cur = current ; cur != NULL; cur = cur->next)
            {
                if(minimum->pT > cur->pT) 
                {
                    minimum = cur;
                }
            }
            if(minimum != current)
            {
                Node *current_previous, *current_next, *min_previous, *min_next;

                // Initialize them
                current_next = current->next;
                min_previous = minimum->prev;
                min_next = minimum->next;
                current_previous = current->prev;

                if(current_previous == NULL)
                {
                    // Change the head Node
                    head = minimum;
                }
                if(current->next == minimum)
                {
                    // Nodes are Adjacent
                    minimum->prev = current_previous;
                    minimum->next = current;

                    current->prev = minimum;
                    current->next = min_next;

                    if(min_next)
                    {
                        min_next->prev = current;
                    }
                    if(current_previous)
                    {
                        current_previous->next = minimum;
                    }
                }
                else
                {
                    minimum->prev = current_previous;
                    minimum->next = current_next;

                    current->prev = min_previous;
                    current->next = min_next;

                    if(current_next)
                    {
                        current_next->prev = minimum;
                    }
                    if(min_previous)
                    {
                        min_previous->next = current;
                    }
                    if(min_next)
                    {
                        min_next->prev = current;
                    }
                    if(current_previous)
                    {
                        current_previous->next = minimum;
                    }
                }
                current = minimum;
            }
        }

    }
private:
	Node *head, *tail;
};
