#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

#include <bitset>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <map>
#include <fstream>
#include <ctime>
#define nmax 100

const int maxResources=100;
const int maxProcesses=100;
int numOfResources;
int numOfProcess;

class Process;
class Resource
{
	public:
	Process* allocated;
	bool allocate;
	int rid;
};

class Process
{
	public:
	Resource* claim[maxResources];
	int pid;

};

class WaitFor
{
    public:
    //Process* waitfor[maxProcesses];
    int waitCount;
    int waitFor[maxProcesses];
};


Process* P[maxProcesses];
Resource* R[maxResources];
WaitFor* waitForGraph[maxProcesses];
ifstream fin ("waitFor.txt");

void init()
{
	fin>>numOfProcess>>numOfResources;
	for(int i=0;i<numOfProcess;i++)
	{
		P[i]=new Process;
		for(int j=0;j<numOfResources;j++)
			P[i]->claim[j]=NULL;
        P[i]->pid=i;
        waitForGraph[i]=new WaitFor;
        waitForGraph[i]->waitCount=0;

	}
	for(int j=0;j<numOfResources;j++)
	{
	    R[j]=new Resource;
	    R[j]->rid=j;
	}

	//in>>numOfProcess>>numOfResources;
	int temp;
	cout<<"enter num of claims followed by claims (p,r)"<<endl;
	fin>>temp;
	int a,b;
	for(int i=0;i<temp;i++)
	{
		fin>>a>>b;
		//P[a]->resourceCount++;
		P[a]->claim[b]=R[b];
	}

	cout<<"enter initial allocations "<<endl;
	fin>>temp;
	for(int i=0;i<temp;i++)
	{
		fin>>b>>a;
		R[b]->allocate=true;
		R[b]->allocated=P[a];
	}

}


void constructWaitForGraph()
{
    for(int i=0;i<numOfProcess;i++)
    {
        for(int j=0;j<numOfResources;j++)
        {
            if(P[i]->claim[j]==NULL)continue;
            if(P[i]->claim[j]->allocate)//resource claimed is already allocated to some other process
            {
                //pd=P[i]->pid; pid=i
                waitForGraph[i]->waitFor[waitForGraph[i]->waitCount++]=R[j]->allocated->pid;

            }

        }
    }
}
int statep[maxProcesses];
int stater[maxResources];

bool DFS(Process* p)
{
    bool res=false; int tmp;
    for(int i=0;i<waitForGraph[p->pid]->waitCount;i++)
    {
        tmp=waitForGraph[p->pid]->waitFor[i];
        if(statep[tmp]==1){statep[p->pid]=2; return true;}
        if(statep[tmp]==2)continue;
        statep[tmp]=1;
        res=DFS(P[tmp]);
        if(res)return true;
    }

    statep[p->pid]=2;//exit from stack
    return false;
}

bool checkDeadlock() // true means a deadlock is there
{

    for(int i=0;i<numOfProcess;i++) statep[i]=0; //unvisited
    for(int i=0;i<numOfResources;i++) stater[i]=0;
    bool res=false;
    for(int i=0;i<numOfProcess;i++)
    {
        if(statep[i]!=0)continue;
        statep[i]=1;
        res=DFS(P[i]);
        if(res)return true;
    }
    return false;
}

void disp()
{
	for(int i=0;i<numOfProcess;i++)
	{
		for(int j=0;j<numOfResources;j++)
		{
			if(P[i]->claim[j]!=NULL)
			cout<<" "<<i<<" "<<j<<endl;
		}
		cout<<endl;
	}
	cout<<endl<<"............"<<endl;
	for(int i=0;i<numOfResources;i++)
	{
		if(!R[i]->allocate)continue;
		cout<<"... "<<i<<" "<<R[i]->allocated->pid<<endl;
	}
}


int main()
{
	init();
	disp();
	constructWaitForGraph();
//	query();
    bool res=checkDeadlock();
    if(res)
    {
        cout<<"Deadlock exists!!!! "<<endl;
    }
    else
    {
        cout<<"No Deadlock!!!! "<<endl;
    }
	return 0;
}
