#include <iostream>
using namespace std;

#ifndef NODE_H
#define NODE_H

class Node
{
    private:
        int PID;
        char *PName;
        int burst_time;
        int arrival_time;
        int priority;
        Node *next;

    public:
        Node();

        void set_PID(int);
        void set_burst_time(int);
        void set_arrival_time(int);
        void set_PName(char *);
        void set_priority(int);
        void set_next(Node *);

        int return_PID();
        int return_arrival_time();
        int return_burst_time();
        char *return_PName();
        int return_priority();
        Node *return_next();
};

#endif

Node::Node()
{
    PID = 0;
    PName = NULL;
    burst_time = 0;
    arrival_time = 0;
}

void Node::set_PID(int pid)
{
    this->PID = pid;
}

void Node::set_burst_time(int bt)
{
    this->burst_time = bt;
}

void Node::set_arrival_time(int at)
{
    this->arrival_time = at;
}

void Node::set_priority(int p)
{
    this->priority = p;
}

void Node::set_PName(char *pname)
{
    this->PName = pname;
}

void Node::set_next(Node *nxt)
{
    this->next = nxt;
}

int Node::return_PID()
{
    return this->PID;
}

int Node::return_burst_time()
{
    return this->burst_time;
}

int Node::return_arrival_time()
{
    return this->arrival_time;
}

int Node::return_priority()
{
    return this->priority;
}

char *Node::return_PName()
{
    return this->PName;
}

Node *Node::return_next()
{
    return this->next;
}



