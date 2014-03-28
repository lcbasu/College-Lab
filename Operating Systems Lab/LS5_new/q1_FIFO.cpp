#include <iostream>
using namespace std;

#define max 100

class Node
{
public:
	Node(int el,Node *n=0)
	{
		info = el;
		next = n;
	}
	int info;
	Node *next;
};

class PageFrame
{
public:
	PageFrame(int n)
	{
		head = tail = 0;
		int count = 0;
		head = tail = new Node(-1);
		while(count < (n-1))
		{
			tail->next = new Node(-1);
			tail = tail->next;
			count++;
		}
	}

	int isPresent(int el)
	{
		Node *temp;
		for(temp = head; temp != 0 && !(temp->info == el); temp = temp->next);
		return temp != 0;
	}

	void pageEntry(int el)
	{
		tail->next = new Node(el);
		tail = tail->next;
		Node *temp = head;
		head = head->next;
		delete temp;
	}

	void pageData(int n)
	{
		Node *temp;
		for(temp = head; temp != 0; temp = temp->next)
		{
			if(temp->info == -1)
				cout << "| _";
			else
				cout << "| " << temp->info;
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
 		if(!frame.isPresent(inString[i]))
 		{
 			frame.pageEntry(inString[i]);
 			frame.pageData(size);
 			pageFault++;
 		}
 	}

 	cout << "Total page fault : " << pageFault << endl;

 	return 0;
}