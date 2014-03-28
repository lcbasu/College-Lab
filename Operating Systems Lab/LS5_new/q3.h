#include <iostream> 

using namespace std;

class Node
{
public:
	int info;
	Node* next;
	Node(int el, Node* n=0)
	{
		info = el;
		next = n;
	}
};

class LRU
{
public:
	LRU(int s)
	{
		head = tail = 0;
		head = tail = new Node(-1);
		int count = 0;
		while(count< (s-1))
		{
			tail->next = new Node(-1);
			tail = tail->next;
			count++;
		}
	}
	int addToHead(int);
	void delNode(int);
	void delTail();
	int lruEl();
	int isPresent(int el, int arr[], int size);
	void displayFrame(int arr[], int size);
private:
	Node *head, *tail;
};

int LRU::isPresent(int el, int arr[], int size)
{
	int index = -1;
	for(int i=0; i<size; i++)
	{
		if(arr[i] == el)
		{
			index = i;
			break;
		}
	}
	return index;
}

int LRU::lruEl()
{
	return tail->info;
}

int LRU::addToHead(int el)
{
	head = new Node(el, head);
}

void LRU::delNode(int el)
{
	if((head == tail) && (head->info == el))
	{
		delete head;
		head = tail = 0;
	}
	else if(head->info == el)
	{
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
	else
	{
		Node *pred,*tmp;
		for(pred = head, tmp = head->next;
			tmp != 0, !(tmp->info == el);
			pred = pred->next, tmp = tmp->next);
		if(tmp != 0)
		{
			pred->next = tmp->next;
			if(tmp == tail)
				tail = pred;
			delete tmp;
		}
	}
}

void LRU::delTail()
{
	if(head == tail)
	{
		delete head;
		head = tail = 0;
	}
	else
	{
		Node *tmp;
		for(tmp = head; tmp->next != tail; tmp = tmp->next);

		delete tail;
		tail = tmp;
		tail->next = 0;
	}
}


void LRU::displayFrame(int arr[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(arr[i] == -1)
			cout << "| _";
		else
			cout << "| " << arr[i];
	}
	cout << "\n";
}
