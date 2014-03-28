#include<iostream>
using namespace std;

int empty=5;
int full=0;
int mutex=1;
bool b=true;

void wait(int &e)
{
while(e<=0);
e--;
}

void signal(int &f)
{
f++;
}

void* producer(void *x)
{

do
{
wait(empty);
wait(mutex);
while(!b);
cout<<"Producer used the space: Now remaining empty "<<empty<<endl;
sleep(1);
b=false;
signal(mutex);
signal(full); //it should be kept in mind that this full doesn't follow immediately follow mutex, so till the signal function is called, consumer can gain mutex and show full as 0
cout<<"Producer says full is "<<full<<endl;
b=true;
}while(1);
}

void* consumer(void *y)
{

do
{
wait(full);
sleep(3); //this gap between full and mutex allows producer to again gain mutex
wait(mutex);
while(!b);
cout<<"Consumer freed a space: Now full "<<full<<endl;
b=false;
signal(mutex);
signal(empty);
b=true;
cout<<"CONSUMER IN THE REMAINDER SECTION"<<endl;
}while(1);
}



int main()
{
int i;
pthread_t thread1, thread2;
pthread_create(&thread1, NULL, producer, (void*)i);
pthread_create(&thread2, NULL, consumer, (void*)i);

while(1)
{
sleep(10);
}
}
