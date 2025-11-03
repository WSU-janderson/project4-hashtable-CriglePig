/* Filename: HashTable.cpp
 * Author: Crystal Daniel
 * Project: Project 4 - Hash Table
 * Due Date: 11/03/2025
 * Program Description: This program implements a hash table using open addressing
 * with pseudo-random probing for collision resolution. It supports operations
 * such as insertion, deletion, lookup, dynamic resizing, and retrieval of all keys.
 * It also provides a bracket operator for reference-based access and a formatted
 * print method.
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <vector>
#include "HashTable.h"

/* Purpose: Constructs a hash table with initial capacity.
 * Parameters:
 *    initCapacity – number of buckets to initially create (defaults to 8)
 * Behavior:
 *    Initializes table vector, sets size to 0, and generates initial offsets
 *    for pseudo-random probing.
 */
HashTable::HashTable(const size_t initCapacity) : m_capacity(initCapacity), m_size(0) {
    table.resize(m_capacity);
    generateOffsets();
}

/* Purpose: Resizes the hash table when load factor exceeds threshold.
 * Behavior:
 *    Doubles the table capacity, rehashes all existing key-value pairs,
 *    and regenerates offsets.
 */
void HashTable::resize() {
    std::vector<HashTableBucket> oldTable = table;
    m_capacity *= 2;
    table.clear();
    table.resize(m_capacity);
    m_size = 0;

    generateOffsets(m_capacity); // deterministic shuffle for new table

    for (HashTableBucket& bucket : oldTable) {
        if (!bucket.isEmpty()) {
            insert(bucket.getKey(), bucket.getValue());
        }
    }
}

/* Purpose: Generates offsets for pseudo-random probing.
 * Parameters:
 *    seed – optional seed for deterministic shuffle (default 0)
 * Behavior:
 *    Fills offsets vector with 1..capacity-1 and shuffles deterministically
 *    if a seed is provided.
 */
void HashTable::generateOffsets(const size_t seed) {
    offsets.clear();

    // Fill offsets vector with 1 ... (capacity - 1)
    for (size_t i = 1; i < m_capacity; i++) {
        offsets.push_back(i);
    }

    // deterministic shuffle if a seed is given
    if (seed > 0) {
        srand(seed); // pseudo-random seed for reproducibility

        for (size_t i = 0; i < offsets.size(); i++) {
            size_t j = rand() % offsets.size();
            std::swap(offsets[i], offsets[j]);
        }
    }
}

/* Purpose: Computes a hash value for a given key.
 * Parameters:
 *    key – string key to hash
 * Returns:
 *    int – hash index within table capacity
 */
int HashTable::hash(const std::string& key) const {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % m_capacity;
}

/* Purpose: Checks if a normal key exists at a given index.
 * Parameters:
 *    key – string key to check
 *    index – bucket index to examine
 * Returns:
 *    true if key exists and is not marked empty
 */
bool HashTable::isNormalKeyFound(const std::string& key, const size_t index) const {
    return table[index].getKey() == key && !table[index].isEmpty();
}

/* Purpose: Checks whether the table contains a key.
 * Parameters:
 *    key – string key to search
 * Returns:
 *    true if key exists, false otherwise
 */
bool HashTable::contains(const std::string& key) const {
    const size_t home = hash(key);

    for (size_t i = 0; i < offsets.size(); i++) {
        const size_t index = (home + offsets[i]) % m_capacity;

        if (table[index].isEmptySinceStart()) {
            break; // stop when hitting an ESS
        }
        if (isNormalKeyFound(key, index)) {
            return true; // key found
        }
    }

    return false;
}

/* Purpose: Inserts a key-value pair into the hash table.
 * Parameters:
 *    key – string key to insert
 *    value – integer value to associate with key
 * Returns:
 *    true if insertion succeeded, false if key already exists
 * Behavior:
 *    Resizes the table if load factor >= 0.5. Uses pseudo-random probing
 *    to find an empty bucket for insertion.
 */
