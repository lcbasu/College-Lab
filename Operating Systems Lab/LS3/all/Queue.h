#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

struct node
{
	int PID;
	string Pname;
	int burst;
	clock_t time;
	int priority; 
	node *next;
};
class Queue
{
	private:
	node* front;
	node* rear;
	public:
	Queue();
	void enque(int, string, int,clock_t,int);
	node deque();
	void search(int);
	void display(int k);
	void minque();
	int elem();
	void SJF(int);
	bool isEmpty();
	void delque();
	void extractmin(int);
	void gantt(int);
	void ganttMQFS(int,int);
};

Queue:: Queue()
{
	front=rear=NULL;
}

bool Queue::isEmpty()
{
	if(front==NULL)
	{return true;}
	else
	{return false;}
}

void Queue:: delque()
{
	front=rear=NULL;
}

void Queue::enque(int pid, string s, int random, clock_t t=0,int l=0)
{
	node* newnode = new node;
	newnode->PID = pid;
	newnode->Pname = s;
	newnode->burst = random;
	newnode->time = t;
	newnode->priority=l;
	newnode->next=NULL;
	if (front==NULL)
	{
		front=rear=newnode;
	}
	else
	{
		rear->next = newnode;
		rear = newnode;
	}
}

node Queue::deque()
{
	if(front==NULL)
	{
	//	cout<<"Queue Empty"<<endl;
	}
	else if(front->next==NULL)
	{
		int temp = front->PID;
		string temp2 = front->Pname;
		int bur = front->burst;
		clock_t k = front->time;
		node result = {temp,temp2,bur,k};
		front=NULL;
		return result;
	}
	else
	{
		int temp = front->PID;
		string temp2 = front->Pname;
		int bur = front->burst;
		clock_t k = front->time;
		front=front->next;
		node result = {temp,temp2,bur,k};
		return result;
	}
}

void Queue::search(int key)
{
	node* temp = front;
	bool flag = false;
	while(temp->next!=NULL)
	{
		temp= temp->next;
	}
	flag = true;
	int a = front->PID;
	string b =front->Pname;
	int c = front->burst;
	clock_t u = front->time;
	front->PID = temp->PID;
	front->Pname = temp->Pname;
	front->burst = temp->burst;
	front->time = temp->time;
	temp->PID = a;
	temp->Pname = b;
	temp->burst = c;
	temp->time = u;
	if (flag==false)
	{
		cout<<"No entry"<<endl;
	}
}

void Queue::display(int k=0)
{
	cout<<endl;
	if(front!=NULL)
	{
		node* temp = front;
		if(k==0)
		{
			while (temp->next!=NULL)
			{
				cout<<setw(8)<<temp->PID<<setw(20)<<temp->Pname<<setw(12)<<temp->burst<<setw(12)<<temp->priority<<endl;
				temp=temp->next;
			}	
			cout<<setw(8)<<temp->PID<<setw(20)<<temp->Pname<<setw(12)<<temp->burst<<setw(12)<<temp->priority<<endl;
			cout<<endl;
		}
		else if(k==1)
		{
			while (temp->next!=NULL)
			{
				cout<<setw(8)<<temp->PID<<setw(20)<<temp->Pname<<setw(12)<<temp->burst<<setw(12)<<temp->time<<setw(12)<<temp->priority<<endl;
				temp=temp->next;
			}	
			cout<<setw(8)<<temp->PID<<setw(20)<<temp->Pname<<setw(12)<<temp->burst<<setw(12)<<temp->time<<setw(12)<<temp->priority<<endl;
			cout<<endl;
		}
	}	
	else
	{
	cout<<"Queue Empty"<<endl;
	}
}

void Queue::gantt(int k)
{
	cout<<"GANTT CHART"<<endl;
	int count=0;
	node p;
	int l=0;
	if(front!=NULL)
	{
		count=this->elem();
		int ar[count+1];
		for(int i=0; i<(count*8 + 6);i++)
		{
			cout<<"_";
		}
		cout<<endl;
		cout<<setw(2)<<"PID->"<<setw(2)<<" ";
		if(k!=0)
		{
			for(int i=0; i<count; i++)
			{
				p = this->deque();
				cout<<setw(4)<<p.PID<<setw(4)<<"|";
				ar[i]= l;
				(p.burst<k)? l=l+p.burst:l=l+k; 
			}
		}
		else if (k==0)
		{
			for(int i=0; i<count; i++)
			{
				p = this->deque();
				cout<<setw(4)<<p.PID<<setw(4)<<"|";
				ar[i]= l;
				l=l+p.burst; 
			}
		}
		ar[count] = l;
		cout<<endl;
		for(int i=0; i<(count*8 + 6);i++)
		{
			cout<<"_";
		}
		cout<<endl;
		cout<<setw(2)<<"t->  "<<setw(2)<<" ";
		cout<<ar[0]<<setw(3)<<" ";
		for(int i=1; i<=count; i++)
		{
			cout<<setw(4)<<ar[i]<<setw(4)<<" ";
		}
		cout<<endl;
		for(int i=0; i<(count*8 + 6);i++)
		{
			cout<<"_";
		}
		cout<<endl;
	}	
}

