#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#endif

#include <string>

struct Node {
    int data;
    Node *next;
};

class SinglyLinkedList {
   private:
    Node *head;
    Node *tail;

   public:
    void push_front(int data);
    void push_back(int data);
    void insert(int data, int index);
    void del(int data);
    bool contains(int data);
    unsigned int size();
    std::string to_string();

    SinglyLinkedList();
    ~SinglyLinkedList();
};
