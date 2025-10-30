/*
 * HashTable.h
 */

#include "HashTableBucket.h"

class HashTable {
    private:
        size_t capacity;
        size_t numElements;
        std::vector<HashTableBucket> table;

    public:
        HashTable(size_t initCapacity); // default constructor
        bool insert(std::string key, size_t value);

        bool remove(std::string key);

        bool contains(const std::string &key) const;

        std::optional<int> get(const std::string &key) const;

        int &operator[](const std::string &key);

        std::vector<std::string> keys() const;

        double alpha() const;

        size_t getCapacity() const;

        size_t size() const;
};
