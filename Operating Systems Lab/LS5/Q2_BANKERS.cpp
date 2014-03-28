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
int need[maxProcessCount][maxResourceCount];
//int requiredResources[maxResourceCount];
//int requiredResourcesCopy[maxProcessCount][maxResourceCount];
//int totalAvailableInstances[maxResourceCount];
int Available[maxResourceCount];
int demand[maxResourceCount]; // stores the current query as demand of the resources by process pid
int AvailableCopy[maxResourceCount];

int resourceCount,processCount;
bitset<100> processDone;
int startSearchingIndex; // start with this index in a cyclic order to get next unallocated process... this is to avoid moving to same unsafe state again and again

void input();
bool checkSafe();
void setMaxColumn();
void allotNext();
void query();

ifstream fin ("maxResourcesDemand.txt");
int temp[maxResourceCount];
int maxOfColumnRequiredResources[maxProcessCount];
vector<int> order; // stores the order .. supports push and pop...


int main()
{
    input();
    //processDone.reset();
    query();

return 0;
}

void makeCopy()
{
    for(int i=0;i<resourceCount;i++)AvailableCopy[i]=Available[i];
}

void revertBack()
{
    for(int i=0;i<resourceCount;i++)Available[i]=AvailableCopy[i];
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
            if(need[i][j]>Available[j]){res=false; break;}
        }
        if(res){vis[i]=1; return i;}
    }
    return -1;
}

bool checkSafe()
{
	//setMaxColumn();
    int pid;
	vis.reset();
	makeCopy();

    for(int i=0;i<processCount;i++)
    {
        pid=getProcess();//get pid of an unfinished process which can be completed by currentlyAvailableResources[]
        if(pid==-1)return false;
        //now pid has enough resources to execute...
        //after exec, the available resources increase by the allotment[pid][]
        //increasing resources after pid's exec.
        for(int j=0;j<resourceCount;j++)Available[j]+=currentAllotment[pid][j];
    }

	return true;

}


void query()//resource request
{
    int pid,choice; bool res,flag;
    while(true)
    {
        cout<<"enter the demanding process "<<endl;
        cin>>pid;
        cout<<"enter no. of instances demanded "<<endl;
        for(int i=0;i<resourceCount;i++)
            cin>>demand[i];

        //TO DO: check with need[][]

        //now check if can be allocated
        flag=true;
        for(int i=0;i<resourceCount;i++)
            if(Available[i]<demand[i])flag=false;
        if(!flag)
        {
            cout<<"Not allowed "<<endl;
            //not safe
            continue;
        }

        res=checkSafe();
        if(res){
            cout<<"safe "<<endl;
        }
        else{
            cout<<"not safe "<<endl;
        }

        cout<<"do you want too revert back: 1 for yes, 0 for no "<<endl;
        cin>>choice;
        revertBack();
        if(choice==0)
        {
            for(int i=0;i<resourceCount;i++)
            {
                currentAllotment[pid][i]+=demand[i];
                Available[i]-=demand[i];
            }
        }

        cout<<"showing currently available "<<endl;
        for(int i=0;i<resourceCount;i++)
        {
            cout<<Available[i]<<" ";
        }
        cout<<endl;
    }

}



void input()
{
	cout<<"Enter the values of no. of processes and no. of resources"<<endl;
	fin>>processCount>>resourceCount;
	cout<<"enter the CurrnetInstances Available of resources"<<endl;
	for(int i=0;i<resourceCount;i++)
	{
		fin>>Available[i];
	}
	cout<<endl;
	cout<<"Enter Max Resorces Demand: processCount x resourceCount"<<endl;
	for(int i=0;i<processCount;i++)
	{
		for(int j=0;j<resourceCount;j++)
		{
			fin>>maxResourcesDemand[i][j];
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

	//calculating need[][]
	cout<<"Showing need matrix "<<endl;
	for(int i=0;i<processCount;i++)
	{
		for(int j=0;j<resourceCount;j++)
		{
			need[i][j]=maxResourcesDemand[i][j]-currentAllotment[i][j];
			cout<<need[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl;

}
