#include "Node.h"
#include <string>

class Queue {
    private:
        Node* head;
        Node* tail;
        unsigned int _size = 0;

    public:
        Queue();
        ~Queue();

        void enqueue(int data);
        int dequeue();
        int front();
        int back();
        int size();
};