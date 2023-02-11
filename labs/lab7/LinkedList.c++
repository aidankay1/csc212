#include "LinkedList.h"

LinkedList::LinkedList() {

}

LinkedList::~LinkedList() {
    Node *temp = this->head;
    Node *next = temp ? temp->next : nullptr;

    while (temp) {
        delete temp;

        temp = next;
        next = temp ? temp->next : nullptr;
    }
}

void LinkedList::Insert(int data) {
    if (!this->head) {
        this->head = new Node(data, nullptr);
        return;
    }

    Node *temp = this->head;
    Node *next = temp->next;

    while (temp) {
        if (!next) {
            temp->next = new Node(data, nullptr);
            return;
        }

        temp = next;
        next = temp ? temp->next : nullptr;
    }
}

std::vector<int> LinkedList::Access() {
    std::vector<int> data;

    Node *temp = this->head;
    Node *next = temp->next;

    while (temp) {
        data.push_back(temp->data);

        temp = next;
        next = temp ? temp->next : nullptr;
    }

    return data;
}
