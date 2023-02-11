#include <vector>
#include "LinkedList.h"

class HashTableChaining {
    private:
        unsigned int hash_modulus;
        std::vector<LinkedList> table;
        unsigned int Hash(int);
    public:
        HashTableChaining(unsigned int);
        bool Insert(int);
        int Access(int);
};
