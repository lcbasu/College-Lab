#include <iostream>
using namespace std;

#define max 100

class Node
{
public:
	Node(int el=-1, int rB=0, int mB=0, Node *n=0)
	{
		info = el;
		refBit = rB;
		modBit = mB;
		next = n;
	}
	int info, refBit, modBit;
	Node *next;
};

class PageFrame
{
public:
	PageFrame(int n)
	{
		head = tail = 0;
		int count = 0;
		head = tail = new Node();
		tail->next = head;
		while(count < (n-1))
		{
			tail->next = new Node();
			tail = tail->next;
			tail->next = head;
			count++;
		}
	}

	int isPresent(int el, int n)
	{
		Node *temp = head;
		int count=0;
		while((count < n) && !(temp->info == el))
		{
			temp = temp->next;
			count++;
		}
		return temp->info == el;
	}

	void pageEntry(int el)
	{
		while(1)
		{
			if(head->refBit == 0)
			{
				head->info = el;
				head->refBit = 1;
				head->modBit = 1;
				head = head->next;
				break;
			}
			else if(head->refBit == 1)
			{
				head->refBit = 0;
				head = head->next;
			}
		}
	}

	void pageData(int n)
	{
		Node *temp = head;
		int count = 0;
		while(count < n)
		{
			if(temp->info == -1)
				cout << "| _";
			else
				cout << "| " << temp->info;
			count++;
			temp = temp->next;
		}
		cout << "\n";
	}

private:
	Node *head, *tail;
};

int main()
{
	int size;
	cout << "Enter the size of the page frame : ";
	cin >> size;

	PageFrame frame(size);

	int pageFault = 0;

	int temp;
	int inString[max];
 	int count = 0;
 	cout << "\nReference String (-1 for end) : \n";
 	cin >> temp;
 	while(temp != -1 && count <= max)
 	{
  		inString[count++]=temp;
  		cin >> temp;
 	}

 	for(int i=0; i<count; i++)
 	{
 		if(!frame.isPresent(inString[i], size))
 		{
 			frame.pageEntry(inString[i]);
 			frame.pageData(size);
 			pageFault++;
 		}
 	}

 	cout << "Total page fault : " << pageFault << endl;

 	return 0;
}