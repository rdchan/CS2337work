#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"

class Queue
{
    public:
        Queue() { head = nullptr; tail = nullptr;};
        ~Queue();
        Node* head;
        Node* tail;
        void Push(Node* in);
        Node* Pop();
        bool isEmpty() { return head == nullptr; }
    protected:

    private:
};

#endif // QUEUE_H