void Queue::ganttMQFS(int k,int j)
{
	cout<<"GANTT CHART"<<endl;
	int count=0;
	int tempcount =0;
	node p;
	int l=0;
	count=this->elem();
	int ar[count+1];
	///////////////////////////////////////
	for(int i=0; i<(count*8 + 6);i++)
	{
		cout<<"_";
	}
	cout<<endl;
	cout<<setw(2)<<"PID->"<<setw(2)<<" ";
	//////////////////////////////////////
	for(int i=0; i<5; i++)
	{
		p = this->deque();
		cout<<setw(4)<<p.PID<<setw(4)<<"|";
		ar[i]= l;
		if(p.burst<=k)
		{
			l=l+p.burst;
			tempcount++;
		}
		else
		{
			l=l+k;
		}
	}
	//////////////////////////////////////
	for(int i=5; i<(10-tempcount); i++)
	{
		p = this->deque();
		cout<<setw(4)<<p.PID<<setw(4)<<"|";
		ar[i]= l;
		(p.burst<j)? l=l+p.burst:l=l+j;
	}
	//////////////////////////////////////
	int h=10;
	while(!(this->isEmpty()))
	{
		p=this->deque();
		cout<<setw(4)<<p.PID<<setw(4)<<"|";
		ar[h]=l;
		l=l+p.burst;
		h++;
	}
	ar[count] = l;
	cout<<endl;
	//////////////////////////////////////
	for(int i=0; i<(count*8 + 6);i++)
	{
			cout<<"_";
	}
	cout<<endl;
	cout<<setw(2)<<"t->  "<<setw(2)<<" ";
	cout<<ar[0]<<setw(3)<<" ";
	//////////////////////////////////////
	for(int i=1; i<=count; i++)
	{
		cout<<setw(4)<<ar[i]<<setw(4)<<" ";
	}
	cout<<endl;
	//////////////////////////////////////
	for(int i=0; i<(count*8 + 6);i++)
	{
		cout<<"_";
	}
	cout<<endl;	
}
void Queue:: minque()
{
	if(front!=NULL)
	{
		if(front->next!=NULL)
		{
			node* temp = front;
			int min = temp->priority;
			node* minnode = temp;
			while(temp->next!=NULL)
			{
				temp = temp->next;
				if ( min>(temp->priority))
				{
					min = temp->priority;
					minnode = temp;
				}
			}
			int a = front->PID;
			string b =front->Pname;
			int c = front->burst;
			clock_t d = front->time;
			int e = front->priority;
			front->PID = minnode->PID;
			front->Pname = minnode->Pname;
			front->burst = minnode->burst;
			front->time = minnode->time;
			front->priority = minnode->priority;
			minnode->PID = a;
			minnode->Pname = b;
			minnode->burst = c;
			minnode->time = d;
			minnode->priority = e;
		}
	}	
}


void Queue:: SJF(int k)
{
	if(front!=NULL)
	{
		if(front->next!=NULL)
		{
			node* temp = front;
			int min = temp->burst;
			node* minnode = temp;
			while(temp->next!=NULL)
			{
				temp = temp->next;
				if ((temp->burst)<=min && (temp->time)<=k)
				{
					min = temp->burst;
					minnode = temp;
				}
			}
			int a = front->PID;		
			string b =front->Pname;
			int c = front->burst;	
			clock_t d = front->time;
			int e = front->priority;
			front->PID = minnode->PID;
			front->Pname = minnode->Pname;
			front->burst = minnode->burst;
			front->time = minnode->time;
			front->priority = minnode->priority;
			minnode->PID = a;
			minnode->Pname = b;
			minnode->burst = c;
			minnode->time = d;
			minnode->priority = e;
		}
	}
}


void Queue:: extractmin(int k)
{
	if(front!=NULL)
	{
		if(front->next!=NULL)
		{
			node* temp = front;
			int min = temp->priority;
			node* minnode = temp;
			while(temp->next!=NULL)
			{
				temp = temp->next;
				if ((temp->priority)<min && (temp->time)<=k)
				{
					min = temp->burst;
					minnode = temp;
				}
			}
			int a = front->PID;
			string b =front->Pname;
			int c = front->burst;
			clock_t d = front->time;
			int e = front->priority;
			front->PID = minnode->PID;
			front->Pname = minnode->Pname;
			front->burst = minnode->burst;
			front->time = minnode->time;
			front->priority = minnode->priority;
			minnode->PID = a;
			minnode->Pname = b;
			minnode->burst = c;
			minnode->time = d;
			minnode->priority = e;
		}
	}
}

int Queue :: elem()
{
	if(front!=NULL)
	{
		if(front->next!=NULL)
		{
			node* temp = front;
			int count = 1;
			while(temp->next!=NULL)
			{
				count++;
				temp=temp->next;
			}
			return count;
		}
		else {return 1;}
	}
	else
	{
		return 0;
	}
}

