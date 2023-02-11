#include "linked_list.h"
#include <iostream>

SinglyLinkedList::SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

SinglyLinkedList::~SinglyLinkedList() {
    Node *tmp = head->next;
    Node *prev = head;
    
    while (tmp != nullptr) {
        delete prev;
        prev = tmp;
        tmp = tmp->next;
    }
    
    delete prev;
}

std::string SinglyLinkedList::to_string() {
    Node *tmp = head;
    std::string str = "";
    
    while (tmp != nullptr) {
        str += std::to_string(tmp->data) + " ";
        tmp = tmp->next;
    }
}

void SinglyLinkedList::push_front(int data) {
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = head;

    head = tmp;
    
    if (tail == nullptr) {
        tail = head;
    }
}



void SinglyLinkedList::push_back(int data) {
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = nullptr;

    tail->next = tmp;
    tail = tmp;
    
    if (head == nullptr) {
        head = tail;
    }

}

void SinglyLinkedList::insert(int data, int index) {
    
    
}

void SinglyLinkedList::delete(int data) {
    Node* tmp = head->next;
    Node* prev = head;
    
    if (head->data == data) {
        delete prev;
        head = tmp;
        return;
    }
    
    while (tmp != nullptr) {
        if (tail == tmp) {
            tail = prev;
            tail->next = nullptr;
            delete tmp;
            return;
        }
        
        if (tmp->data == data) {
            prev->next = tmp->next;
        }
        delete tmp;
        tmp = tmp->next;
        return;
    }
    
}

bool SinglyLinkedList::contains(int data) {
    Node* tmp = head;    
    
    while (tmp != nullptr) {
        if (tmp->data = data) return true;
        tmp = tmp->next;
    }
    
    return false;
}

unsigned int SinglyLinkedList::size() {
    Node* tmp = head;
    unsigned int count = 0;
    
    while (tmp != nullptr) {
        tmp = tmp->next;
        count++;
    }
    
    return count;
}    