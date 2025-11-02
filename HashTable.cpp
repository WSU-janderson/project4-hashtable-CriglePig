/*
 * HashTable.cpp
 */

#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>
#include "HashTable.h"

/*
 * Only a single constructor that takes an initial capacity for the table is
 * necessary. If no capacity is given, it defaults to 8 initially
 */
HashTable::HashTable(size_t initCapacity) : capacity(initCapacity), size(0) {
    table.resize(capacity);
}

void HashTable::resize() {
    std::vector<HashTableBucket> oldTable = table;
    capacity *= 2;
    table.clear();
    table.resize(capacity);
    size = 0;

    for (HashTableBucket& bucket : oldTable) {
        if (!bucket.isEmpty()) {
            insert(bucket.getKey(), bucket.getValue());
        }
    }
}

int HashTable::hash(const std::string& key) const {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % capacity;
}

bool HashTable::isNormalKeyFound(const std::string& key, const size_t index) const {
    return table[index].getKey() == key && !table[index].isEmpty();
}

/**
* contains returns true if the key is in the table and false if the key is not in
* the table.
*/
bool HashTable::contains(const std::string& key) const {
    for (size_t i = 0; i < capacity; i++) {
        if (isNormalKeyFound(key, i)) {
            return true;
        }
    }
    return false;
}

/**
 * Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
 * method should return true if the insertion was successful. If the insertion was
 * unsucessful, such as when a duplicate is attempted to be inserted, the method
 * should return false
 */
bool HashTable::insert(const std::string& key, const int value) {
    if (contains(key)) return false; // returns false if duplicate key

    if (alpha() >= 0.5) {
        resize();
    }

    size_t index = hash(key);

    // loops until empty bucket is found
    while (!table[index].isEmpty()) {
        index = (index + 1) % capacity; // move to the next bucket. When reaching the end, wrap around
    }

    table[index].load(key, value);
    table[index].makeNormal();
    size++;

    return true;
}

 /**
 * If the key is in the table, remove will “erase” the key-value pair from the
 * table. This might just be marking a bucket as empty-after-remove
 */
bool HashTable::remove(const std::string& key) {
    if (!contains(key)) return false;

    for (size_t i = 0; i < capacity; i++) {
        if (isNormalKeyFound(key, i)) {
            table[i].makeEAR();
        }
    }

    size--;
    return true;
}

/**
 * If the key is found in the table, find will return the value associated with
 * that key. If the key is not in the table, find will return something called
 * nullopt, which is a special value in C++. The find method returns an
 * optional<int>, which is a way to denote a method might not have a valid value
 * to return. This approach is nicer than designating a special value, like -1, to
 * signify the return value is invalid. It's also much better than throwing an
 * exception if the key is not found.
 */
std::optional<int> HashTable::get(const std::string& key) const {
    for (size_t i = 0; i < capacity; i++) {
        if (isNormalKeyFound(key, i)) {
            return table[i].getValue();
        }
    }
    return std::nullopt;
}

/**
 * The bracket operator lets us access values in the map using a familiar syntax,
 * similar to C++ std::map or Python dictionaries. It behaves like get, returning
 * the value associated with a given key: int idNum = hashTable[“James”];
 * Unlike get, however, the bracket operator returns a reference to the value,
 * which allows assignment: hashTable[“James”] = 1234;
 * If the key is not in the table, returning a valid reference is impossible. You may choose to
 * throw an exception in this case, but for our implementation, the situation
 * results in undefined behavior. Simply put, you do not need to address attempts
 * to access keys not in the table inside the bracket operator method.
 */
int& HashTable::operator[](const std::string& key) {
    for (size_t i = 0; i < capacity; i++) {
        if (isNormalKeyFound(key, i)) {
            return table[i].getValueRef();
        }
    }
    throw std::exception(); // throw exception if no valid key-pair found
}

/**
* keys returns a std::vector (C++ version of ArrayList, or simply list/array)
* with all of the keys currently in the table. The length of the vector should be
* the same as the size of the hash table.
*/
std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> keys;

    for (size_t i = 0; i < capacity; i++) {
        if (!table[i].isEmpty()) {
            keys.push_back(table[i].getKey());
        }
    }
    return keys;
}

/**
* alpha returns the current load factor of the table, or size/capacity. Since
* alpha returns a double,make sure to properly cast the size and capacity, which
* are size_t, to avoid integer division. You can cast a size_t num to a double in
* C++ like:
                 static_cast<double>(num)
The time complexity for
* this method must be O(1).
*/
double HashTable::alpha() const {
    return static_cast<double>(size) / static_cast<double>(capacity);
}

/**
* capacity returns how many buckets in total are in the hash table. The time
* complexity for this algorithm must be O(1).
*/
size_t HashTable::getCapacity() const {
    return capacity;
}

/**
* The size method returns how many key-value pairs are in the hash table. The
* time complexity for this method must be O(1)
*/
size_t HashTable::getSize() const {
    return size;
}