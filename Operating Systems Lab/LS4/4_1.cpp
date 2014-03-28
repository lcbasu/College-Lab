#include<iostream>
#include<map>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
int main()
{
     map< pair<char,int>, vector< pair<char,int> > > graph;
     vector< pair<char,int> >::iterator it;
     queue< pair<char,int> > que[2];
     cout<<"Which type of edge: \n";
     while(1)
     {
          int r,p,t;
          cout<<"1. Allocation 2. Request ?"<<endl;
          cin>>t;
          if(t==1)
          {
               cout<<"enter resource id :";
               cin>>r;
               cout<<"enter process id :";
               cin>>p;
               bool flag=0;
               que[0].push(make_pair('p',p));
               for(int i=0;!que[i%2].empty();i++)
               {
                    while(!que[i%2].empty())
                    {
                         vector< pair<char,int> > curr = graph[que[i%2].front()];
                         que[i%2].pop();
                         for(it=curr.begin();it!=curr.end();it++)
                         {
                              if((*it).first=='r' && (*it).second==r)
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
               graph[make_pair('r',r)].push_back(make_pair('p',p));
          }
          else
          {
               cout<<"enter process id :";
               cin>>p;
               cout<<"enter resource id :";
               cin>>r;
               
               bool flag=0;
               que[0].push(make_pair('r',r));
               for(int i=0;!que[i%2].empty();i++)
               {
                    while(!que[i%2].empty())
                    {
                         vector< pair<char,int> > curr = graph[que[i%2].front()];
                         que[i%2].pop();
                         for(it=curr.begin();it!=curr.end();it++)
                         {
                              if((*it).first=='p' && (*it).second==p)
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
               graph[make_pair('p',p)].push_back(make_pair('r',r));
          }
     }
     return 0;
}
