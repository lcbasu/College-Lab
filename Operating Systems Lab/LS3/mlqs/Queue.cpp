#include <iostream>
#ifndef QUEUE_H
#define QUEUE_H
#include "Node.cpp"

class Queue
{
    private:
        Node *front;
        Node *rear;

    public:
        Queue();
        void enQ(Node *);
        Node *deQ();
        bool isEmpty();
        int count();
        void displayQ();
        Node *extract_min_priority(int);
};

#endif

using namespace std;

Queue::Queue()
{
    front = NULL;
    rear = NULL;
}

void Queue::enQ(Node *newNode)
{
    if( (front == NULL) && (rear == NULL) )
        front = rear = newNode;
    else
    {
        rear->set_next(newNode);
        rear = newNode;
    }
}

Node *Queue::deQ()
{
    if( (front == NULL) && (rear == NULL) )
    {
        cout<<"Queue is Empty!"<<endl;
        return NULL;
    }
    else
    {
        Node *to_delete = front;
        front = front->return_next();
        if(front == NULL)
        {
            front = rear = NULL;
        }
        return to_delete;
    }
}

bool Queue::isEmpty()
{
    if( (front == NULL) && (rear == NULL) )
        return true;
    else
        return false;
}

int Queue::count()
{
    int ctr = 0;
    if( (front == NULL) && (rear == NULL) )
        return 0;

    Node *currNode = front;
    while(currNode != rear)
    {
        ctr += 1;
        currNode = currNode->return_next();
    }
    return ctr + 1;
}

void Queue::displayQ()
{
    if( isEmpty() )
        cout<<"Queue is Empty!"<<endl<<endl;


    else
    {
        Node *currNode = front;
        while(currNode != rear->return_next())
        {
            cout<<currNode->return_PID()<<"\t"<<currNode->return_PName()<<"\t"
                <<currNode->return_arrival_time()<<"\t"<<currNode->return_burst_time()
                <<"\t"<<currNode->return_priority()<<endl;
            currNode = currNode->return_next();
        }
    }
}

Node *Queue::extract_min_priority(int time)
{
    if( (front == NULL) && (rear == NULL) )
        return NULL;

    Node *currNode = front;
    Node *minNode = NULL;

    while(currNode != NULL)
    {
        if(currNode->return_arrival_time() <= time)
            minNode = currNode;
        currNode = currNode->return_next();
    }

    currNode = front;
    while(currNode != NULL)
    {
        if( (currNode->return_arrival_time() <= time) && (currNode->return_priority() <= minNode->return_priority()) )
            minNode = currNode;
        currNode = currNode->return_next();
    }

    Node *toDelete = NULL;

    if(minNode == front)
    {
        toDelete = front;
        front = front->return_next();
        if(front == NULL)
            front = rear = NULL;
    }
    else if(minNode == rear)
    {
        Node *currNode = front;
        Node *prevNode = NULL;
        while(currNode != rear)
        {
            prevNode = currNode;
            currNode = currNode->return_next();
        }
        toDelete = rear;
        prevNode->set_next(NULL);
        rear = prevNode;
    }
    else
    {
        Node *currNode = front;
        Node *prevNode = NULL;
        while(currNode != NULL)
        {
            if(currNode == minNode)
            {
                toDelete = currNode;
                prevNode->set_next(currNode->return_next());
            }
            prevNode = currNode;
            currNode = currNode->return_next();
        }
    }

    return minNode;
}
