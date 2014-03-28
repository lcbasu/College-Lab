#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX 30

#define UNVISITED -1
#define VISITED 1
#define INFINITY 32767

int adjMat[MAX][MAX],n;

void view();
int search(int src,int des,int pathmat[MAX],int *minLen);
int constructFile();

using namespace std;

typedef struct
{
	int previous;
	int len;
	int status;
}node;

int source;
int nodes;

int main()
{
	char ch,s,d;
	int i,j,k,src,des,minLen,tot,pathMat[MAX];
	constructFile();
	FILE *f1;
	n=nodes;
	printf("The number of vertices of Weighted Graph: %d",n);

	if((f1=fopen("input.txt","rt"))==NULL)
	{
		fprintf(stderr,"Cannot open input file.");
		return 0;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			fscanf(f1,"%d",&adjMat[i][j]);
	fclose(f1);
	printf("\nThe adjacency matrix is . . .\n");
	printf("\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ");
	view();
	//printf(" \nEnter the Source Node:");
	scanf("%c",&s);
	cout<<endl;
	src=toupper(s)-64;
	printf("\nDES\tCOST\tNR");
	for(i=1;i<=n;i++)
	{
		printf("\n");
		tot=search(src,i,pathMat,&minLen);
		printf("%c\t%d",i+64,minLen);
		if(src==i)
			printf("\t-\t");
		else
			printf("\t%c\t",pathMat[tot-1]+64);
	}

	cout<<endl;
	return 0;
}

void view()
{
	int i,j;
	//printf(" ");
	for(i=1;i<=n;i++)
	{
		printf("\t");
		for(i=1;i<=n;i++)
		{
			printf("\n");
			for(j=1;j<=n;j++)
			{
				if(j==1)
					printf("%c\t",i+64);
				printf("%d\t",adjMat[i][j]);
			}
		}
	}
}

int search(int src,int des,int pathMat[MAX],int *minLen)
{
	node graph[MAX];
	int i,k,min,tot=0,curVertex,newLen,u,v;

	*minLen=0;
	for(i=1;i<=n;i++)
	{
		graph[i].previous=0;
		graph[i].len=INFINITY;
		graph[i].status=UNVISITED;
	}
	graph[src].previous=0;
	graph[src].len=0;
	graph[src].status=VISITED;
	curVertex=src;
	while(curVertex!=des)
	{
		for(k=1;k<=n;k++)
		{
			if(adjMat[curVertex][k]>0&&graph[k].status==UNVISITED)
			{
				newLen=graph[curVertex].len+adjMat[curVertex][k];
				if(newLen<graph[k].len)
				{
					graph[k].previous=curVertex;
					graph[k].len=newLen;
				}
			}
		}
		min=INFINITY;
		curVertex=0;

		for(i=1;i<=n;i++)
			if(graph[i].status==UNVISITED&&graph[i].len<min)
			{
				min=graph[i].len;
				curVertex=i;
			}
		if(curVertex==0)
			return 0;
		graph[curVertex].status=VISITED;
	}
	while(curVertex!=0)
	{
		pathMat[++tot]=curVertex;
		curVertex=graph[curVertex].previous;
	}
	for(i=tot;i>1;i--)
	{
		u=pathMat[i];
		v=pathMat[i-1];
		*minLen=*minLen+adjMat[u][v];
	}
	return(tot);
}

int constructFile()
{
    string data[3];
    int dat[3];
    string myline;
    int i,j;
    char* parts;
    ifstream f1("network.txt");
    getline(f1,myline);
    nodes=atoi(myline.c_str());
    cout<<nodes<<"\n";
    int graph[nodes][nodes];
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            graph[i][j]=0;
        }
    }
    while(!f1.eof())
    {
        getline(f1,myline);
        //cout<<myline<<"\n";
         char * pch;
         int TempNumOne=myline.size();
            char line[50];
            for (int a=0;a<=TempNumOne;a++)
                    {
                        line[a]=myline[a];
                    }
          pch = strtok (line," ");
          int m=0;
          while (pch != NULL)
          {
            data[m]=pch;
            dat[m]=atoi(data[m].c_str());
           // cout<<pch<<".";
            pch = strtok (NULL, " ");
            m++;
          }
          /*for(int k=0;k<3;k++)
          {
              cout<<data[k]<<"    "<<dat[k]<<"\n";
          } */
          int s=dat[0];
          int t=dat[1];
          graph[s][t]=dat[2];
          graph[t][s]=dat[2];
          //cout<<"\n";
    }
    ofstream f2("input.txt");
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            f2<<graph[i][j]<<" ";
        }
        f2<<"\n";
    }
    f2.close();
    cout<<"Enter source node:";
    cin>>source;
}
