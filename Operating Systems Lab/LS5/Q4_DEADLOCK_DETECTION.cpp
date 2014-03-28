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
#include <vector>

const int maxProcessCount=10;
const int maxResourceCount=10;
int maxResourcesDemand[maxProcessCount][maxResourceCount];
int currentAllotment[maxProcessCount][maxResourceCount];
int request[maxProcessCount][maxResourceCount];
int currentlyAvailableInstances[maxResourceCount];
int demand[maxResourceCount]; // stores the current query as demand of the resources by process pid
int currentlyAvailableInstancesCopy[maxResourceCount];

int resourceCount,processCount;
bitset<100> processDone;
int startSearchingIndex; // start with this index in a cyclic order to get next unallocated process... this is to avoid moving to same unsafe state again and again

void input();
bool checkSafe();
void setMaxColumn();
void allotNext();
void query();

ifstream fin ("checkDeadlockMultiple.txt");
int temp[maxResourceCount];
int maxOfColumnRequiredResources[maxProcessCount];
vector<int> order; // stores the order .. supports push and pop...


int main()
{
    input();
    //processDone.reset();
    //query();
    bool res=checkSafe();
    if(!res)
    {
        cout<<"Deadlock "<<endl;
    }
    else
    {
        cout<<"No Deadlock "<<endl;
    }

return 0;
}

void makeCopy()
{
    for(int i=0;i<resourceCount;i++)currentlyAvailableInstancesCopy[i]=currentlyAvailableInstances[i];
}

void revertBack()
{
    for(int i=0;i<resourceCount;i++)currentlyAvailableInstances[i]=currentlyAvailableInstancesCopy[i];
}
bitset<100> vis;

int getProcess()//get pid of an unfinished process which can be completed by currentlyAvailableResources[]
{
    bool res;
    for(int i=0;i<processCount;i++)
    {
        if(vis[i])continue;
        res=true;
        for(int j=0;j<resourceCount;j++)
        {
            if(request[i][j]>currentlyAvailableInstances[j]){res=false; break;}
        }
        if(res){vis[i]=1; return i;}
    }
    return -1;
}

bool checkSafe()//returns true for safe
{
	//setMaxColumn();
	makeCopy();
    int pid;
	vis.reset();
	makeCopy();

    for(int i=0;i<processCount;i++)
    {
        pid=getProcess();//get pid of an unfinished process which can be completed by currentlyAvailableResources[]
        if(pid==-1){revertBack();return false;}
        cout<<"step "<<(i+1)<<endl;
        //now pid has enough resources to execute...
        //after exec, the available resources increase by the allotment[pid][]
        //increasing resources after pid's exec.
        for(int j=0;j<resourceCount;j++){currentlyAvailableInstances[j]+=currentAllotment[pid][j]; cout<<currentlyAvailableInstances[j]<<" ";}
        cout<<endl;
    }

    revertBack();
	return true;

}




void input()
{
	cout<<"Enter the values of no. of processes and no. of resources"<<endl;
	fin>>processCount>>resourceCount;
	cout<<"enter the CurrnetInstances Available of resources"<<endl;
	for(int i=0;i<resourceCount;i++)
	{
		fin>>currentlyAvailableInstances[i];
	}
	cout<<endl;
	cout<<"Enter Requirement: processCount x resourceCount"<<endl;
	for(int i=0;i<processCount;i++)
	{
		for(int j=0;j<resourceCount;j++)
		{
			fin>>request[i][j];
		}
	}
	cout<<endl;
	cout<<"Enter current Allotment: processCount x resourceCount"<<endl;
	for(int i=0;i<processCount;i++)
	{
		for(int j=0;j<resourceCount;j++)
		{
			fin>>currentAllotment[i][j];
		}
	}
	cout<<endl;
	/*cout<<"Enter more required resources: processCount x resourceCount"<<endl;
	for(int i=0;i<processCount;i++)
	{
		for(int j=0;j<resourceCount;j++)
		{
			fin>>requiredResources[i][j];
		}
	}*/

	//calculating request[][]
	/*cout<<"Showing request matrix "<<endl;
	for(int i=0;i<processCount;i++)
	{
		for(int j=0;j<resourceCount;j++)
		{
			request[i][j]=maxResourcesDemand[i][j]-currentAllotment[i][j];
			cout<<request[i][j]<<" ";
		}
		cout<<endl;
	}
*/
	cout<<endl;

}

/*
5 3
0 0 0
0 0 0
2 0 2
0 0 0
1 0 0
0 0 2
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
NO DEADLOCK
*/

/*
5 3
0 0 0
0 0 0
2 0 2
0 0 1
1 0 0
0 0 2
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
DEADLOCK
*/
