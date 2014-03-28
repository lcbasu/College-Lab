#include<iostream>
#include<map>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
int main()
{
     map<int,vector<int> > graph;
     vector<int>::iterator it;
     queue<int> que[2];
     while(1)
     {
          int p1,p2;
          cout<<"FROM process : ";
          cin>>p1;
          cout<<"TO process : ";
          cin>>p2;
          bool flag=0;
          que[0].push(p2);
          for(int i=0;!que[i%2].empty();i++)
          {
               while(!que[i%2].empty())
               {
                    vector<int> curr = graph[que[i%2].front()];
                    que[i%2].pop();
                    for(it=curr.begin();it!=curr.end();it++)
                    {
                         if((*it)==p1)
                         {
                              flag=1;
                              break;
                         }
                         else
                              que[(i+1)%2].push((*it));
                    }
                    if(flag)
                         break;
               }
               if(flag)
                    break;
          }
          if(flag)
          {
               cout<<"WARNING : deadlock may occur !! "<<endl;
          }
          else
          {
               cout<<"continue .. "<<endl;
          }
          graph[p1].push_back(p2);
     }
     return 0;
}
