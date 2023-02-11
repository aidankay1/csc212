#include "Pqueue.h"
#include <iostream>

int main(){
    Pqueue q;

    std::cout << "created Queue q" << '\n';
    
    q.enqueue(7);
    q.enqueue(101);
    q.enqueue(2);

    std::cout << "enqueued 3 elements" << '\n';

    std::cout << q.size() << '\n';

    std::cout << q.dequeue() << '\n';
    std::cout << q.dequeue() << '\n';
    std::cout << q.dequeue() << '\n';
}