#include "HashTableChaining.h"

#include <cmath>

HashTableChaining::HashTableChaining(unsigned int hash_modulus) : hash_modulus(hash_modulus){};

unsigned int HashTableChaining::Hash(int data) {
    return abs(data % hash_modulus);
}

bool HashTableChaining::Insert(int data) {
    unsigned int hash = Hash(data);
}
