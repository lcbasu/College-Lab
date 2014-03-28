#include <iostream>
using namespace std;

#define max 100
#define min 10

int ref[max],count,frame[min],n;

void inputString()
{
 	int temp;
 	cout << "Number of Page Frames : " ;
 	cin >> n ;
 	count = 0;
 	cout << "\nReference String (-1 for end) : \n";
 	cin >> temp;
 	while(temp != -1 && count <= max)
 	{
  		ref[count++]=temp;
  		cin >> temp;
 	}
}

int frameNumber(int nm)
{
	int fn,l,big=nm;
	int k;
	for(k=0;k<n;k++)
	{
		l = nm+1;
		while(ref[l] != frame[k] && l < count)
			l++;
		if(l>big)
		{
			big = l;
			fn = k;
		}
	}
	return fn;
}

void optimalPageReplacement()
{
	int i,j,fault=0;
	for(i=0;i<n;i++)
		frame[i] = -1;
	int ind,pos=0;
	cout << "-----------------------------";
	cout << "\nPage    Frame Status\n";
	cout << "-----------------------------";
	for(i=0;i<count;i++)
	{
		ind = 0;
		cout << "\n " << ref[i] << "\t";
		for(j=0;j<n;j++)
		{
			if(frame[j] == -1)
			{
				ind = 1;
				pos = j;
				break;
			}
			if(frame[j] == ref[i])
			{
				ind = 2;
				break;
			}
		}
		if(ind != 2)
		{
			if(ind == 0)
				pos = frameNumber(i);
			frame[pos] = ref[i];
			fault ++;
		}
		for(j=0;j<n;j++)
		{
			if(frame[j] == -1)
				cout << "| -";
			else
				cout << "| " << frame[j];
		}
	}
	cout << "\nTotal Page Fault for Optimal Page Replacement is : " << fault << "\n";
}

int main()
{
	inputString();
	optimalPageReplacement();
	return 0;
}