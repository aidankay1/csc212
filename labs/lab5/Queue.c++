#include "Queue.h"
#include <iostream>

Queue::Queue(){
    this->head = nullptr;
    this->tail = nullptr;
    this->_size = 0;
}

Queue::~Queue() {
    // Special case: if queue is empty
    if (head == nullptr) {
        return;
    }
    
    Node* prev = this->head;
    Node* curr = prev->next;

    // Traverse list, deleting elements one by one
    while (curr != nullptr) {
        delete prev;
        prev = curr;
        curr = curr->next;
    }

    delete prev;
    this->head = nullptr;
    this->tail = nullptr;
}

void Queue::enqueue(int data){
    // Special case: enqueueing when queue is empty
    if (this->tail == nullptr) {
        Node* temp = new Node(data);
        this->head = temp;
        this->tail = temp;

        this->_size++;
        return;
    }

    // Start temp pointer at tail
    Node* temp = this->tail;

    // Create a new Node at the end of the list
    temp->next = new Node(data);
    this->_size++;
    
    // Update tail accordingly
    this->tail = temp->next;
}

// change to dequeue
int Queue::dequeue() {
    // Special case: queue is empty
    if (!this->_size) {
        return -1;
    }
    
    // Get element at front
    Node* temp = this->head;

    // Move head to next element
    this->head = temp->next;

    int data = temp->data;

    // Remove front element
    delete temp;    
    this->_size--;

    
    
    return data;
}

int Queue::front() {
    return this->head->data;
}

int Queue::back(){
    return this->tail->data;
}

int Queue::size(){
    return this->_size;
}