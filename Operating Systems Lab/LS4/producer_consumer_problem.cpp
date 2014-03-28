#include <iostream>
#include <stdlib>
#include<windows>
#define FULL 1
#define EMPTY 0

HANDLE hmutex;
HANDLE hproducer,hconsumer;


int temp,prod=0,cons=0;

struct node1
{
	int info1;
	struct node1 *next1;
};

struct node2
{
	int info2;
	struct node2 *next2;
};


typedef struct node1 *NODEPTR1;
NODEPTR1 makeNode1(int);

typedef struct node2 *NODEPTR2;
NODEPTR2 makeNode2(int);

class list1
{
public:
	list1();
	~list1();
	int emptylist1();
	void insertend1(int);
	void printlist1();
	void addFront1(int);
	void deleteFront1();
	void deletespecific1(int);
private:
	NODEPTR1 listptr1;
};

class list2
{
public:
	list2();
	~list2();
	int emptylist2();
	void insertend2(int);
	void printlist2();
	void addFront2(int);
	void deleteFront2();
private:
	NODEPTR2 listptr2;
};

list1::list1()
{
	listptr1=0;
}

list2::list2()
{
	listptr2=0;
}

list1::~list1()
{
	NODEPTR1 CurrPtr1;
	if(emptylist1())
		return;
	while(listptr1!=NULL)
	{
		CurrPtr1=listptr1;
		listptr1 =listptr1->next1;
		delete CurrPtr1;
	}
}

list2::~list2()
{
	NODEPTR2 CurrPtr2;
	if(emptylist2())
		return;
	while(listptr2!=NULL)
	{
		CurrPtr2=listptr2;
		listptr2 =listptr2->next2;
		delete CurrPtr2;
	}
}


void list1::addFront1(int value)
{
	NODEPTR1 CurrPtr1, newNode1;
	newNode1 = makeNode1(value);
	CurrPtr1= listptr1;
	newNode1->info1=value;
	if(emptylist1())
	{
		newNode1->next1 = listptr1;
		listptr1= newNode1;
	}
	else
	{
		for(CurrPtr1=listptr1;CurrPtr1->next1!=NULL;CurrPtr1=CurrPtr1->next1);
                  newNode1->next1= listptr1;
		  listptr1 = newNode1;

        }

}

void list2::addFront2(int value)
{
	NODEPTR2 CurrPtr2, newNode2;
	newNode2 = makeNode2(value);
	CurrPtr2= listptr2;
	newNode2->info2=value;
	if(emptylist2())
	{
		newNode2->next2 = listptr2;
		listptr2= newNode2;
	}
	else
	{
		for(CurrPtr2=listptr2;CurrPtr2->next2!=NULL;CurrPtr2=CurrPtr2->next2);
                  newNode2->next2= listptr2;
		  listptr2 = newNode2;

        }

}



NODEPTR1 makeNode1(int number)
{
	NODEPTR1 newNode1;
	if(!(newNode1 = new node1))
	{
		cout<<"Memory Allocation error";
		exit(0);
	}
	newNode1->info1= number;
	newNode1->next1=NULL;
	return newNode1;
}

NODEPTR2 makeNode2(int number)
{
	NODEPTR2 newNode2;
	if(!(newNode2 = new node2))
	{
		cout<<"Memory Allocation error";
		exit(0);
	}
	newNode2->info2= number;
	newNode2->next2=NULL;
	return newNode2;
}

void list1::printlist1()
{
	NODEPTR1 CurrPtr1;
	cout<<"****This is the full Queue****"<<endl;
	if(emptylist1())
		cout<<"\n----The List 1 is Empty----\n";
	else
	{
		cout<<endl;
		for(CurrPtr1=listptr1;CurrPtr1!=NULL;CurrPtr1=CurrPtr1->next1)
		{
			if(CurrPtr1->next1==NULL)
				cout<<CurrPtr1->info1<<endl;
			else
				cout<<CurrPtr1->info1<<"->";
		}
	}
}

void list2::printlist2()
{
	NODEPTR2 CurrPtr2;
	cout<<"****This is the Empty Queue****"<<endl;
	if(emptylist2())
		cout<<"\n----The List 1 is Empty----\n";
	else
	{
		cout<<endl;
		for(CurrPtr2=listptr2;CurrPtr2!=NULL;CurrPtr2=CurrPtr2->next2)
		{
			if(CurrPtr2->next2==NULL)
				cout<<CurrPtr2->info2<<endl;
			else
				cout<<CurrPtr2->info2<<"->";
		}
	}
}


int list1::emptylist1()
{
	return (listptr1==0);
}

