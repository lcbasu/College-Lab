#include<iostream>
using namespace std;
struct node
{
int data;
node* next;
};
class queue
{
 private:
 node *front,*rear;
public :

queue()
{
front =rear= NULL;

}

bool isempty()
{
node *r = front;
if(front == NULL)
return true;
else return false;

}

void enque(int n)
{
node *p = new node;
if(p == NULL)
{
cout<<endl<<"queue is full";return;
}
p->data = n;
p->next = NULL;
if(front == NULL)
{
rear = p;
front = p;
return;
}

rear->next = p; 
rear = rear->next;

}

int deque()
{
if(front == NULL)
{
cout<<"queue is empty";
return 0;
}
node *temp;
int n;
n = front->data;
temp=front;
front= front->next;
//delete temp;
return n;
}

void display()
{
node* q= front;
while(q != NULL)
{
cout<<q->data<<"->";
q=q->next;
}
}

};
/*
int main()
{

queue job;
queue w8;
queue ready;
queue running;
int n;
int choice =0;
int j ;

while(choice != 7)

{
cout<<"\n 1. Start a new process(Job Queue).\n 2.Add a process from Job Queue to Ready Queue.\n 3.Terminate the Running Process.\n 4. I/O wait \n 5.Interrupt the Running Process \n 6.I/O terminate \n 7. Quit \n 8. Display";
cin>>j;

switch(j)

{
//case 1
case 1 :
{
char ch='t';
while(ch != 'n')
   {
cout<<"\nEnter the PID of Process";
cin>>n;
job.enque(n);
cout<<"\nProcess in Job Queue\n";
cout<<"Do u want to enter more process(y/n)?";
cin>>ch;
cout<<endl;
   }
break;
}

//case 2
case 2 :
{
int x = job.deque();
ready.enque(x);
cout<<"Process added to ready queue with Pid"<<x<<endl;
if(running.isempty() == true)
{
int n = ready.deque();
running.enque(n);
cout<<"Process with PID " <<n<<" is running ";
}

break;
}
//case 3
case 3:

{
running.deque();
if(running.isempty() == true)
{
if(ready.isempty() == false)
{
int x= ready.deque();
running.enque(x);

}
else
{
if(job.isempty() == false)
{
int n = job.deque();
ready.enque(n);
running.enque(ready.deque());
}
else cout<<"\n UnderFlow \n";
}
cout<<"Process Terminated \n";
}
break;
}

//case 4
case 4:
{
int n= running.deque();
w8.enque(n);
if(running.isempty() == true)
{
if(ready.isempty() == false)
{
int x= ready.deque();
running.enque(x);

}
else
{
if(job.isempty() == false)
{
int n = job.deque();
ready.enque(n);
running.enque(ready.deque());
}
else cout<<"\n UnderFlow \n";
}
cout<<"Process inserted in Waiting queue\n";
break;
}
}
case 5 :
{
int x;
x= running.deque();
ready.enque(x);
if( running.isempty() == true && ready.isempty() == false )
{ int y = ready.deque();
running.enque(y);
}
else
{
if(job.isempty() == false)
{
int s = job.deque();
ready.enque(s);
running.enque(ready.deque());
}
else
cout<<"\n Underflow \n";
}
 break;
}
//case 6
case 6 :
{
int x =w8.deque();
ready.enque(x);
cout<<"\n I/O terminated and process enqued in ready queue with pid "<<x<<endl;
break;
} 
//case 7
case 7 :
{
choice= 7;
cout<<"program terminated"<<endl;
break;

}
case 8 :
{
cout<<" Job queue ";
job.display();
cout<<endl;
cout<<"Ready queue ";
ready.display();
cout<<endl;
cout<<"Running queue";
running.display();
cout<<endl;
cout<<"Waiting queue ";
w8.display();
cout<<endl;
break;
}
}
}

return 0;

}

*/







