#include <iostream>

using namespace std;


class Node
{
public:
	int info[3];
	Node *next, *prev;
	
	Node()
	{
		next = prev = 0;
	}
	
	Node (int pID, int exeTime, int priority, Node *p = 0, Node *n = 0)
	{
		info[0] = pID;
		info[1] = exeTime;
		info[2] = priority;
		prev = p;
		next = n;		
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
	void enqueue(int pID, int exeTime, int priority)
	{
		if (tail != 0)
		{
			tail = new Node(pID, exeTime, priority, tail, 0);
			tail->prev->next = tail;
		}
		else
			tail = head = new Node(pID, exeTime, priority);
	}
	int *dequeue()
	{		
		int *ptr = new int[3];
		if (head == tail) //only one node in the Queue
		{
			ptr[0] = head->info[0];
			ptr[1] = head->info[1];
			ptr[2] = head->info[2];
			
			delete head;
			head = tail = 0;
		}			
		else
		{	
			ptr[0] = head->info[0];
			ptr[1] = head->info[1];
			ptr[2] = head->info[2];
					
			head = head->next;
			delete head->prev;
			head->prev = 0;
		}
		
		return ptr;
		
	}
	
	
	void queueDisplay()
	{	
		Node *p = head;
		cout << endl;
		while(p != 0)
		{
			cout << "P[" <<p->info[0] << "]" << "	" << p->info[1] << "	" << p->info[2] << "	" << endl;
			p = p->next;
		}
		cout << "\n\n" << endl;
	}
	
	//sorting the queue according to Priority
	  
	void sortQueue()
    {
        Node *current, *cur;

        for(current = head; current->next != NULL; current = current->next)
        {
            Node *minimum = current;
            for(cur = current ; cur != NULL; cur = cur->next)
            {
                if(minimum->info[2] > cur->info[2]) 
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
