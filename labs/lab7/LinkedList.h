#include <vector>

struct Node {
    int data = 0;
    Node *next = nullptr;
    Node(int data, Node *next) : data(data), next(next) {};
};

class LinkedList {
   private:
    Node *head = nullptr;

   public:
    LinkedList();
    ~LinkedList();
    void Insert(int);
    std::vector<int> Access();
};
