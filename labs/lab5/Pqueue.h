#include "Node.h"
#include <string>

class Pqueue {
    private:
        Node* head;
        Node* tail;
        unsigned int _size = 0;

    public:
        Pqueue();
        ~Pqueue();

        void enqueue(int data);
        int dequeue();
        int size();
};