/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>
#include "HashTable.h"


int main() {
    HashTable hashTable;
    hashTable.insert("Wolf", 27);
    hashTable.insert("Bear", 59);
    hashTable.insert("Chicken", 5);
    hashTable.insert("Worm", 1);
    hashTable.insert("Cat", 12);
    hashTable.insert("Dog", 14);
    hashTable.insert("Lizard", 3);
    hashTable.insert("Ostrich", 32);
    hashTable.insert("Komodo Dragon", 40);
    hashTable.insert("Snake", 20);

    std::cout << hashTable << std::endl;

    hashTable.remove("Snake");
    hashTable.remove("Dog");
    hashTable.remove("Bear");
    hashTable.remove("Ostrich");
    hashTable.remove("Cat");
    hashTable.remove("Lizard");
    hashTable.remove("Komodo Dragon");
    hashTable.remove("Worm");

    std::cout << hashTable << std::endl;

    hashTable.insert("Dog", 14);
    hashTable.insert("Bear", 14);

    std::cout << hashTable << std::endl;

    return 0;
}