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

struct node
{
	int id; bool type;// 1=process, 0=resource
};

Process* P[maxProcesses];
Resource* R[maxResources];

void init()
{
	cout<<"\n Enter the Number of Processes : ";
	cin>>numOfProcess;
	cout<<"\n Enter the Number of Resources : ";	
	cin>>numOfResources;
	for(int i=0;i<numOfProcess;i++)
	{
		P[i]=new Process;
		for(int j=0;j<numOfResources;j++)
			P[i]->claim[j]=NULL;
        P[i]->pid=i;
	}
	for(int j=0;j<numOfResources;j++)
	{
	    R[j]=new Resource;
	    R[j]->rid=j;
	}

	//in>>numOfProcess>>numOfResources;
	int temp;
	cout<<"enter num of claims followed by claims (p,r)"<<endl;
	cin>>temp;
	int a,b;
	for(int i=0;i<temp;i++)
	{
		cin>>a>>b;
		//P[a]->resourceCount++;
		P[a]->claim[b]=R[b];
	}

	cout<<"enter initial allocations "<<endl;
	cin>>temp;
	for(int i=0;i<temp;i++)
	{
		cin>>b>>a;
		R[b]->allocate=true;
		R[b]->allocated=P[a];
	}

}

node queue[100];
int visp[100],visr[100];

bool BFS(Process* p);

bool BFS(Resource* r)
{
	cout<<"rr "<<r->rid<<endl;
	if(!r->allocate){ visr[r->rid]=2; cout<<"**1 "<<r->rid<<endl; return false;}
	if(visp[r->allocated->pid]==1){cout<<"re true..."<<r->rid<<endl; visr[r->rid]=2; return true;}
	if(visp[r->allocated->pid]==2){cout<<"**2 "<<r->rid<<endl;visr[r->rid]=2;return false;}
	visp[r->allocated->pid]=1;
	bool res= BFS(r->allocated); visr[r->rid]=2; cout<<"**3 "<<r->rid<<endl;  return res;
}

bool BFS(Process* p) // true for cycle
{

	cout<<"pp "<<p->pid<<endl;
	bool res=false;
	for(int i=0;i<numOfResources;i++)
	{
		if(p->claim[i]==NULL){cout<<"jk prob "<<endl; continue;}
		if(visr[p->claim[i]->rid]==2){cout<<"continuee "<<p->pid<<" "<<i<<endl; continue;} // visited but v=currently not in stack
		if(visr[p->claim[i]->rid]==1){cout<<"eeee true "<<p->pid<<endl;visp[p->pid]=2;return true;} // currently in stack => cycle
		visr[p->claim[i]->rid]=1; // enters stack
		if(BFS(p->claim[i])){cout<<"ret true process "<<p->pid<<endl; visp[p->pid]=2; return true;}
	}
	visp[p->pid]=2;//removed from stack
	return false;
}


void reset(int arr[],int n)
{
    for(int i=0;i<n;i++)arr[i]=0;
   // memset(arr,n,0);
}

bool check()
{

	 bool res=false;
	 reset(visp,numOfProcess);
     reset(visr,numOfResources);//0->unvisited, 1->visited and in stack 2-> visted, has exited stack

	for(int i=0;i<numOfProcess;i++)
	{
		if(visp[i]!=0 || P[i]==NULL)continue;
		visp[i]=1;
		res=BFS(P[i]); if(res)return true;
	}
	return false;

}

void query()
{
	int p,r; bool res;
	while(true)
	{
		cout<<"enter the request (r,p)"<<endl;
		cin>>r>>p;
		// place a check...
		R[r]->allocate=true;
		R[r]->allocated=P[p];
		P[p]->claim[r]=NULL;   //claim to allocate
		res=check();
		if(res) // if cycle forms
		{
			cout<<"not safe "<<endl;
			//revert back
			R[r]->allocate=false;
			P[p]->claim[r]=R[r];
			//R[r]->allocated=NULL;
		}
		else
		{
			cout<<"safe "<<endl;
		}
	}

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
	query();
	return 0;
}

/*
5 5
5
0 0
1 4
3 1
4 4
1 3
5
0 1
1 0
4 3
3 2
2 4

*/