int list2::emptylist2()
{
	return (listptr2==0);
}

void list1::insertend1(int value)
{
	NODEPTR1 CurrPtr1, newNode1;
	newNode1 = makeNode1(value);
	newNode1->info1=value;
	if(emptylist1())
	{
		newNode1->next1=listptr1;
		listptr1=newNode1;
	}
	else
	{
		for(CurrPtr1=listptr1;CurrPtr1->next1!=NULL;CurrPtr1=CurrPtr1->next1);
		 newNode1->next1= CurrPtr1->next1;
		 CurrPtr1->next1=newNode1;

	}
}

void list2::insertend2(int value)
{
	NODEPTR2 CurrPtr2, newNode2;
	newNode2 = makeNode2(value);
	newNode2->info2=value;
	if(emptylist2())
	{
		newNode2->next2=listptr2;
		listptr2=newNode2;
	}
	else
	{
		for(CurrPtr2=listptr2;CurrPtr2->next2!=NULL;CurrPtr2=CurrPtr2->next2);
		 newNode2->next2= CurrPtr2->next2;
		 CurrPtr2->next2=newNode2;

	}
}

void list1::deleteFront1()
{
	NODEPTR1 CurrPtr1, prevPtr;
	if(emptylist1())
	{
		cout<<"\n----The List 1 is Empty----"<<endl;
		return;
	}
	if(listptr1->next1==NULL)
	{
		CurrPtr1=listptr1;
		listptr1= listptr1->next1;
		temp=CurrPtr1->info1;
		delete CurrPtr1;
	}
	else
	{
		CurrPtr1= listptr1;
		while(CurrPtr1->next1 !=NULL)
		{

			CurrPtr1=CurrPtr1->next1;
		}
		CurrPtr1 = listptr1;
		listptr1 = listptr1->next1;
        temp=CurrPtr1->info1;
		delete CurrPtr1;

	}
}

void list2::deleteFront2()
{
	NODEPTR2 CurrPtr2, prevPtr;
	if(emptylist2())
	{
		cout<<"\nthe list1 is empty"<<endl;
		return;
	}
	if(listptr2->next2==NULL)
	{
		CurrPtr2=listptr2;
		listptr2= listptr2->next2;
		delete CurrPtr2;
	}
	else
	{
		CurrPtr2= listptr2;
		while(CurrPtr2->next2!=NULL)
		{

			CurrPtr2=CurrPtr2->next2;
		}
		CurrPtr2 = listptr2;
		listptr2 = listptr2->next2;

		delete CurrPtr2;

	}
}

void producer();
void consumer();
void display();

list1 numbers;
list2 numbers2;

int main()
{
	int pid;
	char ch;
	HANDLE hth[2];
	DWORD thid;
	hmutex=CreateMutex(NULL,FALSE,NULL);

	hproducer=CreateEvent(NULL,TRUE,FALSE,NULL);
	hconsumer=CreateEvent(NULL,TRUE,FALSE,NULL);
	prod=1;

	hth[0]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)producer,NULL,0,&thid);
	hth[1]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)consumer,NULL,0,&thid);
	WaitForMultipleObjects(2,hth,TRUE,INFINITE);
     
     return 0;

}

void producer()
{
    int value;
	while(1)
	{
	l1:if(prod==0)
	{
	ReleaseMutex(hmutex);
	WaitForSingleObject(hproducer,INFINITE);
	continue;
	}
	cout<<"----Enter the new Integer Value----"<<endl;
	cin>>value;
	cout<<"Producer:: Buffer containing "<<value<<" is returned to the full queue"<<endl;
	numbers.insertend1(value);
	cout<<"Producer:: An Empty buffer is obtained form the Empty Queue"<<endl;
	numbers2.addFront2(value);
	prod=0;
	cons=1;
	PulseEvent(hconsumer);
	goto l1;
	}
}

void consumer()
{
	while(1)
	{
	l2:if(cons==0)
	{
	ReleaseMutex(hmutex);
	WaitForSingleObject(hconsumer,INFINITE);
	continue;
	}
	prod=1;
	PulseEvent(hproducer);
	Sleep(2000);
	cout<<"Consumer:: Buffer containing "<<temp<<" is returned from the full Queue"<<endl;
	numbers.deleteFront1();
	cout<<"Consumer:: An Empty Buffer is returned to the Empty Queue"<<endl;
	numbers2.insertend2(temp);
	cons=0;
	prod=1;
	PulseEvent(hproducer);
	display();
	goto l2;
	}
}

void display()
{
	numbers.printlist1();
	numbers2.printlist2();
}