bool HashTable::insert(const std::string& key, const int value) {
    if (contains(key)) return false;
    if (alpha() >= 0.5) resize();

    // seed with key length
    generateOffsets(key.length());
    const size_t home = hash(key);

    // pseudo-random probing
    for (size_t i = 0; i < offsets.size(); i++) {
        const size_t index = (home + offsets[i]) % m_capacity;
        if (table[index].isEmpty()) {
            table[index].load(key, value);
            table[index].makeNormal();
            m_size++;
            return true;
        }
    }

    return false;
}

/* Purpose: Removes a key-value pair from the table.
 * Parameters:
 *    key – string key to remove
 * Returns:
 *    true if removal succeeded, false if key not found
 * Behavior:
 *    Marks bucket as empty-after-remove without altering other buckets.
 */
bool HashTable::remove(const std::string& key) {
    const size_t home = hash(key);

    for (size_t i = 0; i < offsets.size(); i++) {
        const size_t index = (home + offsets[i]) % m_capacity;

        if (table[index].isEmptySinceStart()) {
            break;
        }
        if (isNormalKeyFound(key, index)) {
            table[index].makeEAR();
            m_size--;
            return true;
        }
    }

    return false;
}

/* Purpose: Retrieves the value associated with a key.
 * Parameters:
 *    key – string key to lookup
 * Returns:
 *    optional<int> containing value if key exists, nullopt otherwise
 */
std::optional<int> HashTable::get(const std::string& key) const {
    const size_t home = hash(key);

    for (size_t i = 0; i < offsets.size(); i++) {
        const size_t index = (home + offsets[i]) % m_capacity;

        if (table[index].isEmptySinceStart()) {
            break;
        }
        if (isNormalKeyFound(key, index)) {
            return table[index].getValue();
        }
    }

    return std::nullopt;
}


/* Purpose: Returns all keys currently in the hash table.
 * Returns:
 *    vector<string> containing all active keys
 */
std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> keys;

    for (size_t i = 0; i < m_capacity; i++) {
        if (!table[i].isEmpty()) {
            keys.push_back(table[i].getKey());
        }
    }

    return keys;
}

/* Purpose: Returns current load factor of the table.
 * Returns:
 *    double – ratio of size to capacity
 */
double HashTable::alpha() const {
    return static_cast<double>(m_size) / static_cast<double>(m_capacity);
}

/* Purpose: Returns total number of buckets in the table.
 * Returns:
 *    size_t – table capacity
 */
size_t HashTable::capacity() const {
    return m_capacity;
}

/* Purpose: Returns number of key-value pairs in the table.
 * Returns:
 *    size_t – number of entries
 */
size_t HashTable::size() const {
    return m_size;
}

/* Purpose: Accesses value by key using bracket notation.
 * Parameters:
 *    key – string key to access
 * Returns:
 *    reference to the value associated with the key
 * Throws:
 *    exception if key does not exist
 */
int& HashTable::operator[](const std::string& key) {
    size_t home = hash(key);

    for (size_t i = 0; i < offsets.size(); i++) {
        const size_t index = (home + offsets[i]) % m_capacity;

        if (table[index].isEmptySinceStart()) {
            break;
        }
        if (isNormalKeyFound(key, index)) {
            return table[index].getValueRef();
        }
    }

    throw std::exception();
}

/* Purpose: Prints the hash table to an output stream.
 * Parameters:
 *    os – output stream (e.g., cout)
 * Behavior:
 *    Prints all non-empty buckets in formatted form.
 */
std::ostream& operator<<(std::ostream& os, const HashTable& table) {
    os << table.printMe();
    return os;
}

/* Purpose: Returns a string representation of the hash table.
 * Returns:
 *    string – formatted output of all non-empty buckets
 */
std::string HashTable::printMe() const {
    std::ostringstream out;

    for (size_t i = 0; i < m_capacity; i++) {
        const HashTableBucket bucket = table[i];

        if (!bucket.isEmpty()) {
            out << "Bucket " << i << ": " << bucket << "\n";
        }
    }

    return out.str();
}