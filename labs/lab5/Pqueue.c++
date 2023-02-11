#include "Pqueue.h"
#include <iostream>

// enqueue: unsorted O(1)
// dequeue: find highest value O(n)

Pqueue::Pqueue(){
    this->head = nullptr;
    this->tail = nullptr;
    this->_size = 0;
}

Pqueue::~Pqueue() {
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

void Pqueue::enqueue(int data){
    // Special case: enqueueing when queue is empty
    if (this->head == nullptr) {
        Node* temp = new Node(data);
        this->head = temp;
        
        this->_size++;
        
        return;
    }

    // Start temp pointer at head
    Node* temp = new Node(data);

    // Create a new Node at the start of the list
    temp->next = head->next;
    this->_size++;
    
    // Update head accordingly
    this->head = temp;
}

// change to dequeue
int Pqueue::dequeue() {
    int idx = 0;
    int highest_value_idx = 0;
    int highest_value = 0;

    Node* temp = this->head;

    // Traverse until end of queue is reached
    while (temp != nullptr) {
        if (temp->data > highest_value) {
            highest_value = temp->data;
            highest_value_idx = idx;
        }

        idx++;
        temp = temp->next;
    }

    if (this->_size != 0) {
        Node* prev = this->head;
        Node* curr = this->head->next;
        
        for (int i = 0; i < highest_value_idx; i++) {
            prev = curr;
            curr = curr->next;
        }

        Node *temp = curr;
        prev->next = curr->next;
        delete temp;
    }
    
    return highest_value;
}

int Pqueue::size(){
    return this->_size;
}