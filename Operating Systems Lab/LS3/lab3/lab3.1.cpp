

//Round Robin Scheduler

#include <iostream>
#include "kbhit.h"
using namespace std;

struct Node
{
       int PID;
       int burst_time, wait_time, arr_time;
       Node *next;
};

class List
{
  public :
	List(){ head = 0; tail = 0;}
	void insert(Node * tmp);//insert the node according to burst time
	void insertAtLast(Node * tmp);
    Node * remove();//remove the first node from list
	Node * remove(int pid);
    bool isEmpty();			//checks if the list if empty
	static int length;
  protected :
	Node * head;
	Node * tail;
};
int List::length = 0;
bool List::isEmpty()
{
	if( head == 0) return true;
	else return false;
}

void List::insert(Node* tmp)
{
	if(head==0){ //list is empty
		head = tail = tmp;
	}
	else if(head == tail) {
		if(head->arr_time > tmp->arr_time){
			tail = tmp->next  = head;
			head = tmp;
		}
		else tail = head->next = tmp;
	}
	else
	{
		Node * t= head;
		if((tmp->arr_time) < (head->arr_time)){
			tmp->next = head;
			head = tmp;
		}
		else{
		 while( t->next!= 0){ 
			if((tmp->arr_time) >= (t->next->arr_time)) { t = t->next;}
			else{
				tmp->next = t->next;
				t->next = tmp; length++;
				if(tmp->next == 0) tail = tmp->next;
				break; 
			}
		  }
		  if(t->next ==0){
			t->next = tmp;
			tail = tmp;
		  }
		}
		
	}
	tail->next = 0;
	length++;
}

void List :: insertAtLast( Node * tmp)
{	if(head == 0) head = tail = tmp;
	else {
		tail->next = tmp;
		tail = tmp;
	}
	tail->next = 0;
}



Node *List :: remove()
{
	Node * tmp = head;
	if(head ==0) return 0;
	if(head == tail)  // only one node
		head = tail = 0;
	else 
		head = head->next;
	length--;
	return tmp;
}

Node * List::remove(int pid){
		Node *tmp = head;
		Node *tmp1;
		if(isEmpty()) // checks for empty list
		return 0; 
		while((tmp->PID!=pid) && (tmp!=0)){
			tmp1 = tmp;
			tmp = tmp->next;
		}
		tmp1->next = tmp->next;
		length--;
		return tmp;
	}
      

int main()
{
	char choice;
	int  n = 0, b, a, pid;
	List Ready;
	int time = 0;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << "Round Robin Scheduler "<< endl;
	cout << "Ready Queue is empty. Do you want to enter some processes(y/n)." << endl;
	cin >> choice;
	if(choice == 'n') return 0;//exit(0); 
	do{
		cout << "Enter in order \tPID \tBURST TIME \tARRIVAL TIME"<< endl;
		cin >> pid; cin >> b; cin >> a;
		Node * tmp = new Node();
		tmp->PID = pid;
		tmp->burst_time = b;
		tmp->arr_time = a;
		Ready.insert(tmp);
		cout << "Do you want to enter more processes(y/n)." << endl;
		cin >> choice;
	}while(choice != 'n');
	cout << "Enter time quantum" << endl;
	cin  >>n;
	cout << "Round Robin Scheduler started..." << endl;
	cout << "grantt chart for input process is " <<endl;
	cout << "******************************************************************" << endl;
	cout << "\tTime \tProcess PID\n" << endl;
	while(!Ready.isEmpty()){
		Node * tmp = Ready.remove();
		
			cout << "\t" << time;
			for(int i = 0; i<n; i++)
			{
				time++;
				tmp->burst_time--;
				if(tmp->burst_time==0)
					break;
			}
			cout << " - " << time << "\tP[" << tmp->PID << "]" << endl;
			if(tmp->burst_time!=0) Ready.insertAtLast(tmp);
	}
	cout << "********************************************************************" << endl;
	return 0;
}
